
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_actiondefault_file_triggered()
{
    std::string filename = "D:/learn/333333333/mark/1.jpg";
    srcImg = cv::imread(filename);
    if (!srcImg.data)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("警告"));
        msgBox.setText("没有该文件，请添加");
        msgBox.exec();
    }
    else
    {
        cv::cvtColor(srcImg,srcImg,cv::COLOR_BGR2RGB);
        myImg = QImage((const unsigned char*)(srcImg.data),srcImg.cols,srcImg.rows,srcImg.cols*srcImg.channels(),QImage::Format_RGB888);
        ui->label_1->clear();
        myImg = myImg.scaled(ui->label_1->width(),ui->label_1->height());
        ui->label_1->setPixmap(QPixmap::fromImage(myImg));
    }
}


void MainWindow::on_actioncustomization_file_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Image"),"",tr("Image File(*.bmp *.jpg *.jpeg *.png"));
    std::string name = filename.toStdString();
    srcImg = cv::imread(name);
    if(srcImg.empty())
    {
        QMessageBox msgBox;
        msgBox.setText("未找到数据");
        msgBox.exec();
    }
    else
    {
        cv::cvtColor(srcImg,srcImg,cv::COLOR_BGR2RGB);
        myImg = QImage((const unsigned char*)(srcImg.data),srcImg.cols,srcImg.rows,srcImg.cols*srcImg.channels(),QImage::Format_RGB888);
        ui->label_1->clear();
        myImg = myImg.scaled(ui->label_1->width(),ui->label_1->height());
        ui->label_1->setPixmap(QPixmap::fromImage(myImg));
    }
}


void MainWindow::on_actionrehabilitation_triggered()
{
    srcImg.copyTo(dstImg);
    myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.rows*dstImg.channels(),QImage::Format_RGB888);
    myImg = myImg.scaled(ui->label_1->size());
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}




void MainWindow::on_actionpurge_triggered()
{
    ui->label_1->clear();
    ui->label_2->clear();
}


void MainWindow::on_actionexit_triggered()
{
    exit(0);
}


void MainWindow::on_actionold_photos_triggered()
{
    cv::Mat dstImg(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++)
    {
        uchar *p0 = srcImg.ptr<uchar>(i);
        uchar *q0 = dstImg.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols; j++)
        {
            int srcR = p0[3*j];
            int srcG = p0[3*j+1];
            int srcB = p0[3*j+2];
            int dstR,dstG,dstB;
            dstR = (101 * srcR + 197 * srcG + 48 * srcB) >> 8;
            dstG = (89 * srcR + 176 * srcG + 43 * srcB) >> 8;
            dstB = (70 * srcR + 137 * srcG + 34 * srcB) >> 8;
            dstR = dstR>255?255:dstR;
            dstG = dstG>255?255:dstG;
            dstB = dstB>255?255:dstB;
            q0[3*j] = dstR;
            q0[3*j+1] = dstG;
            q0[3*j+2] = dstB;
        }
        cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
        cv::resize(srcImg,dstImg,dsize);
        myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.cols*dstImg.channels(),QImage::Format_Indexed8);
        ui->label_2->clear();
        ui->label_2->setPixmap(QPixmap::fromImage(myImg));
//        showLabel(dstImg,ui->label_2);
        qDebug()<<"1111111111111111";
    }
}

void MainWindow::showLabel(cv::Mat img,QLabel *l)
{
//    qDebug
    myImg = QImage((const unsigned char*)(img.data),img.cols,img.rows,img.rows*img.channels(),QImage::Format_RGB888);
    l->clear();
    myImg = myImg.scaled(l->width(),l->height());
    l->setPixmap(QPixmap::fromImage(myImg));
}



void MainWindow::on_actionred_green_swap_triggered()
{
    cv::Mat dstImg(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++)
    {
        uchar *p0 = srcImg.ptr<uchar>(i);
        uchar *q0 = dstImg.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols; j++)
        {
            int srcR = p0[3*j];
            int srcG = p0[3*j+1];
            int srcB = p0[3*j+2];
            int dstR,dstG,dstB;
            dstR = (101 * srcR + 197 * srcG + 48 * srcB) >> 8;
            dstG = (89 * srcR + 176 * srcG + 43 * srcB) >> 8;
            dstB = (70 * srcR + 137 * srcG + 34 * srcB) >> 8;
            dstR = dstR>255?255:dstR;
            dstG = dstG>255?255:dstG;
            dstB = dstB>255?255:dstB;

            q0[3*j] = dstR;
            q0[3*j+1] = dstG;
            q0[3*j+2] = dstB;
        }
        cv::cvtColor(dstImg,dstImg,cv::COLOR_RGB2BGR);
        showLabel(dstImg,ui->label_2);
    }
}



