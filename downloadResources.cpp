#include "downloadResources.h"
#include "httpthread.h"
#include <QDebug>

DownloadResources::DownloadResources(QObject *parent) : QThread(parent)
{

    maxThread(max);
}

void DownloadResources::GetUrl(DownloadData *data)
{
    queue.push(data);
}

void DownloadResources::maxThread(int max)
{
    for(int i=0;i<max;i++){
        auto thread = new HttpThread;
        boreds.append(thread);

        connect(thread,&HttpThread::error,this,&DownloadResources::error);
        connect(thread,&HttpThread::downloadProgress,this,&DownloadResources::downloadProgress);
        connect(thread,&HttpThread::sslError,this,&DownloadResources::sslError);
        connect(thread,&HttpThread::finished,this,[=](QString fileName){
                boreds.append(thread);
                busyness.removeOne(thread);
                emit finished(fileName);
        });


        thread->start();
    }
}

void DownloadResources::Stop()
{
    isRun=false;
}


void DownloadResources::run()
{
    while(isRun){
        if(queue.isEmpty()||boreds.count()<=0){
            QThread::sleep(1);
            continue;
        }
        auto thread = boreds.at(0);
        boreds.removeAt(0);
        busyness.append(thread);
        thread->Set(queue.pop());
    }

    boreds.clear();
    busyness.clear();
    queue.clear();
}





















