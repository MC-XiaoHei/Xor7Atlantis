#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "stable.h"
#include "UpdateManager.h"
#include "AuthCore.h"

class ProfileManager : public QObject
{
    Q_OBJECT
public:
    explicit ProfileManager(QObject *parent = nullptr);
    void read();
    QList<AuthProfile*> getAll();
    AuthProfile* get(quint64 n);
    void choose(quint64 n);
    void push_front(AuthProfile* profile);
    void swap(quint64 a,quint64 b);
    void extracted(QJsonArray &array);
    void save();
    void remove(quint64 n);
    AuthProfile* getNow();
signals:

private:
    quint64 now=0;
    QList<AuthProfile*> profiles;
};
static ProfileManager Profile;
#define SKIN(uuid) QImage(QDir::toNativeSeparators(QString("%1/skin/%2.png").arg(CfgPath,uuid)))

#endif // PROFILEMANAGER_H