void MainWindow::on_actiongrayscale_triggered()
{
    cv::cvtColor(srcImg,dstImg,cv::COLOR_RGB2GRAY);
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dstImg,dstImg,dsize);
    myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.cols*dstImg.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actionbinarization_triggered()
{
    cv::cvtColor(srcImg,dstImg,cv::COLOR_RGB2GRAY);
    cv::threshold(dstImg,dstImg,128,255,0);
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dstImg,dstImg,dsize);
    myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.cols*dstImg.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}




void MainWindow::on_actioncolor_transformation_triggered()
{
    int myRand;
    myRand = rand()%13;
    cv::Mat img(srcImg.size(),CV_8UC3);
    cv::applyColorMap(srcImg,img,myRand);
    showLabel(img,ui->label_2);
}


void MainWindow::on_actionR_channel_triggered()
{
    cv::Mat dst[3];
    cv::Mat dstR(srcImg.rows,srcImg.cols,CV_8UC1);
    cv::split(srcImg, dst);
    dst[0].copyTo(dstR);
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dstR,dstR,dsize);
    myImg = QImage((const unsigned char*)(dstR.data),dstR.cols,dstR.rows,dstR.cols*dstR.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actionG_channel_triggered()
{
    cv::Mat dst[3];
    cv::Mat dstG(srcImg.rows,srcImg.cols,CV_8UC1);
    cv::split(srcImg, dst);
    dst[1].copyTo(dstG);
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dstG,dstG,dsize);
    myImg = QImage((const unsigned char*)(dstG.data),dstG.cols,dstG.rows,dstG.cols*dstG.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}




void MainWindow::on_actionB_channel_triggered()
{
    cv::Mat dst[3];
    cv::Mat dstB(srcImg.rows,srcImg.cols,CV_8UC1);
    cv::split(srcImg, dst);
    dst[2].copyTo(dstB);
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dstB,dstB,dsize);
    myImg = QImage((const unsigned char*)(dstB.data),dstB.cols,dstB.rows,dstB.cols*dstB.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actionwoodcarving_triggered()
{
    cv::Mat dst(srcImg.rows,srcImg.cols,CV_8UC1);
    cv::Mat src;
    cv::cvtColor(srcImg,src,cv::COLOR_RGBA2GRAY);
    for (int i = 1; i < src.rows-1; i++) {
        uchar *current = src.ptr<uchar>(i);
        uchar *currentBefore = src.ptr<uchar>(i-1);
        uchar *currentNext = src.ptr<uchar>(i+1);

        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 1; j < src.cols-1; j++) {
            int a,b,c,d,e,f,g,h;
            a = cv::abs(current[j]-currentBefore[(j-1)]);
            b = cv::abs(current[j]-currentBefore[j]);
            c = cv::abs(current[j]-currentBefore[(j+1)]);
            d = cv::abs(current[j]-currentNext[(j-1)]);
            e = cv::abs(current[j]-currentNext[j]);
            f = cv::abs(current[j]-currentNext[(j+1)]);
            g = cv::abs(current[j]-current[(j-1)]);
            h = cv::abs(current[j]-current[(j+1)]);
            if(a>30||b>30||c>30||d>30||e>30||f>30||g>30||h>30)
            {
                dstLine[j]=255;
            }
            else
            {
                dstLine[j]=0;
            }
        }
    }
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dst,dst,dsize);
    myImg = QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actionpencil_drawing_triggered()
{
    cv::Mat dst(srcImg.rows,srcImg.cols,CV_8UC1);
    cv::Mat src;
    cv::cvtColor(srcImg,src,cv::COLOR_RGBA2GRAY);
    for (int i = 1; i < src.rows-1; i++) {
        uchar *current = src.ptr<uchar>(i);
        uchar *currentBefore = src.ptr<uchar>(i-1);
        uchar *currentNext = src.ptr<uchar>(i+1);

        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 1; j < src.cols-1; j++) {
            int a,b,c,d,e,f,g,h;
            a = cv::abs(current[j]-currentBefore[(j-1)]);
            b = cv::abs(current[j]-currentBefore[j]);
            c = cv::abs(current[j]-currentBefore[(j+1)]);
            d = cv::abs(current[j]-currentNext[(j-1)]);
            e = cv::abs(current[j]-currentNext[j]);
            f = cv::abs(current[j]-currentNext[(j+1)]);
            g = cv::abs(current[j]-current[(j-1)]);
            h = cv::abs(current[j]-current[(j+1)]);
            if(a>30||b>30||c>30||d>30||e>30||f>30||g>30||h>30)
            {
                dstLine[j]=0;
            }
            else
            {
                dstLine[j]=255;
            }
        }
    }
    cv::Size dsize = cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dst,dst,dsize);
    myImg = QImage((const unsigned char*)(dst.data),dst.cols,dst.rows,dst.cols*dst.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actionsketching_triggered()
{
    cv::Mat src;
    srcImg.copyTo(src);
    int width=src.cols;
    int heigh=src.rows;
    cv::Mat gray0,gray1;
    cv::cvtColor(src,gray0,cv::COLOR_RGBA2GRAY);
    cv::addWeighted(gray0,-1,NULL,0,255,gray1);
    cv::GaussianBlur(gray1,gray1,cv::Size(11,11),0);
    cv::Mat dst(gray1.size(),CV_8UC1);
    for (int y = 0; y < heigh; y++) {
        uchar* P0 = gray0.ptr<uchar>(y);
        uchar* P1 = gray1.ptr<uchar>(y);
        uchar* P = dst.ptr<uchar>(y);
        for (int x = 0; x < width; x++) {
            int tmp0=P0[x];
            int tmp1=P1[x];
            P[x] = (uchar) std::min((tmp0+(tmp0*tmp1)/(256-tmp1)),255);
        }
    }
    cv::Size dsize = cv::Size (ui->label_2->width(),ui->label_2->height());
    cv::resize(dst,dstImg,dsize);
    myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.cols*dstImg.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actiondifuse_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    cv::RNG rng;
    for (int y=1; y<srcImg.rows-1; y++){
        uchar* srcR = srcImg.ptr<uchar>(y);
        uchar* dstR = dst.ptr<uchar>(y);
        for (int x=1; x<srcImg.cols-1; x++){
            int myRand=rng. uniform(0,9);srand(time(NULL));
            myRand=rand()%9;
            dstR[3*x]=srcImg.at<uchar>(y-1+myRand/3,3*(x-1+myRand%3));
            dstR[3*x+1]=srcImg.at<uchar>(y-1+myRand/3,3*(x-1+myRand%3)+1);
            dstR[3*x+2]=srcImg.at<uchar>(y-1+myRand/3,3*(x-1+myRand%3)+2);
        }
        dst.copyTo(dstImg);
        showLabel(dstImg,ui->label_2);
    }
}


void MainWindow::on_actionblur_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    int tem[3][3]={1,2,1,2,4,2,1,2,1};
    for (int y=1; y<srcImg.rows-1; y++)
    {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 1; x < srcImg.cols-1; x++) {
            br = 0;
            bg = 0;
            bb = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    br+=srcImg.at<uchar>(y+i,3*(x+j))* tem[i+1][j+1];
                    bg+=srcImg.at<uchar>(y+i,3*(x+j)+1)* tem[i+1][j+1];
                    bb+=srcImg.at<uchar>(y+i,3*(x+j)+2)* tem[i+1][j+1];
                }
            }
            dstR[3*x]=br>>4;
            dstR[3*x+1]=bg>>4;
            dstR[3*x+2]=bb>>4;
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actionsoften_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 2; y < srcImg.rows-2; y++) {
        uchar* srcR = srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 2; x < srcImg.cols-2; x++) {
            br = 0;
            bg = 0;
            bb = 0;
            for (int i = -2; i < 2; i++) {
                for (int j = -2; j < 2; j++) {
                    br+=srcImg.at<uchar>(y+i,3*(x+j));
                    bg+=srcImg.at<uchar>(y+i,3*(x+j)+1);
                    bb+=srcImg.at<uchar>(y+i,3*(x+j)+2);
                }
            }
            dstR[3*x]=br/(4*2*2+4*2+1);
            dstR[3*x+1]=bg/(4*2*2+4*2+1);
            dstR[3*x+2]=bb/(4*2*2+4*2+1);
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actionsharpen_triggered()
{
    int R,S;
    R=2;
    S=2;
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 2; y < srcImg.rows-2; y++) {
        uchar* srcR = srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 2; x < srcImg.cols-2; x++) {
            br = 0;
            bg = 0;
            bb = 0;
            for (int i = -2; i < 2; i++) {
                for (int j = -2; j < 2; j++) {
                    if(i == 0 && j==0){
                        continue;
                    }
                    br+=srcImg.at<uchar>(y+i,3*(x+j));
                    bg+=srcImg.at<uchar>(y+i,3*(x+j)+1);
                    bb+=srcImg.at<uchar>(y+i,3*(x+j)+2);
                }
            }
            br=srcImg.at<uchar>(y,3*x)*(1+S)-br*S/(4*R*R+4*R+1);
            bg=srcImg.at<uchar>(y,3*x+1)*(1+S)-br*S/(4*R*R+4*R+1);
            bb=srcImg.at<uchar>(y,3*x+2)*(1+S)-br*S/(4*R*R+4*R+1);
            dstR[3*x]=br;
            dstR[3*x+1]=bg;
            dstR[3*x+2]=bb;
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actionmaximum_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y=1; y<srcImg.rows-1; y++)
    {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 1; x < srcImg.cols-1; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    br=br>srcImg.at<uchar>(y+i,3*(x+j)+1)?br:srcImg.at<uchar>(y+i,3*(x+j)+1);
                    bg=bg>srcImg.at<uchar>(y+i,3*(x+j)+1)?bg:srcImg.at<uchar>(y+i,3*(x+j)+1);
                    bb=bb>srcImg.at<uchar>(y+i,3*(x+j)+1)?bb:srcImg.at<uchar>(y+i,3*(x+j)+1);
                }
            }
            dstR[3*x]=br;
            dstR[3*x+1]=bg;
            dstR[3*x+2]=bb;
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actionminimum_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y=2; y<srcImg.rows-2; y++)
    {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 2; x < srcImg.cols-2; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    br=br<srcImg.at<uchar>(y+i,3*(x+j)+1)?br:srcImg.at<uchar>(y+i,3*(x+j)+1);
                    bg=bg<srcImg.at<uchar>(y+i,3*(x+j)+1)?bg:srcImg.at<uchar>(y+i,3*(x+j)+1);
                    bb=bb<srcImg.at<uchar>(y+i,3*(x+j)+1)?bb:srcImg.at<uchar>(y+i,3*(x+j)+1);
                }
            }
            dstR[3*x]=br;
            dstR[3*x+1]=bg;
            dstR[3*x+2]=bb;
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioncomic_strip_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 0; y < srcImg.rows; y++) {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        float brF,bgF,bbF;
        for (int x = 0; x < srcImg.cols; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];

            brF= (abs(bg - bb + bg + br) * br) >> 8;
            bgF= (abs(bb - bg + bb + br) * br) >> 8;
            bbF= (abs(bb - bg + bb + br) * bg) >> 8;

            brF = brF > 255? 255 : brF;
            bgF = bgF > 255? 255 :bgF;
            bbF = bbF > 255? 255 : bbF;

            brF = brF < 0? 0 : brF;
            bgF = bgF < 0? 0 : bgF;
            bbF = bbF < 0? 0 : bbF;

            dstR[3*x]= (uchar)brF;
            dstR[3*x+1]= (uchar)bgF;
            dstR[3*x+2]= (uchar)bbF;
        }
    }
    normalize(dst,dst,255,0,cv::NORM_MINMAX);
    showLabel(dst,ui->label_2);
