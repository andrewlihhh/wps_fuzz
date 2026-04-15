// Nautilus
// Copyright (C) 2024  Daniel Teuchert, Cornelius Aschermann, Sergej Schumilo

extern crate time as othertime;
use othertime::strftime;

use std::collections::HashSet;
use std::collections::VecDeque;
use std::env;
use std::fs;
use std::fs::File;
use std::io::Cursor;
use std::io::Read;
use std::io::stdout;
use std::io::Write;
use std::process::Command;
use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Instant;

use forksrv::exitreason::ExitReason;
use forksrv::newtypes::SubprocessError;
use forksrv::newtypes::QemuRunIO;
use forksrv::ForkServer;
use grammartec::context::Context;
use grammartec::tree::TreeLike;
use shared_state::GlobalSharedState;
use snafu::ResultExt;
use tempfile::tempdir;
use zip::read::ZipArchive;
use zip::write::FileOptions;
use zip::CompressionMethod;
use zip::ZipWriter;

pub enum ExecutionReason {
    Havoc,
    HavocRec,
    Min,
    MinRec,
    Splice,
    Det,
    Gen,
}

pub struct Fuzzer {
    forksrv: ForkServer,
    last_tried_inputs: HashSet<Vec<u8>>,
    last_inputs_ring_buffer: VecDeque<Vec<u8>>,
    pub global_state: Arc<Mutex<GlobalSharedState>>,
    pub target_path: String,
    pub target_args: Vec<String>,
    pub execution_count: u64,
    pub average_executions_per_sec: f32,
    pub bits_found_by_havoc: u64,
    pub bits_found_by_havoc_rec: u64,
    pub bits_found_by_min: u64,
    pub bits_found_by_min_rec: u64,
    pub bits_found_by_splice: u64,
    pub bits_found_by_det: u64,
    pub bits_found_by_det_afl: u64,
    pub bits_found_by_gen: u64,
    pub asan_found_by_havoc: u64,
    pub asan_found_by_havoc_rec: u64,
    pub asan_found_by_min: u64,
    pub asan_found_by_min_rec: u64,
    pub asan_found_by_splice: u64,
    pub asan_found_by_det: u64,
    pub asan_found_by_det_afl: u64,
    pub asan_found_by_gen: u64,
    work_dir: String,
    input_lowerer_path: Option<String>,
    input_lowerer_args: Vec<String>,
}

impl Fuzzer {
    pub fn new(
        path: String,
        args: Vec<String>,
        global_state: Arc<Mutex<GlobalSharedState>>,
        work_dir: String,
        timeout_in_millis: u64,
        bitmap_size: usize,
        input_lowerer_path: Option<String>,
        input_lowerer_args: Vec<String>,
    ) -> Result<Self, SubprocessError> {
        let fs = ForkServer::new(
            path.clone(),
            args.clone(),
            true,
            timeout_in_millis,
            bitmap_size,
        );
        return Ok(Fuzzer {
            forksrv: fs,
            last_tried_inputs: HashSet::new(),
            last_inputs_ring_buffer: VecDeque::new(),
            global_state,
            target_path: path,
            target_args: args,
            execution_count: 0,
            average_executions_per_sec: 0.0,
            bits_found_by_havoc: 0,
            bits_found_by_havoc_rec: 0,
            bits_found_by_min: 0,
            bits_found_by_min_rec: 0,
            bits_found_by_splice: 0,
            bits_found_by_det: 0,
            bits_found_by_det_afl: 0,
            bits_found_by_gen: 0,
            asan_found_by_havoc: 0,
            asan_found_by_havoc_rec: 0,
            asan_found_by_min: 0,
            asan_found_by_min_rec: 0,
            asan_found_by_splice: 0,
            asan_found_by_det: 0,
            asan_found_by_det_afl: 0,
            asan_found_by_gen: 0,
            work_dir: work_dir,
            input_lowerer_path,
            input_lowerer_args,
        });
    }

