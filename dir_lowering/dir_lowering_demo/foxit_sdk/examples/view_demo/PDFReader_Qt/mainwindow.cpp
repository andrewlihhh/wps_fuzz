#include <QPainter>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QLibrary>
#include <QTemporaryFile>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "util.h"

#include "common/fs_common.h"

using namespace foxit::common;

static const char* sn = "XQSqpYXftiFIcjaUVzEYXWVFvT86aRH+NpxaYmpzjXt+knIjbaBmMQ==";
static const char* key = "8f3g1kNstBkNAgfCSIczuioWaeXe4+c9+glonrwf6b2LMfDWf0CC92cxiF1M4Re6KUqmkA3+M4O1IRQXmfDg2WnFjr6Fy5eBqpmElth3Kch1UnDYqzIPf4PVOEZvUd51NT/a3Rp2dprVjI9p43m4BRUbHi14Ls5WJrbjiVImPsVCUGD4vLwv5KivNUlruYxBJklnVqASv/Ql2eMYs+QjkW2FF561ojrhWBbkZo+foLp7Dks6zaDFn2bjnFO0QQoD20LdUWuJc38kL+k6tcTaieNizW1FzvFVFDY8NWnaPY7k9nth2Ty5DtIdwMs2WuHrWIgd01SI/FkGZnVjdnmHMrGMNaJeiLJi64khor68iqTH+5C+3Eq48zfcsrsA8Qpe3GDEMHA1aDadhOj+wM1jFvjDQNQR4UQrgVEcS8HhoQECjJv3p/n6zpqSUEHwgoWt3MCZaOButo4qsSUf00/oFCrSaKugMwZsIZPzLilaIvyDYEyVUTDeZmnFRCri9Bnylj/uD+N2EPm2YZnsePp/ORv3FIHlNMl6kOQXmZMKsZMGQcCLc8Xxf9nSaiZzYD1jRgcytPBP0ROfN/rG3EI/1lG+ZCnax9oadtpEbEGjUvja70YRE14iVwR8QIRFVpqJVZTCMcmuFpMFfC2CKcYQORBygs+6bnobAli9qIzIoXvbk2gYI5X2WhkZHRwIrOXwk3fW9nFKjCXVpyYSFSdOrkRQdAT5u+6eEIaSD47GmIHoaDDlHH1RF6BusVsCqvfAfG8qIYJNes2q/c5nheCmBThdWjl4MKwxPH7K306MaekAKFPJAwKhBTES9nZrsseQLQ9v8WNGTZyBwJucEHMCol+Vk3lf+PpKEaD6G8TT7n36V43XJ/N09APgDcGxGB4rAAeinCbANyaYOQtZ0jb+5Jb/NKQ2grdA9KoEvafLE09J4VSloQPQOCCbIwhrvwZO0guWaEjXbiN4UPzSOnyQK7lZfFNmAIgjZtAqzIL8yeGes0I/CCI4CiRKz+pFh313WLtbKi3acqO7GrlFH9g652bkeITPg06fhkqSVjf7iHv+ZpZYXWz+K0FiTUaCinPzNKOCWbYrqNcWaM1Y6bR/uoUJkSUMoODHZ3csWhOz7VqUVZc9M4U6Qg0+0wck3w+ZbdEyVSlWnAPXkphg4UYMrMrUFUzHYSjORTdXoLYMveoIbWMhubtugl0DqD8hOEWqaGYYlJo2N2WU54mYEIaoZ8wfpWsMVOfPFyi5j754lngonq5vf36inXn3xRO5CkYFrzXKJ3n2DYiSrVV0ll/5WTkR3F/lEby4CP81UkVubm4GrvH7fBnhQuWgV9GlZbZhaCWl6FC1dnabn+sNwvh3iEP/2oWqi2013gtQQlSSFE5mCg+pCr6zFEAUTNHBqQZrXyMdIJ9tNimbX551HE+bKp5Eog1wHWP1k3orEjQUwm+R";

QColor kViewAreaBackgroundColor = QColor(0x60, 0x60, 0x60);

#define VSCROLLBAR_PAGESTEP_DEFAULT 50
#define VSCROLLBAR_SINGLESTEP_DEFAULT 20
#define HSCROLLBAR_PAGESTEP_DEFAULT 50
#define HSCROLLBAR_SINGLESTEP_DEFAULT 50

#define SLIDERZOOM_RANGE_MIN 25
#define SLIDERZOOM_RANGE_MAX 175

#define ZOOMFACTOR_FLOAT_MIN 0.25
#define ZOOMFACTOR_FLOAT_MAX 64.0
#define ZOOMFACTOR_FLOAT_DELTA 0.2

#pragma pack(push,1)
typedef struct BITMAPFILEHEADER
{
    u_int16_t type;
    u_int32_t size;
    u_int16_t reserved_1;
    u_int16_t reserved_2;
    u_int32_t off_bits;
}BITMAPFILEHEADER;

typedef struct BITMAPINFOHEADER
{
    u_int32_t size;
    u_int32_t width;
    u_int32_t height;
    u_int16_t planes;
    u_int16_t bit_count;
    u_int32_t compression;
    u_int32_t size_image;
    u_int32_t x_pels_per_meter;
    u_int32_t y_pels_per_meter;
    u_int32_t clr_used;
    u_int32_t clr_important;
}BITMAPINFODEADER;
#pragma pack(pop)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , sdk_initialized_(false)
    , current_pdf_doc_(nullptr)
    , current_page_count_(0)
    , current_page_index_(-1)
    , current_zoom_factor_(1.0)
    , current_checked_zoom_btn_type_(MainWindow::e_ZoomBtnOther)
    , current_pdf_file_("")
    , current_pdf_password_("")
{
    ui_->setupUi(this);

    ErrorCode error_code = Library::Initialize(sn, key);
    if (error_code != foxit::e_ErrSuccess) {
      QString msgbox_title = "Error";
      QString message = GetErrorCodeMessage(error_code);
      QMessageBox::about(this, msgbox_title, message );
      return;
    }
    sdk_initialized_ = true;

    MyXFAAppProviderCallback* xfa_callback = new MyXFAAppProviderCallback(this);
    if (xfa_callback) {
        try {
            Library::RegisterXFAAppProviderCallback(xfa_callback);
        } catch (foxit::Exception &) {
            delete xfa_callback;
            xfa_callback = NULL;
        }
    }

    setWindowTitle("PDFReader_Qt");
    // Forbid changing size of main window.
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    // Initialize view area and scroll bars.
    initViewArea() ;

    // Initalize zoom related slider and lineEdit.
    ui_->hSliderZoom->setRange(SLIDERZOOM_RANGE_MIN, SLIDERZOOM_RANGE_MAX);
    ui_->hSliderZoom->setSingleStep(10);
    ui_->hSliderZoom->setPageStep(10);

    ui_->lineEditZoomNum->setReadOnly(true);
    current_zoom_factor_ = 1.0;

    updatePageRelatedUIWidget();
    enableZoomRelatedUIWidget(false);
    updateZoomRelatedBtnCheckedStatus(false);

    ui_->pushBtnOpenFile->setEnabled(true);
    ui_->pushBtnCloseFile->setEnabled(false);
    ui_->pushBtnPrint->setEnabled(false);



    ui_->centralWidget->installEventFilter(this);
    ui_->hScrollBarViewArea->installEventFilter(this);
    ui_->hSliderZoom->installEventFilter(this);
    ui_->labelViewArea->installEventFilter(this);
    ui_->lineEditPageNum->installEventFilter(this);
    ui_->lineEditZoomNum->installEventFilter(this);
    ui_->menuBar->installEventFilter(this);
    ui_->pushBtnCloseFile->installEventFilter(this);
    ui_->pushBtnGoToFirstPage->installEventFilter(this);
    ui_->pushBtnGoToLastPage->installEventFilter(this);
    ui_->pushBtnGoToNextPage->installEventFilter(this);
    ui_->pushBtnGoToPrevPage->installEventFilter(this);
    ui_->pushBtnOpenFile->installEventFilter(this);
    ui_->pushBtnPrint->installEventFilter(this);
    ui_->pushBtnZoomActualSize->installEventFilter(this);
    ui_->pushBtnZoomFitPage->installEventFilter(this);
    ui_->pushBtnZoomFitWidth->installEventFilter(this);
    ui_->pushBtnZoomIn->installEventFilter(this);
    ui_->pushBtnZoomOut->installEventFilter(this);
    ui_->vScrollBarViewArea->installEventFilter(this);
    this->installEventFilter(this);


}

