#include "downloaddata.h"
#include <QNetworkRequest>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include <QFileInfo>
#include<QCoreApplication>
DownloadData::DownloadData(QString url)
{
    this->url=url;
    QFileInfo info(url);
    this->save=QString("%1/%2").arg(QCoreApplication::applicationDirPath()).arg(info.fileName());
    request = new QNetworkRequest(QUrl(url));
}

DownloadData::DownloadData(QString url, QString save)
{
    this->url=url;
    this->save=save;
    request = new QNetworkRequest(QUrl(url));
}

DownloadData::DownloadData(QNetworkRequest *request, QString save)
{
    this->request=request;
    this->save=save;
}

void DownloadData::setContent(QByteArray array)
{
    this->content=array;
}

QString DownloadData::getUrl() const
{
    return url;
}

QString DownloadData::getSave() const
{
    return save;
}

QNetworkReply *DownloadData::getReply(QNetworkAccessManager *manager)
{
    if(isGet){
        return manager->get(*request);
    }else{
        return manager->post(*request,content);
    }

}
