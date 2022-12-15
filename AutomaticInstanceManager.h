#ifndef AUTOMATICINSTANCEMANAGER_H
#define AUTOMATICINSTANCEMANAGER_H

#include "stable.h"
#include "Settings.h"

class AutomaticInstanceManager : public QObject
{
    Q_OBJECT
public:
    explicit AutomaticInstanceManager(QObject *parent = nullptr);
    QString read();
    void checkInstance();
signals:

};
Q_GLOBAL_STATIC(AutomaticInstanceManager,AutomaticInstanceManagerInstance);
#endif // AUTOMATICFILEMANAGE_H