    pub(crate) fn materialize_input<T: TreeLike>(
        &self,
        tree: &T,
        ctx: &Context,
    ) -> Result<Vec<u8>, SubprocessError> {
        let ir = tree.unparse_to_vec(ctx);
        self.lower_input(ir)
    }

    fn lower_input(&self, ir: Vec<u8>) -> Result<Vec<u8>, SubprocessError> {
        let Some(lowerer_path) = self.input_lowerer_path.as_ref() else {
            return Ok(ir);
        };

        let temp_dir = tempdir().context(QemuRunIO {
            task: "Could not create temporary lowerer directory".to_string(),
        })?;
        let input_path = temp_dir.path().join("input.ir.json");
        let output_path = temp_dir.path().join("output.docx");

        fs::write(&input_path, &ir).context(QemuRunIO {
            task: format!("Could not write lowerer input to {}", input_path.display()),
        })?;

        let args = self
            .input_lowerer_args
            .iter()
            .map(|arg| match arg.as_str() {
                "@@INPUT@@" => input_path.to_string_lossy().into_owned(),
                "@@OUTPUT@@" => output_path.to_string_lossy().into_owned(),
                _ => arg.clone(),
            })
            .collect::<Vec<_>>();

        let output = Command::new(lowerer_path)
            .args(&args)
            .output()
            .context(QemuRunIO {
                task: format!("Could not execute lowerer command {}", lowerer_path),
            })?;

        if !output.status.success() {
            let stderr = String::from_utf8_lossy(&output.stderr);
            let stdout = String::from_utf8_lossy(&output.stdout);
            return Err(SubprocessError::QemuRunIO {
                task: format!(
                    "Lowerer command {} failed with status {:?}. stdout: {} stderr: {}",
                    lowerer_path,
                    output.status.code(),
                    stdout.trim(),
                    stderr.trim()
                ),
                source: std::io::Error::new(std::io::ErrorKind::Other, "input lowerer failed"),
            });
        }

        let lowered = fs::read(&output_path).context(QemuRunIO {
            task: format!("Could not read lowerer output from {}", output_path.display()),
        })?;
        Ok(lowered)
    }

    pub fn run_on_with_dedup<T: TreeLike>(
        &mut self,
        tree: &T,
        exec_reason: ExecutionReason,
        ctx: &Context,
    ) -> Result<bool, SubprocessError> {
        let code = self.materialize_input(tree, ctx)?;
        if self.input_is_known(&code) {
            return Ok(false);
        }
        self.run_on(&code, tree, exec_reason, ctx)?;
        return Ok(true);
    }

    pub fn run_on_without_dedup<T: TreeLike>(
        &mut self,
        tree: &T,
        exec_reason: ExecutionReason,
        ctx: &Context,
    ) -> Result<(), SubprocessError> {
        let code = self.materialize_input(tree, ctx)?;
        return self.run_on(&code, tree, exec_reason, ctx);
    }

    pub fn run_materialized_seed(
        &mut self,
        code: &[u8],
        exec_reason: ExecutionReason,
    ) -> Result<bool, SubprocessError> {
        if self.input_is_known(code) {
            return Ok(false);
        }

        let (exitreason, _) = self.exec_raw(code)?;
        let is_crash = matches!(exitreason, ExitReason::Normal(223) | ExitReason::Signaled(_));
        let mut discovered_new_path = false;

        if let Some(mut new_bits) = self.candidate_new_bits(is_crash) {
            if exitreason != ExitReason::Timeouted || self.collect_timeout_coverage() {
                if !new_bits.is_empty() {
                    self.commit_new_bits(is_crash, &new_bits);
                    self.increment_path_counter(&exec_reason);
                    discovered_new_path = true;
                }
            }
        }

        Ok(discovered_new_path)
    }