MainWindow::~MainWindow()
{
    wrong_page_index_set_.clear();
    if (current_pdf_doc_) {
        delete current_pdf_doc_;
        current_pdf_doc_ = NULL;
    }

    if (sdk_initialized_) {
        Library::Release();
        sdk_initialized_ = false;
    }
    delete ui_;
}

bool MainWindow::isSDKInitialized() {
    return sdk_initialized_;
}


void MainWindow::initViewArea() {
    // Refresh the background color.
    QRect viewarea_rect = ui_->labelViewArea->geometry();
    QPixmap temp_pixmap(viewarea_rect.width(), viewarea_rect.height());
    temp_pixmap.fill(kViewAreaBackgroundColor);
    ui_->labelViewArea->setPixmap(temp_pixmap);

    // Initialize vertical scroll bar for view area.
    ui_->vScrollBarViewArea->setVisible(true);
    ui_->vScrollBarViewArea->setEnabled(false);
    ui_->vScrollBarViewArea->setRange(0, 0) ;
    ui_->vScrollBarViewArea->setPageStep(VSCROLLBAR_PAGESTEP_DEFAULT);
    ui_->vScrollBarViewArea->setSingleStep(VSCROLLBAR_SINGLESTEP_DEFAULT);

    // Initialize horizonal scroll bar for view area.
    ui_->hScrollBarViewArea->setVisible(true);
    ui_->hScrollBarViewArea->setEnabled(false);
    ui_->hScrollBarViewArea->setRange(0, 0) ;
    ui_->hScrollBarViewArea->setPageStep(HSCROLLBAR_PAGESTEP_DEFAULT);
    ui_->hScrollBarViewArea->setSingleStep(HSCROLLBAR_SINGLESTEP_DEFAULT);
}

void MainWindow::updatePageRelatedUIWidget() {
    if (current_page_count_<=0 ||
        current_page_index_ < 0 || current_page_index_>=current_page_count_) {
        ui_->pushBtnGoToFirstPage->setEnabled(false);
        ui_->pushBtnGoToPrevPage->setEnabled(false);
        ui_->pushBtnGoToNextPage->setEnabled(false);
        ui_->pushBtnGoToLastPage->setEnabled(false);
        ui_->lineEditPageNum->setEnabled(false);
        ui_->lineEditPageNum->setText("");
        return ;
    }

    bool enable_btn_firstpage = false;
    bool enable_btn_prevpage = false;
    bool enable_btn_nextpage = false;
    bool enable_btn_lastpage = false;
    if (current_page_count_>1) {
        if (0 == current_page_index_) {
            enable_btn_nextpage = true;
            enable_btn_lastpage = true;
        } else if (current_page_index_ == current_page_count_-1) {
            enable_btn_firstpage = true;
            enable_btn_prevpage = true;
        } else {
            enable_btn_firstpage = true;
            enable_btn_prevpage = true;
            enable_btn_nextpage = true;
            enable_btn_lastpage = true;
        }
    }
    ui_->pushBtnGoToFirstPage->setEnabled(enable_btn_firstpage);
    ui_->pushBtnGoToPrevPage->setEnabled(enable_btn_prevpage);
    ui_->pushBtnGoToNextPage->setEnabled(enable_btn_nextpage);
    ui_->pushBtnGoToLastPage->setEnabled(enable_btn_lastpage);

    QString lineedit_text_pagenum = "";
    if (current_page_count_>0) {
        lineedit_text_pagenum = QString::number(current_page_index_+1) + "/" + QString::number(current_page_count_);
    }
    ui_->lineEditPageNum->setEnabled(lineedit_text_pagenum.isEmpty()?false:true);
    ui_->lineEditPageNum->setText(lineedit_text_pagenum);
}

void MainWindow::enableZoomRelatedUIWidget(bool to_enable) {
    ui_->hSliderZoom->setEnabled(to_enable);
    ui_->lineEditZoomNum->setEnabled(to_enable);

    ui_->pushBtnZoomActualSize->setEnabled(to_enable);
    ui_->pushBtnZoomActualSize->setCheckable(true);

    ui_->pushBtnZoomFitPage->setEnabled(to_enable);
    ui_->pushBtnZoomFitPage->setCheckable(true);

    ui_->pushBtnZoomFitWidth->setEnabled(to_enable);
    ui_->pushBtnZoomFitWidth->setCheckable(true);

    if (false == to_enable) {
        ui_->pushBtnZoomActualSize->setChecked(false);
        ui_->pushBtnZoomFitPage->setChecked(false);
        ui_->pushBtnZoomFitWidth->setChecked(false);
    }

    ui_->pushBtnZoomIn->setEnabled(to_enable);
    ui_->pushBtnZoomOut->setEnabled(to_enable);
}

