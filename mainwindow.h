
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <opencv2/opencv.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

signals:
    void timeout();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void showLabel(cv::Mat img,QLabel *l);


    void on_actiondefault_file_triggered();

    void on_actioncustomization_file_triggered();

    void on_actionrehabilitation_triggered();

    void on_actionpurge_triggered();

    void on_actionexit_triggered();

    void on_actionold_photos_triggered();

    void on_actionred_green_swap_triggered();

    void on_actiongrayscale_triggered();

    void on_actionbinarization_triggered();

    void on_actioncolor_transformation_triggered();

    void on_actionR_channel_triggered();

    void on_actionG_channel_triggered();

    void on_actionB_channel_triggered();

    void on_actionwoodcarving_triggered();

    void on_actionpencil_drawing_triggered();

    void on_actionsketching_triggered();

    void on_actiondifuse_triggered();

    void on_actionblur_triggered();

    void on_actionsoften_triggered();

    void on_actionsharpen_triggered();

    void on_actionmaximum_triggered();

    void on_actionminimum_triggered();

    void on_actioncomic_strip_triggered();

    void on_actionmelt_triggered();

    void on_actionfreeze_triggered();

    void on_actioninverted_triggered();

    void on_actionglare_triggered();

    void on_actionblack_and_white_negative_triggered();

    void on_actioneffect_1_triggered();

    void on_actioneffect_2_triggered();

    void on_actioneffect_3_triggered();

    void on_actioneffect_4_triggered();

    void on_actioneffect_A_triggered();

    void on_actioneffect_B_triggered();

    void on_actioneffect_C_triggered();

    void on_actioneffect_D_triggered();

    void on_actionversion_triggered();

    void on_actionauthor_triggered();

    void on_actiontest1_triggered();

    void on_actionScene_recognition_triggered();

    void on_actionopen_camera_triggered();

    void on_actionclose_camera_triggered();



    void on_actionTM_CCOEFF_NORMED_triggered();

    void on_actionTM_SQDIFF_NORMED_triggered();

private:

    void displayImageFunc(QLabel *label, const cv::Mat &inputImg);
    void getFeature(cv::Mat m, float a[]);
    float ouDistance(float a[], float b[]);
    int getResultNumber();

private:
    Ui::MainWindow *ui;

    cv::Mat srcImg; //读入原始图像数据
    cv::Mat dstImg; //存放处理后的图像数据
    QImage myImg;
    cv::Mat tmpImg;//临时图像
    cv::Mat shotImg;//短期图像
    QImage myQImg;//显示图像
    QTimer *myTimer;//创建定时器指针
    cv::Mat tempImg; //模板图像
    cv::Mat testImage;
    cv::Mat srcImage[10];
    cv::Mat dstImage;
    QImage img;
    float testFeature[25];
    float srcFeature[10][25];

    cv::VideoCapture Camera;

};

#endif // MAINWINDOW_H
