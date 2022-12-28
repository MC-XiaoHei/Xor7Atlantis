#ifndef PROFILEMANAGER_H
#define PROFILEMANAGER_H

#include "stable.h"
#include "AuthCore.h"

class ProfileManager : public QObject
{
    Q_OBJECT
public:
    explicit ProfileManager(QObject *parent = nullptr);
    void read();
    QList<AuthProfile> getAll();
    AuthProfile get(quint16 n);
    AuthProfile now(quint16 n);
    void push_front(AuthProfile profile);
    void swap(quint16 a,quint16 b);
    void remove(quint16 n);
signals:

private:
    AuthProfile nowProfile;
    QList<AuthProfile> profiles;
};
Q_GLOBAL_STATIC(ProfileManager,Profile)

#endif // PROFILEMANAGER_H