void MainWindow::on_pushBtnOpenFile_clicked()
{
    QString dialog_title = QString::fromUtf8( "Open" ) ;
    QString file_ext_filter = QString::fromUtf8( "pdf file(*.pdf)" ) ;
    QString input_pdf_path = QFileDialog::getOpenFileName( this, dialog_title, "", file_ext_filter ) ;
    current_pdf_file_ = "";
    current_pdf_password_ = "";

    if ( true == input_pdf_path.isEmpty() ) {
        QString msgbox_title = "Info";
        QString message = "No PDF file is chosen to be opened.";
        QMessageBox::about(this, msgbox_title, message );
        return;
    }

    if (current_pdf_doc_)
        on_pushBtnCloseFile_clicked();

    current_pdf_doc_ = new PDFDoc(input_pdf_path.toLocal8Bit());
    if (!current_pdf_doc_) {
        QString msgbox_title = "Error";
        QString message = "Fail to open PDF file \"" + input_pdf_path + "\".";
        QMessageBox::about(this, msgbox_title, message ) ;
        return ;
    }

    ErrorCode error_code = current_pdf_doc_->Load();
    while (foxit::e_ErrPassword == error_code) {
        QString dlg_title = "Password";
        QFileInfo file_info(input_pdf_path);
        QString label =  "'" + file_info.fileName() + "'" + "is password protected. \r\nPlease enter a password to open this document.\r\n\r\nEnter password:";
        bool is_ok = false;
        QString input_password = QInputDialog::getText(this, dlg_title, label, QLineEdit::Password, "", &is_ok);
        if (is_ok) {
            current_pdf_password_ = input_password;
            std::wstring password_wstr = input_password.toStdWString();
            error_code = current_pdf_doc_->LoadW(password_wstr.c_str());
            if (foxit::e_ErrPassword == error_code) {
                QString msgbox_title = "Error";
                QString message = "Invalid password. Please enter password again.";
                QMessageBox::about(this, msgbox_title, message);
            }
        } else {
            return;
        }

    }
    if (error_code != foxit::e_ErrSuccess) {
        delete current_pdf_doc_;
        current_pdf_doc_ = nullptr;

        QString msgbox_title = "Error";
        QString message = GetErrorCodeMessage(error_code);
        QMessageBox::about(this, msgbox_title, message ) ;
        return ;
    }

    if (current_pdf_doc_->IsXFA()) {
        if (!Library::HasModuleLicenseRight(common::e_ModuleNameXFA)) {
            on_pushBtnCloseFile_clicked();
            QString msgbox_title = "Error";
            QString message = "You are not authorized to use \"XFA\" add-on module, please contact us for upgrading your license.";
            QMessageBox::about(this, msgbox_title, message ) ;
            return ;
        }
    }

    current_page_count_ = current_pdf_doc_->GetPageCount();
    current_pdf_file_ = input_pdf_path;
    if ( current_page_count_ > 0 )
    {
        current_page_index_ = 0 ;
        enableZoomRelatedUIWidget( true ) ;
        ui_->pushBtnOpenFile->setEnabled(false);
        ui_->pushBtnCloseFile->setEnabled(true);
        ui_->pushBtnPrint->setEnabled(true);

        updateZoomRelatedUIWidget(current_zoom_factor_) ;
        updateZoomRelatedBtnCheckedStatus(true);

        int render_offset_x = 0;
        int render_offset_y = 0;

        // In some PDF files, some PDF pages are wrong and cannot be retrieved.
        // In this case, we need to show the next page.
        PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
        while (page.IsEmpty() && (current_page_index_+1<current_page_count_)) {
            addWrongPageIndexToList(current_page_index_);
            current_page_index_ += 1;
            page = current_pdf_doc_->GetPage(current_page_index_);
        }
        updatePageRelatedUIWidget();
        if (page.IsEmpty()) return;
        showPage(page, render_offset_x, render_offset_y) ;
        updateViewAreaScrollbars(render_offset_x, render_offset_y) ;
    } else {
        QString msgbox_title = "Alert";
        QString message = "No page in current PDF file.";
        QMessageBox::about(this, msgbox_title, message ) ;
        return ;
    }

}

void MainWindow::on_pushBtnCloseFile_clicked()
{
    if (current_pdf_doc_) {
        delete current_pdf_doc_;
        current_pdf_doc_ = NULL;
    }

    wrong_page_index_set_.clear();
    current_page_count_ = 0;
    current_page_index_ = -1;
    updatePageRelatedUIWidget();
    current_zoom_factor_ = 1.0;
    enableZoomRelatedUIWidget(false);
    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnOther;
    updateZoomRelatedBtnCheckedStatus(false);
    ui_->pushBtnOpenFile->setEnabled(true);
    ui_->pushBtnCloseFile->setEnabled(false);
    ui_->pushBtnPrint->setEnabled(false);

    initViewArea();
}

float MainWindow::getZoomFactorFromSliderValue(int slider_value) {
    int slider_min_value = ui_->hSliderZoom->minimum();
    int slider_max_value = ui_->hSliderZoom->maximum();

    int slider_middle_value = (slider_min_value + slider_max_value) / 2;

    if (slider_value<=slider_middle_value) {
        return ((float)slider_value) / 100.0;
    } else if (slider_value == slider_max_value) {
        return ZOOMFACTOR_FLOAT_MAX;
    } else {
        return ((float)(slider_value - slider_middle_value) / (float)(slider_max_value - slider_middle_value)) * (ZOOMFACTOR_FLOAT_MAX-ZOOMFACTOR_FLOAT_MIN) + 1.0;
    }
}

int MainWindow::getSliderValueFromZoomFactor(float zoom_factor) {

    if ( zoom_factor<1.0 || (zoom_factor - 1.0)<1e-6) {
        return (int)(zoom_factor * 100);
    } else if (qAbs(zoom_factor - ZOOMFACTOR_FLOAT_MAX)<1e-6) {
        return ui_->hSliderZoom->maximum();
    } else {
        int slider_min_value = ui_->hSliderZoom->minimum();
        int slider_max_value = ui_->hSliderZoom->maximum();
        int slider_middle_value = (slider_min_value + slider_max_value) / 2;

        return (zoom_factor-1.0) / (ZOOMFACTOR_FLOAT_MAX-1.0) * (slider_max_value - slider_middle_value) + slider_middle_value;
    }
}

void MainWindow::updateZoomRelatedUIWidget(float new_factor, bool update_slider_value/* = true*/) {

    if (new_factor > ZOOMFACTOR_FLOAT_MIN) {
        ui_->pushBtnZoomOut->setEnabled(true);
    } else {
        ui_->pushBtnZoomOut->setEnabled(false);
    }
    if (new_factor < ZOOMFACTOR_FLOAT_MAX) {
        ui_->pushBtnZoomIn->setEnabled(true);
    } else {
        ui_->pushBtnZoomIn->setEnabled(false);
    }

    QString zoom_factor_str = QString::number( (int)(new_factor*100) ) ;
    ui_->lineEditZoomNum->setText( zoom_factor_str+"%" ) ;

    if (update_slider_value) {
        QObject::disconnect(ui_->hSliderZoom, SIGNAL(valueChanged(int)), this, SLOT(on_hSliderZoom_valueChanged(int))) ;
        int new_slider_value = getSliderValueFromZoomFactor(new_factor);
        ui_->hSliderZoom->setValue( new_slider_value ) ;
        QObject::connect(ui_->hSliderZoom, SIGNAL(valueChanged(int)), this, SLOT(on_hSliderZoom_valueChanged(int))) ;
    }
}