//    cv::Size dsize=cv::Size(ui->label_2->width(),ui->label_2->height());
//    cv::resize(dst,dstImg,dsize);
//    myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.cols*dstImg.channels(),QImage::Format_Indexed8);
//    ui->label_2->clear();
//    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actionmelt_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 0; y < srcImg.rows; y++) {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 0; x < srcImg.cols; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];

            br=br*128/(bg+bb +1);
            bg= bg*128/(br+bb +1);
            bb=bb*128/(bg+br +1);

            br = br > 255? 255 : br;
            bg = bg > 255? 255 : bg;
            bb = bb > 255? 255 : bb;

            br = br < 0? 0 : br;
            bg = bg > 0? 0 : bg;
            bb = bb > 0? 0 : bb;

            dstR[3*x]= br;
            dstR[3*x+1]= bg;
            dstR[3*x+2]= bb;
        }
    }
    showLabel(dst,ui->label_2);
}


void MainWindow::on_actionfreeze_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 0; y < srcImg.rows; y++) {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        float br,bg,bb;
        for (int x = 0; x < srcImg.cols; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];

            br=(br-bg-bb)*3/2;
            bg= (bg-br-bb)*3/2;
            bb=(bb-bg-br)*3/2;

            br = br > 255? 255 : br;
            bg = bg > 255? 255 : bg;
            bb = bb > 255? 255 : bb;

            br = br < 0? -br : br;
            bg = bg > 0? -bg : bg;
            bb = bb > 0? -bb : bb;

            dstR[3*x]= (uchar)br;
            dstR[3*x+1]= (uchar)bg;
            dstR[3*x+2]= (uchar)bb;
        }
    }
    showLabel(dst,ui->label_2);
}


