#ifndef DOWNLOADCORE_H
#define DOWNLOADCORE_H

#include "stable.h"
#include "DownloadThread.h"

class DownloadCore : public QObject{
    Q_OBJECT
public:
    bool CheckFileHash(QString srcDir,QString hash);
    enum State{Waiting,Downloading,Pause,Stop,Finished};
    explicit DownloadCore(QObject *parent = 0);
    QString errorString(){return errorInfo;};
    qint64 getFileSize(QString url, int tryTimes = 3);
    bool downloadFile(QString _url, QString _saveFile, int _count);
    State getState(){return state;}
    QString getUrl(){return url;}
    QString getSaveFile(){return saveFile;}
    int getCount(){return count;}
    int getRunningCount(){return runningCount;}
signals:
    void finished(int index);
    void progressChange(int index,qint64 startPoint,qint64 endPoint,qint64 readySize);
    void error(int index, QString errorString);
public slots:
    void pause();
    void restart();
private slots:
    void finishedSlot(int index);
    void progressChangeSlot(int index,qint64 startPoint,qint64 endPoint,qint64 readySize);
    void errorSlot(int index, QString errorString);
private:
    void downloadingFinish();
    QString errorInfo;
    State state;
    QVector<DownloadThread*> threads;
    QString url;
    QString saveFile;
    int count,runningCount;
    qint64 readySize,totalSize;
    QFile *file;
};

#endif // DOWNLOADCORE_H