void MainWindow::updateViewAreaScrollbars(int render_offset_x, int render_offset_y )
{
    if ( !current_pdf_doc_ || current_pdf_doc_->IsEmpty() ||
         !ui_->hScrollBarViewArea || !ui_->vScrollBarViewArea )
        return ;

    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) return;
    float pdf_page_width = page.GetWidth();
    float pdf_page_height = page.GetHeight();

    float page_render_width = pdf_page_width * current_zoom_factor_ ;
    float page_render_height = pdf_page_height * current_zoom_factor_ ;

    float total_width = page_render_width;
    float total_height = page_render_height;

    QRect viewarea_rect = ui_->labelViewArea->geometry() ;
    float viewarea_width = (float)( viewarea_rect.width() ) ;
    float viewarea_height = (float)( viewarea_rect.height() ) ;

    // Update horizonal scroll bar
    QObject::disconnect( ui_-> hScrollBarViewArea, SIGNAL(valueChanged(int)), this, SLOT(on_hScrollBarViewArea_valueChanged(int)) ) ;
    if ( total_width > viewarea_width ) {
        ui_->hScrollBarViewArea->setEnabled(true) ;
        ui_->hScrollBarViewArea->setRange(0, total_width-viewarea_width) ;
        ui_->hScrollBarViewArea->setValue(render_offset_x);
    } else {
        ui_->hScrollBarViewArea->setEnabled(false) ;
        ui_->hScrollBarViewArea->setRange(0, 0) ;
    }
    QObject::connect( ui_-> hScrollBarViewArea, SIGNAL(valueChanged(int)), this, SLOT(on_hScrollBarViewArea_valueChanged(int)) ) ;

    // Update vertical scroll bar
    QObject::disconnect( ui_-> vScrollBarViewArea, SIGNAL(valueChanged(int)), this, SLOT(on_vScrollBarViewArea_valueChanged(int)) ) ;
    if ( total_height > viewarea_height ) {
        int page_delta = 1;
        if (total_height>viewarea_height)
            page_delta = (int)(total_height-viewarea_height + 0.5);
        ui_->vScrollBarViewArea->setEnabled(true);
        int wrong_page_count = wrong_page_index_set_.count();
        ui_->vScrollBarViewArea->setRange( 0, page_delta * (current_page_count_-wrong_page_count) ) ;
        int passed_delta_count = current_page_index_;
        QSetIterator<int> set_iterator(wrong_page_index_set_);
        while(set_iterator.hasNext()) {
            int temp = set_iterator.next();
            if (temp < current_page_index_)
                passed_delta_count--;
        }
        ui_->vScrollBarViewArea->setValue(page_delta*passed_delta_count+render_offset_y);
        ui_->vScrollBarViewArea->setSingleStep(VSCROLLBAR_SINGLESTEP_DEFAULT);
        ui_->vScrollBarViewArea->setPageStep(VSCROLLBAR_PAGESTEP_DEFAULT);
    } else {
        if ( current_page_count_ == 1 ) {
            ui_->vScrollBarViewArea->setEnabled( false ) ;
            ui_->vScrollBarViewArea->setRange(0, 0);
        } else {
            ui_->vScrollBarViewArea->setEnabled( true ) ;
            int wrong_page_count = wrong_page_index_set_.count();
            ui_->vScrollBarViewArea->setRange( 0, (current_page_count_-wrong_page_count)-1 ) ;
            ui_->vScrollBarViewArea->setSingleStep(1);
            ui_->vScrollBarViewArea->setPageStep(1);
            int passed_page_count = current_page_index_;
            QSetIterator<int> set_iterator(wrong_page_index_set_);
            while(set_iterator.hasNext()) {
                int temp = set_iterator.next();
                if (temp < current_page_index_)
                    passed_page_count--;
            }
            ui_->vScrollBarViewArea->setValue(passed_page_count);
        }

    }
    QObject::connect( ui_->vScrollBarViewArea, SIGNAL(valueChanged(int)), this, SLOT(on_vScrollBarViewArea_valueChanged(int)) ) ;
}

bool MainWindow::showPage( PDFPage& page, int offset_x, int offset_y )
{
    if (!ui_->labelViewArea || page.IsEmpty())
        return false ;

    if ( false == page.IsParsed() ) {
        Progressive progressive = page.StartParse(foxit::pdf::PDFPage::e_ParsePageNormal, NULL, false);
        while ( progressive.GetRateOfProgress () != 100 ) {
           progressive.Continue ();
        }
    }

    // Create a bitmap (Foxit PDF SDK) with the same size of view area.
    QRect viewarea_rect = ui_->labelViewArea->geometry() ;
    Bitmap sdk_bitmap(viewarea_rect.width(), viewarea_rect.height(), foxit::common::Bitmap::e_DIBRgb, NULL, 0);

    // Prepare QRect of the bitmap.
    QRect bmp_qrect(0, 0, viewarea_rect.width(), viewarea_rect.height()) ;
    QPoint bmp_centre_point = bmp_qrect.center() ;

    // Get PDF page size.
    float pdf_page_width = page.GetWidth();
    float pdf_page_height = page.GetHeight();
    // Calculate actual page size for rendering.
    int page_render_width = (int)( pdf_page_width * current_zoom_factor_ ) ;
    int page_render_height = (int)( pdf_page_height * current_zoom_factor_) ;

    // Prepare QRect for actual rendering size.
    bool is_render_width_bigger = false ;
    bool is_render_height_bigger = false ;
    QRect page_render_qrect(0,0, page_render_width, page_render_height) ;
    page_render_qrect.moveCenter( bmp_centre_point ) ;
    if ( page_render_qrect.width() >= bmp_qrect.width() ) {
        is_render_width_bigger = true ;
        page_render_qrect.moveLeft( bmp_qrect.left() - offset_x ) ;
    }

    if ( page_render_qrect.height() >= bmp_qrect.height() ) {
        is_render_height_bigger = true ;
        page_render_qrect.moveTop( bmp_qrect.top() - offset_y ) ;
    }

    // Fill background color of viewarea in the bitmap.
    RectI temp_rect(0, 0, (int)viewarea_rect.width(), (int)viewarea_rect.height());
    sdk_bitmap.FillRect(0xFF606060, &temp_rect);

    // Fill background color of page in the bitmap
    temp_rect.left = page_render_qrect.left() ;
    temp_rect.top = page_render_qrect.top() ;
    temp_rect.right = temp_rect.left + page_render_qrect.width() ;
    temp_rect.bottom = temp_rect.top + page_render_qrect.height() ;
    if ( is_render_width_bigger )
        temp_rect.left = 0 ;
    if ( is_render_height_bigger )
        temp_rect.top =  0 ;
    sdk_bitmap.FillRect(0xFFffffff, &temp_rect);

    // Now, render PDF page to the bimtap.
    Renderer render(sdk_bitmap, false);

    //Get display matrix for PDF page.
    temp_rect.left = page_render_qrect.left() ;
    temp_rect.top = page_render_qrect.top() ;
    Rotation render_rotation = foxit::common::e_Rotation0;
    Matrix matrix = page.GetDisplayMatrix(temp_rect.left, temp_rect.top, temp_rect.right-temp_rect.left, temp_rect.bottom-temp_rect.top, render_rotation);

    temp_rect.left = bmp_qrect.left() ;
    temp_rect.top = bmp_qrect.top() ;
    temp_rect.right = temp_rect.left + bmp_qrect.width() ;
    temp_rect.bottom = temp_rect.top + bmp_qrect.height() ;
    render.SetClipRect(&temp_rect );

    Progressive progressive = render.StartRender(page, matrix, NULL);
    while ( progressive.GetRateOfProgress () != 100 ) {
       progressive.Continue();
    }

    // Change bitmap to QPixmap and set to view area.
    int p_size =  sdk_bitmap.GetBpp();
    if(p_size == 8)
        p_size = 256;
    else if(p_size == 1)
        p_size = 2;
    else
        p_size = 0;
    long bitmap_bit_size = sdk_bitmap.GetPitch()*sdk_bitmap.GetHeight() + p_size*4;

    BITMAPINFOHEADER bitmap_info_header ;
    bitmap_info_header.size = sizeof(BITMAPINFOHEADER) ;
    bitmap_info_header.width = sdk_bitmap.GetWidth();
    bitmap_info_header.height = -sdk_bitmap.GetHeight();
    bitmap_info_header.planes = 1;
    bitmap_info_header.bit_count = sdk_bitmap.GetBpp();
    bitmap_info_header.compression = 0;
    bitmap_info_header.size_image = bitmap_bit_size;
    bitmap_info_header.x_pels_per_meter = 0;
    bitmap_info_header.y_pels_per_meter = 0;
    bitmap_info_header.clr_used = 0;
    bitmap_info_header.clr_important = 0 ;

    BITMAPFILEHEADER bitmap_file_header;
    bitmap_file_header.type = 0x4d42 ;
    bitmap_file_header.size = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + bitmap_bit_size + p_size*4;
    bitmap_file_header.reserved_1 = 0 ;
    bitmap_file_header.reserved_2 = 0 ;
    bitmap_file_header.off_bits = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + p_size*4;

    QByteArray bitmap_full_data ;
    bitmap_full_data.append((char*)&(bitmap_file_header.type), sizeof(u_int16_t));
    bitmap_full_data.append((char*)&(bitmap_file_header.size), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_file_header.reserved_1), sizeof(u_int16_t));
    bitmap_full_data.append((char*)&(bitmap_file_header.reserved_2), sizeof(u_int16_t));
    bitmap_full_data.append((char*)&(bitmap_file_header.off_bits), sizeof(u_int32_t));

    bitmap_full_data.append((char*)&(bitmap_info_header.size), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.width), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.height), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.planes), sizeof(u_int16_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.bit_count), sizeof(u_int16_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.compression), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.size_image), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.x_pels_per_meter), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.y_pels_per_meter), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.clr_used), sizeof(u_int32_t));
    bitmap_full_data.append((char*)&(bitmap_info_header.clr_important), sizeof(u_int32_t));

    const uint8* sdk_bitmap_buffer = sdk_bitmap.GetBuffer();
    char* bits_data = (char*)malloc( sizeof(char)*bitmap_bit_size ) ;
    memcpy( bits_data, sdk_bitmap_buffer, bitmap_info_header.size_image ) ;
    bitmap_full_data.append((char*)bits_data, bitmap_info_header.size_image);

    QPixmap result_pixmap;
    result_pixmap.loadFromData( bitmap_full_data ) ;
    ui_->labelViewArea->setPixmap( result_pixmap ) ;
    ui_->labelViewArea->update() ;

    bitmap_full_data.clear() ;

    free( bits_data ) ;
    bits_data = NULL ;

    return true ;
}

