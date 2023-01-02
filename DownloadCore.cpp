#include "DownloadCore.h"

bool DownloadCore::CheckFileHash(QString srcDir,QString hash){
    QFile file(srcDir);
    QCryptographicHash Hash(QCryptographicHash::Sha1);
    if(file.open(QIODevice::ReadOnly)){
        while(file.atEnd() == false){
            QByteArray message = file.readAll();
            Hash.addData(message);
        }
    }
    else{
        throwX("文件SHA1哈希检验","无法打开文件："+srcDir,0);
        return false;
    }
    QString sha1 = Hash.result();
    if(sha1==hash) return true;
    return false;
}
DownloadCore::DownloadCore(QObject *parent) :QObject(parent){
    state = Waiting;
    file = NULL;
}
qint64 DownloadCore::getFileSize(QString url ,int tryTimes){
    qint64 size = -1;
    while(tryTimes --){
        QNetworkAccessManager manager;
        QEventLoop loop;
        QNetworkReply *reply = manager.head(QNetworkRequest(url));
        if(!reply)continue;
        connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        loop.exec();
        if(reply->error() != QNetworkReply::NoError){
            errorInfo = reply->errorString();
            continue;
        }
        QVariant var = reply->header(QNetworkRequest::ContentLengthHeader);
        reply->deleteLater();
        size = var.toLongLong();
        break;
    }
    return size;
}
bool DownloadCore::downloadFile(QString _url, QString _saveFile, int _count){
    if(state == Downloading){
        errorInfo = "is downloading a file";
        emit error(0,errorInfo);
        return false;
    }
    if(file != NULL){
        errorInfo = "unknow error";
        emit error(0,errorInfo);
        return false;
    }
    url = _url;
    saveFile = _saveFile;
    count = _count;
    if(count < 1){
        errorInfo = "to few threads";
        emit error(0,errorInfo);
        return false;
    }
    if(count > 15){
        errorInfo = "to many threads";
        emit error(0,errorInfo);
        return false;
    }
    totalSize = getFileSize(url);
    if(totalSize == -1) return false;
    readySize = 0;
    file = new QFile(saveFile,this);
    if(!file->open(QFile::WriteOnly)){
        errorInfo = "can not open file : \n" + file->errorString();
        file->close();
        file = NULL;
        emit error(0,errorInfo);
        return false;
    }
    file->resize(totalSize);
    threads.clear();
    for(int i = 0;i < count;i ++){
        qint64 startPoint = totalSize * i / count;
        qint64 endPoint = totalSize * (i + 1) / count;
        DownloadThread *thread = new DownloadThread(this);
        connect(thread,SIGNAL(finished(int)),SLOT(finishedSlot(int)));
        connect(thread,SIGNAL(progressChange(int,qint64,qint64,qint64)),SLOT(progressChangeSlot(int,qint64,qint64,qint64)));
        connect(thread,SIGNAL(error(int,QString)),SLOT(errorSlot(int,QString)));
        thread->startDownload(i + 1,url,file,startPoint,endPoint);
        threads.append(thread);
    }
    state = Downloading;
    runningCount = count;
    return true;
}
void DownloadCore::downloadingFinish(){
    file->flush();
    file->close();
    file = NULL;
    state = Finished;
    foreach(DownloadThread *thread,threads) thread->deleteLater();
    threads.clear();
    emit finished(0);
}
void DownloadCore::pause(){
    if(state != Downloading){
        errorInfo = "is not downloading";
        emit error(0,errorInfo);
        return;
    }
    state = Pause;
    foreach(DownloadThread *thread,threads) thread->stop();
}
void DownloadCore::restart(){
    if(state != Pause){
        errorInfo = "is not paused";
        emit error(0,errorInfo);
        return;
    }
    state = Downloading;
    foreach(DownloadThread *thread,threads) thread->restart();
}
void DownloadCore::finishedSlot(int index){
    runningCount --;
    if(runningCount == 0 && state == Downloading) downloadingFinish();
    emit finished(index);
}
void DownloadCore::progressChangeSlot(int index, qint64 startPoint, qint64 endPoint, qint64 readySize){
    this->readySize = 0;
    foreach(DownloadThread *thread,threads) this->readySize += thread->readySize;
    emit progressChange(index,startPoint,endPoint,readySize);
    emit progressChange(0,0,totalSize,this->readySize);
}
void DownloadCore::errorSlot(int index, QString errorString){
    threads.at(index-1)->stop();
    emit error(index,errorString);
}
