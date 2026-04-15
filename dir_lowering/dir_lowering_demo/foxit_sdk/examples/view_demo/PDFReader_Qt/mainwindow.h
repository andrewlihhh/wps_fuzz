#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

#include "pdf/fs_pdfdoc.h"
#include "pdf/fs_pdfpage.h"
using namespace foxit;
using namespace foxit::pdf;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum ZoomBtnType {
        e_ZoomBtnActualsize = 0,
        e_ZoomBtnFitPage = 1,
        e_ZoomBtnFitWidth = 2,
        e_ZoomBtnOther = 3
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool isSDKInitialized();

private slots:
    void on_pushBtnOpenFile_clicked();

    void on_pushBtnCloseFile_clicked();

    void on_vScrollBarViewArea_valueChanged(int value);

    void on_hScrollBarViewArea_valueChanged(int value);

    void on_pushBtnGoToFirstPage_clicked();

    void on_pushBtnGoToPrevPage_clicked();

    void on_pushBtnGoToNextPage_clicked();

    void on_pushBtnGoToLastPage_clicked();

    void on_lineEditPageNum_returnPressed();

    void on_pushBtnZoomActualSize_clicked();

    void on_pushBtnZoomFitPage_clicked();

    void on_pushBtnZoomFitWidth_clicked();

    void on_pushBtnZoomOut_clicked();

    void on_pushBtnZoomIn_clicked();

    void on_hSliderZoom_valueChanged(int value);

    void on_hSliderZoom_sliderReleased();

    bool eventFilter(QObject *watched, QEvent *event);

    void on_pushBtnPrint_clicked();

private:
    // Events
    void wheelEvent( QWheelEvent* pEvent );

private:
    void initViewArea();
    void updatePageRelatedUIWidget();
    void enableZoomRelatedUIWidget(bool to_enable);
    void updateZoomRelatedUIWidget(float new_factor, bool update_slider_value = true);
    void updateZoomRelatedBtnCheckedStatus(bool is_checkable);
    float getZoomFactorFromSliderValue(int slider_value);
    int getSliderValueFromZoomFactor(float zoom_factor);

    void updateViewAreaScrollbars(int render_offset_x, int render_offset_y);
    bool showPage( PDFPage& page, int offset_x, int offset_y );
    QPoint calculateNewRenderOffsetPoint(float old_zoom_factor);

    void addWrongPageIndexToList(int wrong_page_index);
    void focusOutLineEditPageNum();

private:
    Ui::MainWindow *ui_;

    bool sdk_initialized_;
    PDFDoc* current_pdf_doc_;
    QSet<int> wrong_page_index_set_;
    int current_page_count_;
    int current_page_index_;
    QString current_pdf_file_;
    QString current_pdf_password_;

    float current_zoom_factor_;
    ZoomBtnType current_checked_zoom_btn_type_;
};

#endif // MAINWINDOW_H
