#ifndef SHELL_H
#define SHELL_H
#include "stable.h"

class Shell : public QObject
{
    Q_OBJECT
public:
    explicit Shell(QObject *parent = nullptr);
    void start(QString name,QStringList argu);
    void write(QString data);
    void waitForFinished();
signals:
    void onReceive(QString data);
private:
    QProcess *p;
};

#endif // SHELL_H
