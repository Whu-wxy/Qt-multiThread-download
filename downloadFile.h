#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkReply>
class QNetworkAccessManager;
class QNetworkRequest;
class QFile;
class QEventLoop;
class DownloadData;

class DownloadFile : public QObject
{
    Q_OBJECT
public:
    explicit DownloadFile(QObject *parent = 0);
    void Get(DownloadData*data);
    bool isDownload() const;
    void Dispose();
signals:
    void sslError(const QList<QSslError> &errors);
    void error(QNetworkReply::NetworkError code);
    void finished(QString fileName);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

public slots:
    void readyRead();
    void downloadFinished();
    void fileDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    QNetworkAccessManager *m_manager;
    QNetworkReply *m_reply=nullptr;
    QFile *m_file=nullptr;
    QString path;
    QEventLoop *loop;
};

#endif // DOWNLOAD_H
