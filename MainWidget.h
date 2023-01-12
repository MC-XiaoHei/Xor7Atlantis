#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "MinecraftAccountBtn.h"
#include "SideBarBtn.h"
#include "ScrollArea.h"
#include "SelfLockBtnBg.h"
#include "stable.h"
#include "Zoomer.h"
#include "Page.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void setBackground(QImage bg) { this->m_bg = bg; }
    void switchPage(QString name);
    void refreshAMP();
    void onTimerEvent();
signals:
    void closeWindow();
    void minimizeWindow();
private:
    bool flash=false;
    quint8 closeBtnAlpha=0,
           minisizeBtnAlpha=0;
    QImage m_bg;
    QLabel *m_accountHeadLayer1=new QLabel,
           *m_accountHeadLayer2=new QLabel,
           *m_accountUsername=new QLabel,
           *m_accountInfo=new QLabel,
           *m_background=new QLabel(this),
           *m_verInfo=new QLabel,
           *m_pageName=new QLabel(this);
    QPushButton *m_mask=new QPushButton(this),
                *m_closeBtn=new QPushButton,
                *m_minisizeBtn=new QPushButton,
                *m_closeBtnBg=new QPushButton,
                *m_minisizeBtnBg=new QPushButton;
    Page *homePage=new Page(this),
         *instanceSettingsPage=new Page(this),
         *instanceListPage=new Page(this),
         *accountManagePage=new Page(this),
         *multiplayerGamePage=new Page(this),
         *settingsPage=new Page(this),
         *helpPage=new Page(this);
    QMap<QString,SideBarBtn*> m_sideBarBtns;
    QMap<QString,Page*> m_pages;
    QString m_nowPage="home",
            m_nowSideBarBtn="home";
    //账号管理界面
    QMap<AuthProfile*,MinecraftAccountBtn*> amp_minecraftAccountBtns;
    AuthProfile* amp_nowMinecraftAccountBtn;
    ScrollArea *amp_area=new ScrollArea(accountManagePage);
    QPushButton *amp_MinecraftAccountAreaBg=new QPushButton(amp_area->body()),
                *amp_AddMinecraftAccount=new QPushButton(amp_MinecraftAccountAreaBg),
                *amp_OpenFrpAccountAreaBg=new QPushButton(amp_area->body()),
                *amp_AddOpenFrpAccount=new QPushButton(amp_OpenFrpAccountAreaBg),
                *amp_ThirdAccountServerAreaBg=new QPushButton(amp_area->body()),
                *amp_AddThirdAccountServer=new QPushButton(amp_ThirdAccountServerAreaBg),
                *amp_BuyMinecraftLink=new QPushButton(amp_MinecraftAccountAreaBg),
                *amp_SignInBtn=new QPushButton(amp_OpenFrpAccountAreaBg),
                *amp_BuyOpenFrpVASLink=new QPushButton(amp_OpenFrpAccountAreaBg);
    QLabel *amp_MinecraftAccountTitle=new QLabel(amp_MinecraftAccountAreaBg),
           *amp_OpenFrpAccountTitle=new QLabel(amp_OpenFrpAccountAreaBg),
           *amp_OpenFrpAccountAPIText=new QLabel(amp_OpenFrpAccountAreaBg),
           *amp_ThirdAccountServerTitle=new QLabel(amp_ThirdAccountServerAreaBg);
protected:
    void timerEvent(QTimerEvent *event){onTimerEvent();}
    void resizeEvent(QResizeEvent* event);
};

#endif // MAINWIDGET_H
