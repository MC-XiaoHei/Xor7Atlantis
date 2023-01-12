#include "MinecraftAccountBtn.h"

MinecraftAccountBtn::MinecraftAccountBtn(quint64 index,SelfLockBtnBgGroupConfig cfg,AuthProfile *profile,QWidget *parent)
    : SelfLockBtnBgInGroup{index,cfg,parent}
{
    m_profile=profile;
    l_icon=new QLabel(parent);
    l_name=new QLabel(parent);
    l_authServer=new QLabel(parent);
    l_name->setText(profile->username);
    l_authServer->setText(profile->authServer);
    connect(this,&SelfLockBtnBgInGroup::onRefresh,this,[=](){
        QFont font;
        font.setPixelSize(14);
        l_name->setFont(font);
        font.setPixelSize(12);
        l_authServer->setFont(font);
        qDebug()<<AuthCore::getSkin(*m_profile);
        QPixmap icon=QPixmap(AuthCore::getSkin(*m_profile));
        l_icon->setPixmap(icon.scaled(ZOOM(32),
                                      ZOOM(32),
                                      Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation));
        l_icon->resize(ZOOM(32),
                       ZOOM(32));
        l_icon->move(btn->x()+ZOOM(12),
                     btn->y()+ZOOM(7));
        l_name->resize(ZOOM(300),
                       ZOOM(21));
        l_name->move(btn->x()+ZOOM(52),
                     btn->y()+ZOOM(4));
        l_authServer->resize(ZOOM(300),
                             ZOOM(18));
        l_authServer->move(btn->x()+ZOOM(52),
                           btn->y()+ZOOM(23));
        l_icon->raise();
        l_name->raise();
    });
    refresh();
}
