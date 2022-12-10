//#ifndef DOWNLOAD_CORE_H
//#define DOWNLOAD_CORE_H
//#include "launch-core.h"
//#include "cfg-core.h"
//#include "mainwindow.h"
//#include "api-core.h"
////改编于 百度贴吧 的一位大佬的帖子
////因系统重装导致浏览器历史记录丢失无法找到原帖
////如原作者见到此信息请联系我加入开发者名单
//#include "main.h"
//class DownloadThread : public QObject
//{
//    Q_OBJECT
//public:
//    enum State{Waiting,Downloading,Finished,Stoped};
//    explicit DownloadThread(QObject *parent = 0);
//    void startDownload(int _index,QString _url,QFile *_file,qint64 _startPoint,qint64 _endPoint,qint64 _readySize = 0);
//    State getState(){return state;};
//    QString errorString(){return errorInfo;};
//    int index;
//    qint64 startPoint;
//    qint64 endPoint;
//    qint64 readySize;
//signals:
//    void finished(int index);
//    void progressChange(int index,qint64 startPoint,qint64 endPoint,qint64 readySize);
//    void error(int index, QString errorString);
//public slots:
//    void stop();
//    void restart();
//private slots:
//    void finishedSlot();
//    void readyReadSlot();
//    void errorSlot(QNetworkReply::NetworkError code);
//private:
//    QString url;
//    QFile *file;
//    QNetworkAccessManager *manager;
//    QNetworkReply *reply;
//    State state;
//    QString errorInfo;
//};
//class DownloadCore : public QObject{
//    Q_OBJECT
//public:
//    bool CheckFileHash(QString srcDir,QString hash);
//    enum State{Waiting,Downloading,Pause,Stop,Finished};
//    explicit DownloadCore(QObject *parent = 0);
//    QString errorString(){return errorInfo;};
//    qint64 getFileSize(QString url, int tryTimes = 3);
//    bool downloadFile(QString _url, QString _saveFile, int _count);
//    State getState(){return state;}
//    QString getUrl(){return url;}
//    QString getSaveFile(){return saveFile;}
//    int getCount(){return count;}
//    int getRunningCount(){return runningCount;}
//signals:
//    void finished(int index);
//    void progressChange(int index,qint64 startPoint,qint64 endPoint,qint64 readySize);
//    void error(int index, QString errorString);
//public slots:
//    void pause();
//    void restart();
//private slots:
//    void finishedSlot(int index);
//    void progressChangeSlot(int index,qint64 startPoint,qint64 endPoint,qint64 readySize);
//    void errorSlot(int index, QString errorString);
//private:
//    void downloadingFinish();
//    QString errorInfo;
//    State state;
//    QVector<DownloadThread*> threads;
//    QString url;
//    QString saveFile;
//    int count,runningCount;
//    qint64 readySize,totalSize;
//    QFile *file;
//};
//#endif
