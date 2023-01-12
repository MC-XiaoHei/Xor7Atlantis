#ifndef MINECRAFTACCOUNTBTN_H
#define MINECRAFTACCOUNTBTN_H

#include "AuthCore.h"
#include "SelfLockBtnBgInGroup.h"
#include "stable.h"

class MinecraftAccountBtn : public SelfLockBtnBgInGroup
{
    Q_OBJECT
public:
    explicit MinecraftAccountBtn(quint64 index,SelfLockBtnBgGroupConfig cfg,AuthProfile *profile,QWidget *parent = nullptr);

signals:

private:
    AuthProfile *m_profile;
    QLabel *l_icon,*l_name,*l_authServer;
};

#endif // MINECRAFTACCOUNTBTN_H
