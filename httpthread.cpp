#include "httpthread.h"
#include "downloadFile.h"
#include "downloaddata.h"
#include <QDebug>
HttpThread::HttpThread() : QThread()
{

}

void HttpThread::Set(DownloadData *data)
{
    this->data=data;
}

bool HttpThread::isDownloading() const
{
    return download->isDownload();
}

void HttpThread::Stop()
{
    isRun=false;
}


void HttpThread::run()
{
    isRun=true;
    download = new DownloadFile();
    connect(download,&DownloadFile::error,this,&HttpThread::error,Qt::QueuedConnection);
    connect(download,&DownloadFile::downloadProgress,this,&HttpThread::downloadProgress,Qt::QueuedConnection);
    connect(download,&DownloadFile::sslError,this,&HttpThread::sslError,Qt::QueuedConnection);
    connect(download,&DownloadFile::finished,this,&HttpThread::finished,Qt::QueuedConnection);

    while(isRun){
        if(data!=nullptr){
            download->Get(data);
            data=nullptr;
        }
        QThread::sleep(1);
    }

    disconnect(download,&DownloadFile::error,this,&HttpThread::error);
    disconnect(download,&DownloadFile::downloadProgress,this,&HttpThread::downloadProgress);
    disconnect(download,&DownloadFile::sslError,this,&HttpThread::sslError);
    disconnect(download,&DownloadFile::finished,this,&HttpThread::finished);
    download->Dispose();
    download=nullptr;
    data=nullptr;
}