void MainWindow::on_vScrollBarViewArea_valueChanged(int value)
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty())
        return ;

    PDFPage current_page =  current_pdf_doc_->GetPage(current_page_index_) ;
    if (current_page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return;
    }
    float pdf_page_height = current_page.GetHeight();
    float page_render_height = pdf_page_height * current_zoom_factor_ ;

    QRect viewarea_rect = ui_->labelViewArea->geometry() ;
    float viewarea_height = (float)( viewarea_rect.height() ) ;

    int page_delta = 1;
    if (page_render_height > viewarea_height)
        page_delta = (int)(page_render_height - viewarea_height + 0.5);
    int new_page_index = value / page_delta ;

    if ( new_page_index >= current_page_count_ )
        new_page_index = current_page_count_ - 1 ;

    // In some PDF files, some PDF pages are wrong and cannot be retrieved.
    // In this case, we try to show the next valid page instead.
    PDFPage new_page = current_pdf_doc_->GetPage(new_page_index);
    while (new_page.IsEmpty() && (new_page_index+1<current_page_count_)) {
        addWrongPageIndexToList(new_page_index);
        new_page_index += 1;
        new_page = current_pdf_doc_->GetPage(new_page_index);
    }
    if (new_page.IsEmpty()) return;
    current_page_index_ = new_page_index ;

    int offset_x = 0 ;
    if ( ui_->hScrollBarViewArea->isEnabled() )
        offset_x = ui_->hScrollBarViewArea->value();
    int passed_delta_count = current_page_index_;
    QSetIterator<int> set_iterator(wrong_page_index_set_);
    while(set_iterator.hasNext()) {
        int temp = set_iterator.next();
        if (temp < current_page_index_)
            passed_delta_count--;
    }
    int offset_y = value - ( passed_delta_count * page_delta ) ;
    showPage(new_page, offset_x, offset_y ) ;
    updatePageRelatedUIWidget() ;

}

void MainWindow::on_hScrollBarViewArea_valueChanged(int value)
{
    if(!current_pdf_doc_ || current_pdf_doc_->IsEmpty() )
        return;

    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return ;
    }
    float pdf_page_height = page.GetHeight();
    float page_render_height = pdf_page_height * current_zoom_factor_ ;
    QRect viewarea_rect = ui_->labelViewArea->geometry() ;
    float viewarea_height = (float)( viewarea_rect.height() ) ;

    int offset_x = value ;
    int offset_y = 0 ;
    if ( ui_->vScrollBarViewArea->isEnabled() && (page_render_height-viewarea_height) > 0) {
        int passed_delta_count = current_page_index_;
        QSetIterator<int> set_iterator(wrong_page_index_set_);
        while(set_iterator.hasNext()) {
            int temp = set_iterator.next();
            if (temp < current_page_index_)
                passed_delta_count--;
        }
        offset_y = ui_->vScrollBarViewArea->value() - ( passed_delta_count * (page_render_height-viewarea_height) ) ;
    }
    showPage(page, offset_x, offset_y ) ;
}

void MainWindow::wheelEvent( QWheelEvent* pEvent ) {

    if ( ui_->vScrollBarViewArea->isVisible() && ui_->vScrollBarViewArea->isActiveWindow() ) {
        QPoint event_global_pos = pEvent->globalPos() ;
        QRect viewarea_rect = ui_->labelViewArea->geometry() ;
        if ( viewarea_rect.contains(event_global_pos, true) ) {
            if ( pEvent->orientation() == Qt::Vertical ) {
                int event_delta = pEvent->delta() ;
                int vscrollbar_value = ui_->vScrollBarViewArea->value() ;
                vscrollbar_value -= event_delta ;

                ui_->vScrollBarViewArea->setValue( vscrollbar_value ) ;
            }
        }
    }
    pEvent->accept() ;
}

void MainWindow::on_pushBtnGoToFirstPage_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    if (0 == current_page_index_)
        return;

    int new_page_index = 0;
    // In some PDF files, the fist page is wrong and cannot be retrieved.
    // In this case, we show the next valid page instead.
    PDFPage page = current_pdf_doc_->GetPage(new_page_index);
    while (page.IsEmpty() && (new_page_index+1<current_page_index_)) {
        addWrongPageIndexToList(new_page_index);
        new_page_index += 1;
        page = current_pdf_doc_->GetPage(new_page_index);
    }
    if (page.IsEmpty()) return;
    if (current_page_index_ == new_page_index) return;
    current_page_index_ = new_page_index;
    int render_offset_x = 0;
    int render_offset_y = 0;
    showPage(page, render_offset_x, render_offset_y);
    updatePageRelatedUIWidget();
    updateViewAreaScrollbars(render_offset_x, render_offset_y);

	QWidget* focus_widget = this->focusWidget();
    if (focus_widget && focus_widget->objectName() == "lineEditPageNum")
      focus_widget->clearFocus();
}

