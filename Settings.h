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

#endif // SETTINGS_H
