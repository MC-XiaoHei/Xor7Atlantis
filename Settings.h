#ifndef SETTINGS_H
#define SETTINGS_H

#include "stable.h"

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = nullptr);
    void set(QString key,QString value);
    void remove(QString key);
    QString get(QString key);
signals:

private:
    QMap<QString,QString> values;
};
Q_GLOBAL_STATIC(Settings,SettingsInstance);
#define GET(key) SettingsInstance->get(key)
#define REMOVE(key) SettingsInstance->remove(key)
#define SET(key,value) SettingsInstance->set(key,value)
#endif // SETTINGS_H