    fn run_on<T: TreeLike>(
        &mut self,
        code: &Vec<u8>,
        tree: &T,
        exec_reason: ExecutionReason,
        ctx: &Context,
    ) -> Result<(), SubprocessError> {
        let (new_bits, term_sig) = self.exec(code, tree, ctx)?;
        match term_sig {
            ExitReason::Normal(223) => {
                if new_bits.is_some() {
                    //ASAN
                    self.global_state
                        .lock()
                        .expect("RAND_3390206382")
                        .total_found_asan += 1;
                    self.global_state
                        .lock()
                        .expect("RAND_202860771")
                        .last_found_asan = strftime("[%Y-%m-%d] %H:%M:%S", &othertime::now())
                        .expect("RAND_2888070412");
                    let mut file = File::create(format!(
                        "{}/outputs/signaled/ASAN_{:09}_{}",
                        self.work_dir,
                        self.execution_count,
                        thread::current().name().expect("RAND_4086695190")
                    ))
                    .expect("RAND_3096222153");
                    file.write_all(code).expect("RAND_1229707152");
                }
            }
            ExitReason::Normal(_) => {
                if new_bits.is_some() {
                    self.increment_path_counter(&exec_reason);
                }
            }
            ExitReason::Timeouted => {
                self.global_state
                    .lock()
                    .expect("RAND_1706238230")
                    .last_timeout =
                    strftime("[%Y-%m-%d] %H:%M:%S", &othertime::now()).expect("RAND_1894162412");
                let mut file = File::create(format!(
                    "{}/outputs/timeout/{:09}",
                    self.work_dir, self.execution_count
                ))
                .expect("RAND_452993103");
                file.write_all(code).expect("RAND_1541730591");
            }
            ExitReason::Signaled(sig) => {
                if new_bits.is_some() {
                    self.global_state
                        .lock()
                        .expect("RAND_1858328446")
                        .total_found_sig += 1;
                    self.global_state
                        .lock()
                        .expect("RAND_4287051369")
                        .last_found_sig =
                        strftime("[%Y-%m-%d] %H:%M:%S", &othertime::now()).expect("RAND_76391000");
                    let mut file = File::create(format!(
                        "{}/outputs/signaled/{:?}_{:09}",
                        self.work_dir, sig, self.execution_count
                    ))
                    .expect("RAND_3690294970");
                    file.write_all(code).expect("RAND_1481281547");
                }
            }
            ExitReason::Stopped(_sig) => {}
        }
        stdout().flush().expect("RAND_2937475131");
        return Ok(());
    }

    fn increment_path_counter(&mut self, exec_reason: &ExecutionReason) {
        match exec_reason {
            ExecutionReason::Havoc => {
                self.bits_found_by_havoc += 1;
            }
            ExecutionReason::HavocRec => {
                self.bits_found_by_havoc_rec += 1;
            }
            ExecutionReason::Min => {
                self.bits_found_by_min += 1;
            }
            ExecutionReason::MinRec => {
                self.bits_found_by_min_rec += 1;
            }
            ExecutionReason::Splice => {
                self.bits_found_by_splice += 1;
            }
            ExecutionReason::Det => {
                self.bits_found_by_det += 1;
            }
            ExecutionReason::Gen => {
                self.bits_found_by_gen += 1;
            }
        }
    }

    pub fn has_bits<T: TreeLike>(
        &mut self,
        tree: &T,
        bits: &HashSet<usize>,
        exec_reason: ExecutionReason,
        ctx: &Context,
    ) -> Result<bool, SubprocessError> {
        self.run_on_without_dedup(tree, exec_reason, ctx)?;
        let run_bitmap = self.forksrv.get_shared();
        let mut found_all = true;
        for bit in bits.iter() {
            if run_bitmap[*bit] == 0 {
                //TODO: handle edge counts properly
                found_all = false;
            }
        }
        return Ok(found_all);
    }

