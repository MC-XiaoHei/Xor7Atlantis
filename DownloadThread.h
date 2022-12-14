#ifndef DOWNLOADTHREAD_H
#define DOWNLOADTHREAD_H

#include "stable.h"

class DownloadThread : public QObject{
    Q_OBJECT
public:
    enum State{Waiting,Downloading,Finished,Stoped};
    explicit DownloadThread(QObject *parent = 0);
    void startDownload(int _index,QString _url,QFile *_file,qint64 _startPoint,qint64 _endPoint,qint64 _readySize = 0);
    State getState(){return state;};
    QString errorString(){return errorInfo;};
    int index;
    qint64 startPoint;
    qint64 endPoint;
    qint64 readySize;
signals:
    void finished(int index);
    void progressChange(int index,qint64 startPoint,qint64 endPoint,qint64 readySize);
    void error(int index, QString errorString);
public slots:
    void stop();
    void restart();
private slots:
    void finishedSlot();
    void readyReadSlot();
    void errorSlot(QNetworkReply::NetworkError code);
private:
    QString url;
    QFile *file;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    State state;
    QString errorInfo;
};

#endif // DOWNLOADTHREAD_H
