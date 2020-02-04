#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "downloadFile.h"
#include <QDebug>
#include "httpthread.h"
#include "downloaddata.h"
#include "downloadResources.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DownloadResources *thread = new DownloadResources();


    connect(thread,&DownloadResources::error,this,[=](QNetworkReply::NetworkError code){
        qDebug()<<code;
    });

    connect(thread,&DownloadResources::sslError,this,[=]( const QList<QSslError> &errors){
        qDebug()<<errors.count();
    });

    connect(thread,&DownloadResources::downloadProgress,this,[=](qint64 bytesReceived, qint64 bytesTotal){
       qDebug()<< bytesReceived;
       qDebug()<<bytesTotal;
    });
    connect(thread,&DownloadResources::finished,this,[=](QString fileName){
        qDebug()<<fileName;
    });

    thread->start();
    thread->GetUrl(new DownloadData("http://ure.pia.co.jp/mwimgs/c/7/400/img_c7654b54f577db8cc98dac603f78efab257112.jpg","E:/1.jpg"));//http://www.dtj.ink/1.png
    thread->GetUrl(new DownloadData("http://ure.pia.co.jp/mwimgs/c/7/400/img_c7654b54f577db8cc98dac603f78efab257112.jpg","E:/2.jpg"));

    //QSslSocket:TLS initialization failed（TLS初始化失败）
    //找到你的Qt安装目录（我的在这里：Qt\Qt5.12.0\Tools\mingw730_64\opt\bin）
    //的libeay32.bll和ssleay32.bll两个文件，放到你的.exe同目录就OK了
}

MainWindow::~MainWindow()
{
    delete ui;
}
