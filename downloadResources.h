#ifndef DONWLOADRESOURCES_H
#define DONWLOADRESOURCES_H

#include <QThread>
#include<QNetworkReply>
#include <QStack>
class DownloadData;
class HttpThread;

class DownloadResources : public QThread
{
    Q_OBJECT
public:
    explicit DownloadResources(QObject *parent = 0);
    void GetUrl(DownloadData*);
    void maxThread(int max);
    void Stop();

signals:
    void sslError(const QList<QSslError> &errors);
    void error(QNetworkReply::NetworkError code);
    void finished(QString fileName);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);


public slots:


protected:
    void run() Q_DECL_OVERRIDE;

private:
    int max=5;
    bool isRun=true;
    QStack<DownloadData*> queue;
    QList<HttpThread*> boreds;//空闲
    QList<HttpThread*> busyness;//繁忙
};

#endif // DONWLOADRESOURCES_H