void MainWindow::on_actioninverted_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 0; y < srcImg.rows; y++) {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 0; x < srcImg.cols; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];

            dstR[3*x]= 255-br;
            dstR[3*x+1]= 255-bg;
            dstR[3*x+2]= 255-bb;
        }
    }
    showLabel(dst,ui->label_2);
}


void MainWindow::on_actionglare_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 0; y < srcImg.rows; y++) {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 0; x < srcImg.cols; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];

            br=br>127.5? br+(255-br)*(br-127.5)/127.5:br*br/127.5;
            br=br>255?255:br;
            br=br<0?0:br;

            bg=bg>127.5? bg+(255-bg)*(bg-127.5)/127.5:bg*bg/127.5;
            bg=bg>255?255:bg;
            bg=bg<0?0:bg;

            bb=bb>127.5? bb+(255-bb)*(bb-127.5)/127.5:bb*bb/127.5;
            bb=bb>255?255:bb;
            bb=bb<0?0:bb;

            dstR[3*x]= br;
            dstR[3*x+1]= bg;
            dstR[3*x+2]= bb;
        }
    }
    showLabel(dst,ui->label_2);
}


void MainWindow::on_actionblack_and_white_negative_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int y = 0; y < srcImg.rows; y++) {
        uchar* srcR= srcImg.ptr<uchar>(y);
        uchar* dstR= dst.ptr<uchar>(y);
        int br,bg,bb;
        for (int x = 0; x < srcImg.cols; x++) {
            br = srcR[3*x];
            bg = srcR[3*x+1];
            bb = srcR[3*x+2];

            dstR[3*x]= 255-br;
            dstR[3*x+1]= 255-bg;
            dstR[3*x+2]= 255-bb;
        }
    }
    cv::cvtColor(dst,dstImg,cv::COLOR_RGB2GRAY);
    cv::Size dsize=cv::Size(ui->label_2->width(),ui->label_2->height());
    cv::resize(dstImg,dstImg,dsize);
    myImg = QImage((const unsigned char*)(dstImg.data),dstImg.cols,dstImg.rows,dstImg.cols*dstImg.channels(),QImage::Format_Indexed8);
    ui->label_2->clear();
    ui->label_2->setPixmap(QPixmap::fromImage(myImg));
}


