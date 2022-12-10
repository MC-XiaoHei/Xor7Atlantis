#include "Shell.h"

Shell::Shell(QObject *parent)
    : QObject{parent}
{

}
void Shell::start(QString name,QStringList argu){
    p=new QProcess(this);
    connect(p,&QProcess::readyReadStandardOutput,this,[=](){emit onReceive(p->readAll());});
    p->setProcessChannelMode(QProcess::MergedChannels);
    p->start(name,argu);
}
void Shell::waitForFinished(){
    p->waitForFinished();
}
void Shell::write(QString data){
    p->write(data.toLocal8Bit());
}
