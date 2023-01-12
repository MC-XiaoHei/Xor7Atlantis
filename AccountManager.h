#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "stable.h"
#include "UpdateManager.h"
#include "AuthCore.h"

class AccountManager : public QObject
{
    Q_OBJECT
public:
    explicit AccountManager(QObject *parent = nullptr);
    void read();
    void save();
    QList<AuthProfile*> getMinecraftProfiles();
    void chooseMinecraftProfile(quint64 n);
    void pushMinecraftProfile(AuthProfile* profile);
    AuthProfile* getNowMinecraftProfile();
    qsizetype minecraftProfileSize();

    QList<OpenFrpProfile*> getOpenFrpProfiles();
    void chooseOpenFrpProfile(quint64 n);
    void pushOpenFrpProfile(OpenFrpProfile* profile);
    OpenFrpProfile* getNowOpenFrpProfile();
    qsizetype openFrpProfileSize();
signals:

private:
    quint64 mp_now=0,ofp_now;
    QList<AuthProfile*> minecraftProfiles;
    QList<OpenFrpProfile*> openFrpProfiles;
};
Q_GLOBAL_STATIC(AccountManager,Account);

#endif // ACCOUNTMANAGER_H
