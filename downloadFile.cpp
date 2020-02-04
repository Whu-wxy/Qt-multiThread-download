#include "downloadFile.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QApplication>
#include <QThread>
#include "downloaddata.h"

DownloadFile::DownloadFile(QObject *parent) : QObject(parent)
{
    m_manager  = new QNetworkAccessManager(this);
    loop= new QEventLoop;
}

void DownloadFile::Get(DownloadData*data)
{
    path=data->getSave();

    if(m_file!=nullptr){
        m_file->flush();
        m_file->close();
    }

    m_file  = new QFile(data->getSave());
    if(!m_file->open(QIODevice::WriteOnly))
    {
        qDebug()<<QString("Unable to create file: %1").arg(data->getSave());
        return;
    }

    if(m_reply!=nullptr)
    {
        m_reply->deleteLater();
    }

    m_reply = data->getReply(m_manager);

    connect(m_reply,&QNetworkReply::sslErrors,this,&DownloadFile::sslError,Qt::QueuedConnection);
    connect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SIGNAL(error(QNetworkReply::NetworkError)),Qt::QueuedConnection);
    connect(m_reply,&QNetworkReply::downloadProgress,this,&DownloadFile::fileDownloadProgress,Qt::QueuedConnection);
    connect(m_reply,&QNetworkReply::finished,this,&DownloadFile::downloadFinished);
    connect(m_reply,&QNetworkReply::readyRead,this,&DownloadFile::readyRead);
    connect(m_reply,&QNetworkReply::finished,loop,&QEventLoop::quit);

    loop->exec();
}

bool DownloadFile::isDownload() const
{
    return m_file!=nullptr;
}

void DownloadFile::Dispose()
{
    if(m_file!=nullptr){
        m_file->flush();
        m_file->close();
        m_file=nullptr;
    }

    if(m_reply!=nullptr){
        disconnect(m_reply,&QNetworkReply::sslErrors,this,&DownloadFile::sslError);
        disconnect(m_reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SIGNAL(error(QNetworkReply::NetworkError)));
        disconnect(m_reply,&QNetworkReply::downloadProgress,this,&DownloadFile::fileDownloadProgress);
        disconnect(m_reply,&QNetworkReply::finished,this,&DownloadFile::downloadFinished);

        m_reply->deleteLater();
        m_reply=nullptr;
    }
}

void DownloadFile::readyRead()
{
    if(m_file!=nullptr && m_reply!=nullptr){
        m_file->write(m_reply->readAll());
    }
}

void DownloadFile::downloadFinished()
{
    Dispose();
    emit finished(path);
}

void DownloadFile::fileDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    emit downloadProgress(bytesReceived,bytesTotal);
}