    pub fn exec_raw<'a>(&'a mut self, code: &[u8]) -> Result<(ExitReason, u32), SubprocessError> {
        self.execution_count += 1;

        let start = Instant::now();

        let exitreason = self.forksrv.run(&code)?;

        let execution_time = start.elapsed().subsec_nanos();

        self.average_executions_per_sec = self.average_executions_per_sec * 0.9
            + ((1.0 / (execution_time as f32)) * 1000000000.0) * 0.1;

        return Ok((exitreason, execution_time));
    }

    fn input_is_known(&mut self, code: &[u8]) -> bool {
        if self.last_tried_inputs.contains(code) {
            return true;
        } else {
            self.last_tried_inputs.insert(code.to_vec());
            if self.last_inputs_ring_buffer.len() == 10000 {
                self.last_tried_inputs.remove(
                    &self
                        .last_inputs_ring_buffer
                        .pop_back()
                        .expect("No entry in last_inputs_ringbuffer"),
                );
            }
            self.last_inputs_ring_buffer.push_front(code.to_vec());
        }
        return false;
    }

    pub fn distinct_inputs_tried(&self) -> usize {
        self.last_tried_inputs.len()
    }

    pub fn target_exec_calls_per_input(&self) -> f64 {
        let distinct = self.distinct_inputs_tried();
        if distinct == 0 {
            0.0
        } else {
            self.execution_count as f64 / distinct as f64
        }
    }

    fn exec<T: TreeLike>(
        &mut self,
        code: &[u8],
        tree_like: &T,
        ctx: &Context,
    ) -> Result<(Option<Vec<usize>>, ExitReason), SubprocessError> {
        let (exitreason, execution_time) = self.exec_raw(&code)?;

        let is_crash = match exitreason {
            ExitReason::Normal(223) => true,
            ExitReason::Signaled(_) => true,
            _ => false,
        };

        let mut final_bits = None;
        if let Some(mut new_bits) = self.candidate_new_bits(is_crash) {
            if exitreason != ExitReason::Timeouted || self.collect_timeout_coverage() {
                //Check for non deterministic bits
                let old_bitmap: Vec<u8> = self.forksrv.get_shared().to_vec();
                self.check_deterministic_behaviour(&old_bitmap, &mut new_bits, &code)?;
                if new_bits.len() > 0 {
                    self.commit_new_bits(is_crash, &new_bits);
                    final_bits = Some(new_bits);
                    let tree = tree_like.to_tree(ctx);
                    self.global_state
                        .lock()
                        .expect("RAND_2835014626")
                        .queue
                        .add(tree, code, old_bitmap, exitreason, execution_time);
                    //println!("Entry added to queue! New bits: {:?}", bits.clone().expect("RAND_2243482569"));
                }
            }
        }
        return Ok((final_bits, exitreason));
    }

    fn collect_timeout_coverage(&self) -> bool {
        matches!(env::var("NAUTILUS_ACCEPT_TIMEOUT_NEW_BITS"), Ok(value) if value == "1")
    }

    fn check_deterministic_behaviour(
        &mut self,
        old_bitmap: &[u8],
        new_bits: &mut Vec<usize>,
        code: &[u8],
    ) -> Result<(), SubprocessError> {
        for _ in 0..5 {
            let (_, _) = self.exec_raw(code)?;
            let run_bitmap = self.forksrv.get_shared();
            for (i, &v) in old_bitmap.iter().enumerate() {
                if run_bitmap[i] != v {
                    println!("found fucky bit {}", i);
                }
            }
            new_bits.retain(|&i| run_bitmap[i] != 0);
        }
        return Ok(());
    }

    pub fn candidate_new_bits(&mut self, is_crash: bool) -> Option<Vec<usize>> {
        let mut res = vec![];
        let run_bitmap = self.forksrv.get_shared();
        let gstate_lock = self.global_state.lock().expect("RAND_2040280272");
        let shared_bitmap = gstate_lock
            .bitmaps
            .get(&is_crash)
            .expect("Bitmap missing! Maybe shared state was not initialized correctly?");

        for (i, elem) in shared_bitmap.iter().enumerate() {
            if (run_bitmap[i] != 0) && (*elem == 0) {
                res.push(i);
            }
        }

        if res.len() > 0 {
            return Some(res);
        }
        return None;
    }

    fn commit_new_bits(&mut self, is_crash: bool, new_bits: &[usize]) {
        let run_bitmap = self.forksrv.get_shared();
        let mut gstate_lock = self.global_state.lock().expect("RAND_2040280272");
        let shared_bitmap = gstate_lock
            .bitmaps
            .get_mut(&is_crash)
            .expect("Bitmap missing! Maybe shared state was not initialized correctly?");

        for &bit in new_bits {
            shared_bitmap[bit] |= run_bitmap[bit];
        }
    }
}

