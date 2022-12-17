#include "DownloadThread.h"

DownloadThread::DownloadThread(QObject *parent):QObject(parent){
    manager = new QNetworkAccessManager(this);
    state = Waiting;
    index = 0;
}
void DownloadThread::startDownload(int _index, QString _url, QFile *_file, qint64 _startPoint, qint64 _endPoint, qint64 _readySize){
    if(state == Downloading){
        errorInfo = "is downloading a file";
        emit error(index,errorInfo);
        return;
    }
    index = _index;
    url = _url;
    file = _file;
    startPoint = _startPoint;
    endPoint = _endPoint;
    readySize = _readySize;
    QNetworkRequest request;
    request.setUrl(_url);
    QString range = QString( "bytes=%0-%1" ).arg( startPoint + readySize ).arg( endPoint );
    request.setRawHeader("Range", range.toLatin1());
    reply = manager->get(request);
    connect(reply,SIGNAL(finished()),SLOT(finishedSlot()));
    connect(reply,SIGNAL(readyRead()),SLOT(readyReadSlot()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),SLOT(errorSlot(QNetworkReply::NetworkError)));
    state = Downloading;
    emit progressChange(index,startPoint,endPoint,readySize);
}
void DownloadThread::stop(){
    if(state != Downloading){
        errorInfo = "is not downloading";
        emit error(index,errorInfo);
        return;
    }
    state = Stoped;
    reply->abort();
    file->flush();
    reply->deleteLater();
}
void DownloadThread::restart(){
    if(state != Stoped){
        errorInfo = "is not stoped";
        emit error(index,errorInfo);
        return;
    }
    startDownload(index,url,file,startPoint,endPoint,readySize);
}
void DownloadThread::finishedSlot(){
    if(state != Downloading)return;
    file->flush();
    reply->deleteLater();
    state = Finished;
    emit finished(index);
}
void DownloadThread::readyReadSlot(){
    QByteArray buffer = reply->readAll();
    file->seek( startPoint + readySize );
    file->write(buffer);
    readySize += buffer.size();
    emit progressChange(index,startPoint,endPoint,readySize);
}
void DownloadThread::errorSlot(QNetworkReply::NetworkError code){
    if(state != Downloading)return;
    errorInfo = "QNetworkReply::NetworkError : " + QString::number((int)code) + " \n" + reply->errorString();
    stop();
    emit error(index,errorInfo);
}
