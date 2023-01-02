#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include "stable.h"

class UpdateManager : public QObject
{
    Q_OBJECT
public:
    explicit UpdateManager(QObject *parent = nullptr);
    QString read();
    void checkInstance();
    QString cfgPath=RootPath"config/";
signals:

};
Q_GLOBAL_STATIC(UpdateManager,UpdateManagerInstance);
#define CfgPath UpdateManagerInstance->cfgPath
#endif // UPDATEMANAGER_H