pub fn mutate_materialized_seed(code: &[u8], variant: usize) -> Option<Vec<u8>> {
    let reader = Cursor::new(code.to_vec());
    let mut archive = ZipArchive::new(reader).ok()?;
    let writer = Cursor::new(Vec::new());
    let mut zip_writer = ZipWriter::new(writer);
    let mut mutated_document = false;

    for index in 0..archive.len() {
        let mut file = archive.by_index(index).ok()?;
        let name = file.name().to_string();
        let options = FileOptions::default().compression_method(file.compression());

        if file.is_dir() {
            zip_writer.add_directory(name, options).ok()?;
            continue;
        }

        let mut data = Vec::new();
        file.read_to_end(&mut data).ok()?;

        zip_writer
            .start_file(name.clone(), options.compression_method(CompressionMethod::Deflated))
            .ok()?;

        if name == "word/document.xml" {
            let xml = String::from_utf8(data).ok()?;
            let mutated = mutate_document_xml(&xml, variant);
            mutated_document = mutated_document || mutated != xml;
            zip_writer.write_all(mutated.as_bytes()).ok()?;
        } else {
            zip_writer.write_all(&data).ok()?;
        }
    }

    if !mutated_document {
        return None;
    }

    zip_writer.finish().ok().map(|cursor| cursor.into_inner())
}

fn mutate_document_xml(xml: &str, variant: usize) -> String {
    let mutation_text = format!("seed_mutation_variant_{}", variant);
    let extra_paragraph = format!(
        "<w:p><w:r><w:t>{}</w:t></w:r></w:p>",
        mutation_text
    );

    match variant % 6 {
        0 => insert_before_body_end(xml, &extra_paragraph),
        1 => duplicate_first_block(xml, "<w:p", "</w:p>")
            .unwrap_or_else(|| insert_before_body_end(xml, &extra_paragraph)),
        2 => duplicate_first_block(xml, "<w:tbl", "</w:tbl>")
            .unwrap_or_else(|| insert_before_body_end(xml, &extra_paragraph)),
        3 => replace_first_text(xml, &mutation_text)
            .unwrap_or_else(|| insert_before_body_end(xml, &extra_paragraph)),
        4 => insert_before_body_end(
            xml,
            &format!(
                "{}{}",
                extra_paragraph,
                "<w:p><w:r><w:t>seed_mutation_followup</w:t></w:r></w:p>"
            ),
        ),
        _ => {
            let combined = duplicate_first_block(xml, "<w:p", "</w:p>")
                .unwrap_or_else(|| xml.to_string());
            insert_before_body_end(&combined, &extra_paragraph)
        }
    }
}

fn insert_before_body_end(xml: &str, fragment: &str) -> String {
    if let Some(pos) = xml.rfind("</w:body>") {
        let mut mutated = String::with_capacity(xml.len() + fragment.len());
        mutated.push_str(&xml[..pos]);
        mutated.push_str(fragment);
        mutated.push_str(&xml[pos..]);
        mutated
    } else {
        let mut mutated = xml.to_string();
        mutated.push_str(fragment);
        mutated
    }
}

fn duplicate_first_block(xml: &str, start_tag: &str, end_tag: &str) -> Option<String> {
    let start = xml.find(start_tag)?;
    let end = xml[start..].find(end_tag)? + start + end_tag.len();
    let block = &xml[start..end];
    Some(insert_before_body_end(xml, block))
}

fn replace_first_text(xml: &str, replacement: &str) -> Option<String> {
    let start_tag = "<w:t";
    let start = xml.find(start_tag)?;
    let gt = xml[start..].find('>')? + start;
    let end = xml[gt + 1..].find("</w:t>")? + gt + 1;
    let mut mutated = String::with_capacity(xml.len() + replacement.len());
    mutated.push_str(&xml[..gt + 1]);
    mutated.push_str(replacement);
    mutated.push_str(&xml[end..]);
    Some(mutated)
}