void MainWindow::on_pushBtnGoToPrevPage_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    if (0 == current_page_index_)
        return;

    int new_page_index = current_page_index_ - 1;
    // In some PDF files, some pages are wrong and cannot be retrieved.
    // In this case, we show the previous valid page instead.
    PDFPage page = current_pdf_doc_->GetPage(new_page_index);
    while (page.IsEmpty() && (new_page_index-1>0)) {
        addWrongPageIndexToList(new_page_index);
        new_page_index -= 1;
        page = current_pdf_doc_->GetPage(new_page_index);
    }
    if (page.IsEmpty()) return ;

    current_page_index_ = new_page_index;
    int render_offset_x = 0;
    int render_offset_y = 0;
    showPage(page, render_offset_x, render_offset_y);
    updatePageRelatedUIWidget();
    updateViewAreaScrollbars(render_offset_x, render_offset_y);
}

void MainWindow::on_pushBtnGoToNextPage_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    if (current_page_count_-1 == current_page_index_)
        return;

    int new_page_index = current_page_index_ + 1;
    // In some PDF files, some pages are wrong and cannot be retrieved.
    // In this case, we show the next valid page instead.
    PDFPage page = current_pdf_doc_->GetPage(new_page_index);
    while (page.IsEmpty() && (new_page_index+1<current_page_count_)) {
        addWrongPageIndexToList(new_page_index);
        new_page_index += 1;
        page = current_pdf_doc_->GetPage(new_page_index);
    }
    if (page.IsEmpty()) return ;

    current_page_index_ = new_page_index;
    int render_offset_x = 0;
    int render_offset_y = 0;
    showPage(page, render_offset_x, render_offset_y);
    updatePageRelatedUIWidget();
    updateViewAreaScrollbars(render_offset_x, render_offset_y);
}

void MainWindow::on_pushBtnGoToLastPage_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    if (current_page_count_-1 == current_page_index_)
        return ;

    int new_page_index = current_page_count_ - 1;
    // In some PDF files, the last page is wrong and cannot be retrieved.
    // In this case, we show the previous valid page instead.
    PDFPage page = current_pdf_doc_->GetPage(new_page_index);
    while (page.IsEmpty() && (new_page_index-1>current_page_index_)) {
        addWrongPageIndexToList(new_page_index);
        new_page_index -= 1;
        page = current_pdf_doc_->GetPage(new_page_index);
    }
    if (page.IsEmpty()) return ;
    if (new_page_index == current_page_index_) return ;

    current_page_index_ = new_page_index;
    int render_offset_x = 0;
    int render_offset_y = 0;
    showPage(page, render_offset_x, render_offset_y);
    updatePageRelatedUIWidget();
    updateViewAreaScrollbars(render_offset_x, render_offset_y);
}

void MainWindow::on_lineEditPageNum_returnPressed()
{
    ui_->lineEditPageNum->clearFocus();
}

void MainWindow::focusOutLineEditPageNum()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    int render_offset_x = 0;
    int render_offset_y = 0;
    QString lineedit_text = ui_->lineEditPageNum->text() ;
    if (false == lineedit_text.isEmpty()) {
        QStringList input_text_list = lineedit_text.split( "/" ) ;
        if (input_text_list.size() > 0) {
            QChar first_char = input_text_list.at(0).at(0);
            if (first_char.isDigit()) {
                int input_page_number = input_text_list.at(0).toInt();
                if (input_page_number > 0 && input_page_number <= current_page_count_) {
                    if (current_page_index_ != input_page_number-1) {
                        current_page_index_ = input_page_number - 1;

                        PDFPage page = current_pdf_doc_->GetPage(input_page_number-1);
                        if (page.IsEmpty()) {
                            addWrongPageIndexToList(input_page_number-1);
                        } else {
                            current_page_index_ = input_page_number - 1;
                            showPage(page, render_offset_x, render_offset_y);
                            updateViewAreaScrollbars(render_offset_x, render_offset_y);
                        }
                    }

                } else {
                    QString msgbox_title = "Error";
                    QString message = "The page number '" + lineedit_text + "' you input cannot be found in this document.";
                    QMessageBox::about(this, msgbox_title, message ) ;

                }
            }
        }

    }
    updatePageRelatedUIWidget();
}

QPoint MainWindow::calculateNewRenderOffsetPoint(float old_zoom_factor) {
    QPoint new_offset_point(0, 0);
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty())
        return new_offset_point;
    PDFPage page =  current_pdf_doc_->GetPage(current_page_index_) ;
    if (page.IsEmpty()) return new_offset_point;
    if ( qAbs(current_zoom_factor_ - old_zoom_factor)<1e-6 ) {
        // "current_zoom_factor_" IS EQUAL TO "old_zoom_factor"
        // Calculate render offset point from scoll bars directly.
        if ( ui_->hScrollBarViewArea->isEnabled() )
            new_offset_point.setX(ui_->hScrollBarViewArea->value());

        if (ui_->vScrollBarViewArea->isEnabled()) {
            if (page.IsEmpty()) return QPoint();
            float pdf_page_height = page.GetHeight();
            float page_render_height = pdf_page_height * current_zoom_factor_  ;

            QRect viewarea_rect = ui_->labelViewArea->geometry() ;
            float viewarea_height = (float)( viewarea_rect.height() ) ;

            int vscrollbar_page_delta = 1;
            if (page_render_height > viewarea_height)
                vscrollbar_page_delta = (int)(page_render_height - viewarea_height + 0.5);

            int vscrollbar_value = ui_->vScrollBarViewArea->value();
            int passed_delta_count = current_page_index_;
            QSetIterator<int> set_iterator(wrong_page_index_set_);
            while(set_iterator.hasNext()) {
                int temp = set_iterator.next();
                if (temp < current_page_index_)
                    passed_delta_count--;
            }
            new_offset_point.setY( vscrollbar_value - ( passed_delta_count * vscrollbar_page_delta ) );
        }
    } else {
        // current_zoom_factor_ != old_zoom_factor

        float pdf_page_height = page.GetHeight();
        float pdf_page_width = page.GetWidth();

        QRect viewarea_rect = ui_->labelViewArea->geometry() ;
        float viewarea_height = (float)( viewarea_rect.height() ) ;
        float viewarea_width = (float)(viewarea_rect.width());

        if (false == ui_->hScrollBarViewArea->isEnabled()) {
            // In this case, the old offset X must be 0 with old zoom factor.
            // So the new offset x keeps 0.
            new_offset_point.setX(0);
        } else {
            // In this case, the old offset X may not be 0 with old zoom factor.
            int old_scroll_value = ui_->hScrollBarViewArea->value();
            if (0 == old_scroll_value) {
                new_offset_point.setX(0);
            } else {
                float new_render_width = pdf_page_width * current_zoom_factor_;
                if (new_render_width > viewarea_width) {
                    float old_render_width = pdf_page_width * old_zoom_factor;
                    float old_offset_x = old_scroll_value;

                    int new_offset_x = (int)((((float)old_offset_x)/old_render_width) * new_render_width);
                    if (new_render_width - new_offset_x < viewarea_width)
                        new_offset_x = new_render_width - viewarea_width;

                    new_offset_point.setX( new_offset_x);
                } else {
                    // new render width <= vieware_width, so the new offset X will be 0.
                    new_offset_point.setX(0);
                }
            }
        }


        if (false == ui_->vScrollBarViewArea->isEnabled()) {
            // In this case, the old offset y must be 0 with old zoom factor.
            // So the new offset y keeps 0.
            new_offset_point.setY(0);
        } else{
            // In this case, the old offset Y may not be 0 with old zoom factor.
            int old_scroll_value = ui_->vScrollBarViewArea->value();
            int old_scroll_max = ui_->vScrollBarViewArea->maximum();
            if (0 == old_scroll_value || old_scroll_max == current_page_count_-1) {
                new_offset_point.setY(0);
            } else {
                float new_render_height = pdf_page_height * current_zoom_factor_;
                if (new_render_height > viewarea_height) {

                    float old_render_height = pdf_page_height * old_zoom_factor;
                    int old_scollbar_page_delta = (int)(old_render_height - viewarea_height + 0.5);
                    int passed_delta_count = current_page_index_;
                    QSetIterator<int> set_iterator(wrong_page_index_set_);
                    while(set_iterator.hasNext()) {
                        int temp = set_iterator.next();
                        if (temp < current_page_index_)
                            passed_delta_count--;
                    }
                    int old_offset_y = old_scroll_value - old_scollbar_page_delta * passed_delta_count;

                    int new_offset_y = (int)((((float)old_offset_y)/old_render_height) * new_render_height);
                    if (new_render_height - new_offset_y < viewarea_height)
                        new_offset_y = new_render_height - viewarea_height;

                    new_offset_point.setY(new_offset_y);
                } else {
                    // new render height <= vieware height, so the new offset Y will be 0.
                    new_offset_point.setY(0);
                }
            }
        }
    }
    return new_offset_point;
}

