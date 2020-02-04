#ifndef HTTPTHREAD_H
#define HTTPTHREAD_H

#include <QThread>
#include <QNetworkReply>
#include <QQueue>

class DownloadData;
class DownloadFile;

class HttpThread : public QThread
{
    Q_OBJECT
public:
    explicit HttpThread();
    void Set(DownloadData* data);
    bool isDownloading()const;
    void Stop();
signals:
    void sslError(const QList<QSslError> &errors);
    void error(QNetworkReply::NetworkError code);
    void finished(QString fileName);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void Test();
protected:
    void run() Q_DECL_OVERRIDE;

private:
    bool isRun=true;
    DownloadData* data=nullptr;
    DownloadFile *download;
};

#endif // HTTPTHREAD_H