void MainWindow::on_actioneffect_1_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*j+k]-currentBefore[3*(j-1)+k]+128;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_2_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*(j+1)+k]-currentBefore[3*j+k]+128;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_3_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*(j+3)+k]-currentBefore[3*(j-3)+k]+200;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_4_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*(j+3)+k]-currentBefore[3*(j-3)+k]+40;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_A_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*j+k]-currentBefore[3*(j+1)+k]+128;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_B_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*(j-1)+k]-currentBefore[3*j+k]+128;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_C_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*(j-3)+k]-currentBefore[3*(j+3)+k]+200;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actioneffect_D_triggered()
{
    cv::Mat dst(srcImg.size(),CV_8UC3);
    for (int i = 1; i < srcImg.rows-1; i++) {
        uchar *current = srcImg.ptr<uchar>(i);
        uchar *currentBefore = srcImg.ptr<uchar>(i-1);
        uchar *dstLine = dst.ptr<uchar>(i);
        for (int j = 0; j < srcImg.cols-1; j++) {
            for (int k = 0; k < 3; k++) {
                int tmp0 = current[3*(j-3)+k]-currentBefore[3*(j+3)+k]+40;
                if (tmp0<0)
                    dstLine[3*j+k]=0;
                else if(tmp0>255)
                    dstLine[3*j+k]=255;
                else
                    dstLine[3*j+k]=tmp0;
            }
        }
    }
    dst.copyTo(dstImg);
    showLabel(dstImg,ui->label_2);
}


void MainWindow::on_actionversion_triggered()
{
    QMessageBox::information(this,"关于",tr("本软件当前版本为V1.0"));
}


void MainWindow::on_actionauthor_triggered()
{
    QMessageBox::information(this,"版权",tr("本软件版权所有者：201006206张艾明"));
}

