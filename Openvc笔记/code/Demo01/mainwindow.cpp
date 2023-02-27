#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_pressed()
{
    //    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", ".", "Image Files(*.jpg *.png *jeg *.bmp)");
    //    Mat src = imread(fileName.toStdString());
    //    //图片处亚
    //    cvtColor(src, src, COLOR_BGR2GRAY);
    //    int thresh = 100;
    //    Canny(src, src, thresh, thresh * 2, 3);
    //    //将图片显示到tabeL上
    //    QPixmap pix = Mat2QImage(src);
    //    ui->LabeL->setPixmap(pix);
    Mat src(Size(640, 480), CV_8UC1, cv::Scalar(255));
    circle(src, Point(100, 100), 100, Scalar(0), -1);
    //格式转换
//    QPixmap qpixmap = Mat2QImage(src);
//    //将图片显示到tabeL上
//    ui->label->setPixmap(qpixmap);
}

/* ////////////////////////heLper函数/////////////////////////////////////////////*/
//格式转换
//QPixmap Mat2QImage(Mat mat)
//{
//    QImage img;
//    //根据QT的显示方法进行转换
//    if(mat.channels() == 3)
//    {
//        cvtColor(mat, mat, COLOR_BGR2RGB);
//        img = QImage((const unsigned char*)(mat.data), mat.cols, mat.rows, QImage::Format_RGB888 );
//    }
//    else
//    {
//        img = QImage((const unsigned char*)(mat.data), mat.cols, mat.rows, QImage::Format_Grayscale8);
//    }
//    QPixmap qimg = QPixmap::fromImage(img);
//    return qimg;
//}