void MainWindow::on_pushBtnZoomActualSize_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return ;
    }
    float old_zoom_factor = current_zoom_factor_;
    current_zoom_factor_ = 1.0 ;

    updateZoomRelatedUIWidget(current_zoom_factor_);
    QPoint new_offset_point = calculateNewRenderOffsetPoint(old_zoom_factor);
    showPage(page, new_offset_point.x(), new_offset_point.y());
    updateViewAreaScrollbars(new_offset_point.x(), new_offset_point.y());

    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnActualsize;
    updateZoomRelatedBtnCheckedStatus(true);
}

void MainWindow::on_pushBtnZoomFitPage_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty())
        return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return ;
    }
    float pdf_page_width = page.GetWidth();
    float pdf_page_height = page.GetHeight();

    QRect viewarea_rect = ui_->labelViewArea->geometry() ;
    int viewarea_width = viewarea_rect.width();
    int viewarea_height = viewarea_rect.height();

    float zoomfactor_x = viewarea_width / pdf_page_width ;
    float zoomfactor_y = viewarea_height / pdf_page_height ;

    float old_zoom_factor = current_zoom_factor_;
    if ( zoomfactor_x <= zoomfactor_y )
        current_zoom_factor_ = zoomfactor_x ;
    else
        current_zoom_factor_ = zoomfactor_y ;

    updateZoomRelatedUIWidget( current_zoom_factor_ ) ;
    QPoint new_offset_point = calculateNewRenderOffsetPoint(old_zoom_factor);
    showPage(page, new_offset_point.x(), new_offset_point.y());
    updateViewAreaScrollbars(new_offset_point.x(), new_offset_point.y());

    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnFitPage;
    updateZoomRelatedBtnCheckedStatus(true);
}

void MainWindow::on_pushBtnZoomFitWidth_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty())
        return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return;
    }
    float pdf_page_width = page.GetWidth();

    QRect viewarea_rect = ui_->labelViewArea->geometry() ;
    int viewarea_width = viewarea_rect.width();

    float zoomfactor_x = viewarea_width / pdf_page_width ;

    float old_zoom_factor = current_zoom_factor_;
    current_zoom_factor_ = zoomfactor_x;

    updateZoomRelatedUIWidget( current_zoom_factor_ ) ;
    QPoint new_offset_point = calculateNewRenderOffsetPoint(old_zoom_factor);
    showPage(page, new_offset_point.x(), new_offset_point.y());
    updateViewAreaScrollbars(new_offset_point.x(), new_offset_point.y());

    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnFitWidth;
    updateZoomRelatedBtnCheckedStatus(true);
}

void MainWindow::on_pushBtnZoomOut_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return;
    }

    if (!ui_->pushBtnZoomIn->isEnabled())
        ui_->pushBtnZoomIn->setEnabled(true);

    float old_zoom_factor = current_zoom_factor_;
    if (qAbs(old_zoom_factor - ZOOMFACTOR_FLOAT_MIN) < 1e-6)
        return ;

    float new_zoom_factor = old_zoom_factor - ZOOMFACTOR_FLOAT_DELTA;
    if (qAbs(new_zoom_factor - ZOOMFACTOR_FLOAT_MIN) < 1e-6 ||
        new_zoom_factor < ZOOMFACTOR_FLOAT_MIN) {
        new_zoom_factor = ZOOMFACTOR_FLOAT_MIN;
    }
    current_zoom_factor_ = new_zoom_factor;
    updateZoomRelatedUIWidget( current_zoom_factor_ ) ;
    QPoint new_offset_point = calculateNewRenderOffsetPoint(old_zoom_factor);
    showPage(page, new_offset_point.x(), new_offset_point.y());
    updateViewAreaScrollbars(new_offset_point.x(), new_offset_point.y());

    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnOther;
    updateZoomRelatedBtnCheckedStatus(true);
}

void MainWindow::on_pushBtnZoomIn_clicked()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return;
    }

    if (!ui_->pushBtnZoomOut->isEnabled())
        ui_->pushBtnZoomOut->setEnabled(true);

    float old_zoom_factor = current_zoom_factor_;
    if (qAbs(old_zoom_factor - ZOOMFACTOR_FLOAT_MAX) < 1e-6)
        return;
    float new_zoomfactor = old_zoom_factor + ZOOMFACTOR_FLOAT_DELTA;
    if (new_zoomfactor > ZOOMFACTOR_FLOAT_MAX ||
        qAbs(new_zoomfactor - ZOOMFACTOR_FLOAT_MAX) < 1e-6) {
        new_zoomfactor = ZOOMFACTOR_FLOAT_MAX;
    }

    current_zoom_factor_ = new_zoomfactor;
    updateZoomRelatedUIWidget( current_zoom_factor_ ) ;
    QPoint new_offset_point = calculateNewRenderOffsetPoint(old_zoom_factor);
    showPage(page, new_offset_point.x(), new_offset_point.y());
    updateViewAreaScrollbars(new_offset_point.x(), new_offset_point.y());

    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnOther;
    updateZoomRelatedBtnCheckedStatus(true);

}

void MainWindow::on_hSliderZoom_valueChanged(int value)
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return;
    }
    float new_zoom_factor = getZoomFactorFromSliderValue(value);
    updateZoomRelatedUIWidget(new_zoom_factor, false);
	
    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnOther;
    updateZoomRelatedBtnCheckedStatus(true);
}

void MainWindow::addWrongPageIndexToList(int wrong_page_index) {
    if (wrong_page_index_set_.end() == wrong_page_index_set_.find(wrong_page_index))
        wrong_page_index_set_.insert(wrong_page_index);
}

