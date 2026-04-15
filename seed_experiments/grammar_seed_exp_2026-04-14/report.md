# WPS External Seed Experiment

Generated: 2026-04-14 16:04:11

- seed_docx: /home/kzl/wps_fuzz/nautilus_workdirs/wps/test_docx.docx
- duration_seconds: 120
- base_config: /home/kzl/nautilus/config_openxml_sdk_wps_fresh_after_fixes.ron

### baseline

- workdir: /home/kzl/wps_fuzz/seed_experiments/grammar_seed_exp_2026-04-14/baseline_workdir
- execution_count: 196
- execs_per_sec: 22
- chunkstore_trees: 1
- code_coverage: 8.19% (5366/65536)
- new_paths_by_gen: 1
- new_paths_by_mutation_total: 0
- new_paths_total: 1
- queue_files: 3
- timeout_files: 0
- signaled_files: 1

```text
no external seed log
```

### seeded

- workdir: /home/kzl/wps_fuzz/seed_experiments/grammar_seed_exp_2026-04-14/seeded_workdir
- execution_count: 127
- execs_per_sec: 22
- chunkstore_trees: 0
- code_coverage: 8.19% (5366/65536)
- new_paths_by_gen: 2
- new_paths_by_mutation_total: 0
- new_paths_total: 2
- queue_files: 1
- timeout_files: 0
- signaled_files: 0
- external_seed_log: /home/kzl/wps_fuzz/seed_experiments/grammar_seed_exp_2026-04-14/seeded_workdir/outputs/external_seed.log

```text
Loaded external materialized seed /home/kzl/wps_fuzz/nautilus_workdirs/wps/test_docx.docx new_path=true
```

