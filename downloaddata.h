#ifndef DOWNLOADDATA_H
#define DOWNLOADDATA_H

#include <QString>


class QNetworkRequest;
class QNetworkReply;
class QNetworkAccessManager;

class DownloadData
{
public:
    DownloadData(QString url);
    DownloadData(QString url,QString save);
    DownloadData(QNetworkRequest *request, QString save);
    void setContent(QByteArray array);
    QString getUrl() const;
    QString getSave() const;
    QNetworkReply *getReply(QNetworkAccessManager*manager);
private:
    bool isGet=true;
    QByteArray content;
    QString url;
    QString save;
    QNetworkRequest *request=nullptr;
};

#endif // DOWNLOADDATA_H