void MainWindow::updateZoomRelatedBtnCheckedStatus(bool is_checkable) {
    ui_->pushBtnZoomActualSize->setCheckable(is_checkable);
    ui_->pushBtnZoomFitPage->setCheckable(is_checkable);
    ui_->pushBtnZoomFitWidth->setCheckable(is_checkable);

    if (false == is_checkable) {
        ui_->pushBtnZoomActualSize->setChecked(false);
        ui_->pushBtnZoomFitPage->setChecked(false);
        ui_->pushBtnZoomFitWidth->setChecked(false);

        return ;
    }

    switch(current_checked_zoom_btn_type_) {
        case MainWindow::e_ZoomBtnActualsize:
            ui_->pushBtnZoomActualSize->setChecked(true);
            ui_->pushBtnZoomFitPage->setChecked(false);
            ui_->pushBtnZoomFitWidth->setChecked(false);
            break;
        case MainWindow::e_ZoomBtnFitPage:
            ui_->pushBtnZoomActualSize->setChecked(false);
            ui_->pushBtnZoomFitPage->setChecked(true);
            ui_->pushBtnZoomFitWidth->setChecked(false);
            break;
        case MainWindow::e_ZoomBtnFitWidth:
            ui_->pushBtnZoomActualSize->setChecked(false);
            ui_->pushBtnZoomFitPage->setChecked(false);
            ui_->pushBtnZoomFitWidth->setChecked(true);
            break;
        case MainWindow::e_ZoomBtnOther:
            if (qAbs(current_zoom_factor_ - 1.0) < 1e-6)
                ui_->pushBtnZoomActualSize->setChecked(true);
            else
                ui_->pushBtnZoomActualSize->setChecked(false);
            ui_->pushBtnZoomFitPage->setChecked(false);
            ui_->pushBtnZoomFitWidth->setChecked(false);
            break;
    }
}

void MainWindow::on_hSliderZoom_sliderReleased()
{
    if (!current_pdf_doc_ || current_pdf_doc_->IsEmpty()) return ;
    PDFPage page = current_pdf_doc_->GetPage(current_page_index_);
    if (page.IsEmpty()) {
        addWrongPageIndexToList(current_page_index_);
        return;
    }

    int slider_new_value = ui_->hSliderZoom->value();
    float old_zoom_factor = current_zoom_factor_;
    current_zoom_factor_ = getZoomFactorFromSliderValue(slider_new_value);
    updateZoomRelatedUIWidget(current_zoom_factor_, false);
    QPoint new_offset_point = calculateNewRenderOffsetPoint(old_zoom_factor);
    showPage(page, new_offset_point.x(), new_offset_point.y());
    updateViewAreaScrollbars(new_offset_point.x(), new_offset_point.y());

    current_checked_zoom_btn_type_ = MainWindow::e_ZoomBtnOther;
    updateZoomRelatedBtnCheckedStatus(true);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    QEvent::Type event_type = event->type();
    switch (event_type) {
    case QEvent::MouseButtonPress:
        if (watched != ui_->lineEditPageNum && ui_->lineEditPageNum->hasFocus()) {
            ui_->lineEditPageNum->clearFocus();
        }
        if (watched != ui_->lineEditZoomNum && ui_->lineEditZoomNum->hasFocus()) {
            ui_->lineEditZoomNum->clearFocus();
        }
        break;
    case QEvent::FocusOut:
        if (watched == ui_->lineEditPageNum) {
            focusOutLineEditPageNum();
        }
        break;
    default:
        break;
    }

    return QWidget::eventFilter(watched, event);
}

typedef int (*FX_CupsPrintFile)(const char* name, const char* filename, const char* title, int num_options, void* options);

bool QtFileExists(QString &fileName)
{
    QFileInfo fi(fileName);
    return fi.exists();
}

void MainWindow::on_pushBtnPrint_clicked()
{
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print Document"));
    int first_page = 1;
    int last_page = current_pdf_doc_->GetPageCount();
    dialog.setMinMax(first_page, last_page);
    if (dialog.exec() == QDialog::Accepted) {
        if ((dialog.printRange() == QAbstractPrintDialog::PageRange) &&
            (dialog.fromPage() > 0) && (dialog.fromPage() > 0)) {
            first_page = dialog.fromPage();
            last_page = dialog.toPage();
        }

        if (first_page > last_page) {
            // Page range is incorrect
            return;
        }

        // Determine to use output file (for Print to PDF) or temporary file (for CUPS)
        QTemporaryFile* temp_file = NULL;
        QString print_to_file = "";
        if (printer.printerName() == "") {
            print_to_file = printer.outputFileName();
        }
        if (!print_to_file.isEmpty()) {
            if (QtFileExists(print_to_file)) {
                QFile::remove(print_to_file);
            }
        } else {
            temp_file = new QTemporaryFile("PDFReader_Qt_");
            temp_file->open();
            print_to_file = temp_file->fileName();
        }

        if (!print_to_file.isEmpty()) {
            // Create the output PDF from the current document, start by making a copy of the original file
            QString fx_temp_file = print_to_file + ".tmp";
            QFile::copy(current_pdf_file_, fx_temp_file);

            // Load the copy into a new PDFDoc
            PDFDoc* spool_doc = new PDFDoc(fx_temp_file.toLocal8Bit());
            ErrorCode error_code = spool_doc->Load("");

            // If the document needs a password, use the cached password and remove the security
            if (foxit::e_ErrPassword == error_code) {
                QString input_password = current_pdf_password_;
                std::wstring password_wstr = input_password.toStdWString();
                error_code = spool_doc->LoadW(password_wstr.c_str());
                if (foxit::e_ErrSuccess == error_code) {
                    spool_doc->RemoveSecurity();
                }
            }

            if (error_code != foxit::e_ErrSuccess)
            {
                // Some error creating the spool file
                return;
            }

            // Remove the pages before and after the page range
            while (first_page > 1) {
                spool_doc->RemovePage(0);
                first_page--;
                last_page--;
            }
            while (spool_doc->GetPageCount() > last_page) {
                spool_doc->RemovePage(last_page);
            }

            // Rotate and scale the pages to fit onto the output medium
            // to do

            // Save the final PDF
            spool_doc->SaveAs(print_to_file.toLocal8Bit(), PDFDoc::e_SaveFlagNormal);
            delete spool_doc;
            QFile::remove(fx_temp_file);
        }

        // Print the PDF using CUPS
        if (temp_file) {
            if (QtFileExists(print_to_file)) {

#ifdef __linux__
                QLibrary cupsLib(QLatin1String("cups"), 2);
                if (cupsLib.load()) {
                    FX_CupsPrintFile _cupsPrintFile;
                    _cupsPrintFile = (FX_CupsPrintFile) cupsLib.resolve("cupsPrintFile");
                    QString printerName = printer.printerName();
                    if (!printerName.isEmpty()) {
                        _cupsPrintFile(printerName.toStdString().c_str(), print_to_file.toStdString().c_str(),
                                       "PDFReader_Qt", 0, NULL);
                    }
                    cupsLib.unload();
                }
#endif
            }

            // Delete the spool file
            temp_file->close();
            delete temp_file;
        }
    }
}
