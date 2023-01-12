#include "MainWidget.h"
#include "AccountManager.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    //开启鼠标跟踪
    this->setMouseTracking(true);
    //控件初始化
    Account->read();
    m_verInfo->setParent(parent);
    m_closeBtnBg->setParent(parent);
    m_minisizeBtnBg->setParent(parent);
    m_closeBtn->setParent(parent);
    m_minisizeBtn->setParent(parent);
    m_accountHeadLayer1->setParent(parent);
    m_accountHeadLayer2->setParent(parent);
    m_accountUsername->setParent(parent);
    m_accountInfo->setParent(parent);
    //更改控件位置
    m_background->move(0,0);
    //设置控件
    setBackground(QImage(":/Images/background.png"));
    m_closeBtn->setIcon(QIcon(":/Images/Icon/Close.png"));
    m_minisizeBtn->setIcon(QIcon(":/Images/Icon/Minisize.png"));
    m_minisizeBtn->setStyleSheet("background-color:rgba(255,255,255,0);"
                                 "border-radius:0px;");
    m_accountInfo->setStyleSheet("color:rgb(56,56,56)");
    m_closeBtn->setStyleSheet(m_minisizeBtn->styleSheet());
    m_verInfo->setText(QString("Xor 7 Atlantis %1").arg(X7A_VER));
    //设置侧边栏
    SelfLockBtnBgGroupConfig cfg;
    cfg.color="255,255,255";
    cfg.basePoint=QPoint(1,92);
    cfg.bgSize=QSize(213,36);
    cfg.btnSize=QSize(244,41);
    SideBarBtn *homeBtn=new SideBarBtn(
                1,cfg,"主页",":/Images/Icon/Home.png",this);
    m_sideBarBtns.insert("home",homeBtn);
    SideBarBtn *instanceSettingsBtn=new SideBarBtn(
                2,cfg,"没有游戏",":/Images/Icon/InstanceSettings.png",this);
    instanceSettingsBtn->setPageName("版本设置");
    m_sideBarBtns.insert("instanceSettings",instanceSettingsBtn);
    SideBarBtn *instanceListBtn=new SideBarBtn(
                3,cfg,"游戏列表",":/Images/Icon/InstanceList.png",this);
    m_sideBarBtns.insert("instanceList",instanceListBtn);
    SideBarBtn *accountManageBtn=new SideBarBtn(
                4,cfg,"账号管理",":/Images/Icon/AccountManage.png",this);
    m_sideBarBtns.insert("accountManage",accountManageBtn);
    SideBarBtn *multiplayerGameBtn=new SideBarBtn(
                5,cfg,"联机",":/Images/Icon/MultiplayerGame.png",this);
    m_sideBarBtns.insert("multiplayerGame",multiplayerGameBtn);
    SideBarBtn *settingsBtn=new SideBarBtn(
                6,cfg,"设置",":/Images/Icon/Settings.png",this);
    m_sideBarBtns.insert("settings",settingsBtn);
    SideBarBtn *helpBtn=new SideBarBtn(
                7,cfg,"帮助",":/Images/Icon/Help.png",this);
    m_sideBarBtns.insert("help",helpBtn);
    for(const auto &key:m_sideBarBtns.keys()){
        SideBarBtn *btn=m_sideBarBtns.value(key);
        connect(btn,&SideBarBtn::clicked,this,[=](){
            switchPage(key);
            m_sideBarBtns.value(m_nowSideBarBtn)->release();
            m_nowSideBarBtn=key;
            m_pageName->setText(btn->getName());
            btn->click();
        });
    }
    homeBtn->setDefault();
    //设置界面
    m_pages.insert("home",homePage);
    m_pages.insert("instanceSettings",instanceSettingsPage);
    m_pages.insert("instanceList",instanceListPage);
    m_pages.insert("accountManage",accountManagePage);
    amp_MinecraftAccountTitle->setText("Minecraft账号");
    amp_MinecraftAccountTitle->setStyleSheet("background-color:rgba(255,255,255,0);"
                                             "color:rgba(56,56,56,255);");
    amp_BuyMinecraftLink->setText("购买正版账号");
    amp_BuyMinecraftLink->setStyleSheet("background-color:rgba(255,255,255,0);"
                                        "color:rgba(42,130,228,255);");
    amp_AddMinecraftAccount->setStyleSheet("background-color:rgba(255,255,255,0);");
    amp_OpenFrpAccountTitle->setText("OpenFrp账号");
    amp_OpenFrpAccountTitle->setStyleSheet("background-color:rgba(255,255,255,0);"
                                           "color:rgba(56,56,56,255);");
    amp_BuyOpenFrpVASLink->setText("购买增值服务");
    amp_BuyOpenFrpVASLink->setStyleSheet("background-color:rgba(255,255,255,0);"
                                         "color:rgba(42,130,228,255);");
    amp_OpenFrpAccountAPIText->setText("联机功能使用OpenFrp OPENAPI");
    amp_OpenFrpAccountAPIText->setStyleSheet("background-color:rgba(255,255,255,0);"
                                             "color:rgba(128,128,128,255);");
    amp_SignInBtn->setText("一键签到");
    amp_SignInBtn->setStyleSheet("background-color:rgba(255,255,255,0);"
                                 "color:rgba(42,130,228,255);");
    amp_AddOpenFrpAccount->setStyleSheet("background-color:rgba(255,255,255,0);");
    amp_ThirdAccountServerTitle->setText("第三方认证服务器");
    amp_ThirdAccountServerTitle->setStyleSheet("background-color:rgba(255,255,255,0);"
                                               "color:rgba(56,56,56,255);");
    amp_AddThirdAccountServer->setStyleSheet("background-color:rgba(255,255,255,0);");
    m_pages.insert("multiplayerGame",multiplayerGamePage);
    m_pages.insert("settings",settingsPage);
    m_pages.insert("help",helpPage);
    //链接事件和槽
    connect(m_closeBtn,&QPushButton::clicked,this,&MainWidget::closeWindow);
    connect(m_minisizeBtn,&QPushButton::clicked,this,&MainWidget::minimizeWindow);
    //后处理
    homePage->show();
    m_pageName->setText("主页");
    onTimerEvent();
    startTimer(50);
}
void MainWidget::onTimerEvent(){
    //设置控件
    m_accountUsername->setText(Account->getNowMinecraftProfile()->username);
    QString authInfo,authServer=Account->getNowMinecraftProfile()->authServer;
    if(authServer=="offline") authInfo="离线账户";
    else if(authServer=="microsoft") authInfo="微软账户";
    else{
        authServer=authServer.split(":")[0];
        if(authServer=="authlib") authInfo="外置登录账户";
        else if(authServer=="universal") authInfo="统一通行证账户";
    }
    m_accountInfo->setText(Account->getNowMinecraftProfile()->extraInfo+" "+authInfo);
    QImage skin=QImage(AuthCore::getSkin(*Account->getNowMinecraftProfile()));
    m_accountHeadLayer1->setPixmap(QPixmap::fromImage(skin.copy(8,8,8,8).scaled(ZOOM(55),ZOOM(55))));
    m_accountHeadLayer2->setPixmap(QPixmap::fromImage(skin.copy(40,8,8,8).scaled(ZOOM(65),ZOOM(64))));
    //处理最小化以及关闭按钮的背景
    if(m_closeBtn->underMouse())
        closeBtnAlpha=Min(255,closeBtnAlpha+100);
    else
        closeBtnAlpha=Max(0,closeBtnAlpha-100);
    if(m_minisizeBtn->underMouse())
        minisizeBtnAlpha=Min(255,minisizeBtnAlpha+100);
    else
        minisizeBtnAlpha=Max(0,minisizeBtnAlpha-100);
    m_minisizeBtnBg->setStyleSheet(QString(
        "background-color:rgba(229,229,229,%1);"
        "border-radius:0px;")
        .arg(QString::number(minisizeBtnAlpha)));
    m_closeBtnBg->setStyleSheet(QString(
        "background-color:rgba(250,77,77,%1);"
        "border-radius:0px;"
        "border-top-right-radius:%2px;")
        .arg(QString::number(closeBtnAlpha),QString::number(ZOOM(7))));
}
void MainWidget::switchPage(QString name){
    if(name==m_nowPage) return;
    m_pages.value(m_nowPage)->hide();
    m_pages.value(name)->show();
    m_nowPage=name;
}
void MainWidget::refreshAMP(){
    amp_MinecraftAccountAreaBg->resize(ZOOM(480),
                                       ZOOM(73)+Account->minecraftProfileSize()*ZOOM(56));
    amp_OpenFrpAccountAreaBg->resize(ZOOM(480),
                                     ZOOM(73)+Account->openFrpProfileSize()*ZOOM(56));
    amp_ThirdAccountServerAreaBg->resize(ZOOM(480),
                                         ZOOM(73)/*+Account->thirdAccountServerSize()*ZOOM(56)*/);
    amp_OpenFrpAccountAreaBg->move(0,
                                   amp_MinecraftAccountAreaBg->height()+ZOOM(12));
    amp_ThirdAccountServerAreaBg->move(0,
                                       amp_OpenFrpAccountAreaBg->geometry().bottom()+ZOOM(12));
    qDeleteAll(amp_minecraftAccountBtns);
    amp_minecraftAccountBtns.clear();
    SelfLockBtnBgGroupConfig maCfg;
    maCfg.basePoint=QPoint(16,40);
    maCfg.bgSize=maCfg.btnSize=QSize(448,48);
    maCfg.color="191,215,242";
    for(int i=1;i<=Account->minecraftProfileSize();i++){
        AuthProfile* profile=Account->getMinecraftProfiles().at(i-1);
        MinecraftAccountBtn* btn=new MinecraftAccountBtn(
                    i,
                    maCfg,
                    profile,
                    amp_MinecraftAccountAreaBg);
        connect(btn,&MinecraftAccountBtn::clicked,this,[=](){
            Account->chooseMinecraftProfile(
                        Account->getMinecraftProfiles().indexOf(profile));
            if(amp_nowMinecraftAccountBtn!=nullptr)
                amp_minecraftAccountBtns.value(amp_nowMinecraftAccountBtn)->release();
            amp_nowMinecraftAccountBtn=profile;
            btn->click();
        });
        amp_minecraftAccountBtns.insert(profile,btn);
    }
}
void MainWidget::resizeEvent(QResizeEvent* event){
    Q_UNUSED(event);
    ON_ZOOM_UPDATE{//执行仅需要在缩放时
        //更改控件位置
        m_mask->move(ZOOM(1),ZOOM(1));
        m_accountHeadLayer2->move(ZOOM(19),
                                  ZOOM(16));
        m_accountHeadLayer1->move(m_accountHeadLayer2->x()+ZOOM(5.5),
                                  m_accountHeadLayer2->y()+ZOOM(4.5));
        m_accountUsername->move(ZOOM(96),
                                ZOOM(27));
        m_accountInfo->move(ZOOM(96),
                            ZOOM(51));
        amp_MinecraftAccountTitle->move(ZOOM(16),
                                        ZOOM(10));
        amp_OpenFrpAccountTitle->move(ZOOM(16),
                                      ZOOM(10));
        amp_ThirdAccountServerTitle->move(ZOOM(16),
                                          ZOOM(10));
        //更改控件大小
        amp_AddMinecraftAccount->resize(ZOOM(32),
                                        ZOOM(32));
        amp_AddOpenFrpAccount->resize(ZOOM(32),
                                      ZOOM(32));
        amp_AddThirdAccountServer->resize(ZOOM(32),
                                          ZOOM(32));
        amp_area->body()->setMinimumWidth(ZOOM(480));
        m_pageName->resize(ZOOM(480),
                           ZOOM(27));
        m_accountHeadLayer1->resize(ZOOM(55),
                                    ZOOM(55));
        m_accountHeadLayer2->resize(ZOOM(64),
                                    ZOOM(64));
        m_accountUsername->resize(ZOOM(149),
                                  ZOOM(24));
        m_accountInfo->resize(ZOOM(149),
                              ZOOM(15));
        m_verInfo->resize(ZOOM(271),
                          ZOOM(18));
        m_minisizeBtn->resize(ZOOM(46),
                             ZOOM(31));
        m_minisizeBtnBg->resize(m_minisizeBtn->size());
        m_closeBtn->resize(ZOOM(46),
                           ZOOM(31));
        m_closeBtnBg->resize(m_closeBtn->size());
        //设置控件
        m_minisizeBtn->setIconSize(m_minisizeBtn->size());
        m_closeBtn->setIconSize(m_closeBtn->size());
        m_mask->setStyleSheet(QString(
            "background-color:rgba(255,255,255,173);"
            "border-radius:%1px;")
            .arg(ZOOM(7)));
        amp_MinecraftAccountAreaBg->setStyleSheet(QString(
            "background-color:rgba(255,255,255,163);"
            "border-radius:%1px;")
            .arg(ZOOM(8)));
        amp_OpenFrpAccountAreaBg->setStyleSheet(amp_MinecraftAccountAreaBg->styleSheet());
        amp_ThirdAccountServerAreaBg->setStyleSheet(amp_MinecraftAccountAreaBg->styleSheet());
        QFont font;
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setPixelSize(ZOOM(18));
        m_pageName->setFont(font);
        font.setPixelSize(ZOOM(16));
        m_accountUsername->setFont(font);
        font.setPixelSize(ZOOM(12));
        amp_BuyMinecraftLink->setFont(font);
        amp_BuyOpenFrpVASLink->setFont(font);
        amp_OpenFrpAccountAPIText->setFont(font);
        amp_SignInBtn->setFont(font);
        amp_OpenFrpAccountTitle->setFont(font);
        amp_ThirdAccountServerTitle->setFont(font);
        amp_MinecraftAccountTitle->setFont(font);
        m_verInfo->setFont(font);
        m_accountInfo->setFont(font);
        m_verInfo->setStyleSheet("color:rgb(128,128,128)");
        amp_BuyMinecraftLink->resize(getBtnTextSize(amp_BuyMinecraftLink));
        amp_BuyOpenFrpVASLink->resize(getBtnTextSize(amp_BuyOpenFrpVASLink));
        amp_SignInBtn->resize(getBtnTextSize(amp_SignInBtn));
        refreshAMP();
    UPDATE_OVER;}
    //设置pages
    for(auto page:m_pages.values()){
        page->resize(this->width()-ZOOM(246),
                     this->height()-ZOOM(66));
        page->move(ZOOM(246),
                   ZOOM(58));
        page->refresh();
        page->raise();
    }
    //更改控件位置
    amp_AddMinecraftAccount->move(ZOOM(448),
                                  0);
    amp_AddOpenFrpAccount->move(ZOOM(448),
                                0);
    amp_AddThirdAccountServer->move(ZOOM(448),
                                    0);
    amp_BuyMinecraftLink->move(ZOOM(464)-amp_BuyMinecraftLink->width(),
                               amp_MinecraftAccountAreaBg->height()-ZOOM(25));
    amp_BuyOpenFrpVASLink->move(ZOOM(464)-amp_BuyOpenFrpVASLink->width(),
                                amp_OpenFrpAccountAreaBg->height()-ZOOM(25));
    amp_SignInBtn->move(amp_BuyOpenFrpVASLink->x()-ZOOM(12)-amp_SignInBtn->width(),
                        amp_OpenFrpAccountAreaBg->height()-ZOOM(25));
    amp_OpenFrpAccountAPIText->move(ZOOM(16),
                                    amp_OpenFrpAccountAreaBg->height()-ZOOM(25));
    m_pageName->move((this->width()-ZOOM(726))/2+ZOOM(246),
                     ZOOM(30));
    m_verInfo->move(ZOOM(17),
                    this->height()-ZOOM(26));
    m_closeBtn->move(this->width()-ZOOM(47),
                     ZOOM(1));
    m_minisizeBtn->move(this->width()-ZOOM(93),
                        ZOOM(1));
    m_closeBtnBg->move(m_closeBtn->pos());
    m_minisizeBtnBg->move(m_minisizeBtn->pos());
    //更改控件大小
    amp_area->resize(accountManagePage->size());
    m_mask->resize(this->width()-ZOOM(2),
                   this->height()-ZOOM(2));
    m_background->resize(this->size());
    //背景图片大小
    QSize imageSize;
    //背景图片宽高比
    double Iproportion=m_bg.width()/
                       m_bg.height();
    //将背景图片宽高比与窗口宽高比比较
    if(Iproportion>=(this->size().width()*1.00/
                     this->size().height()))
        //背景图片的宽相对更大/高相对更小，按照高等比缩放
        imageSize=QSize(this->size().height()*Iproportion,this->size().height());
    else
        //背景图片的宽相对更小/高相对更大，按照宽等比缩放
        imageSize=QSize(this->size().width(),this->size().width()/Iproportion);
    //缩放图片
    QImage image = m_bg.scaled(imageSize);
    //截取所需区域（防止拉伸图片）
    image=image.copy(0,0,this->size().width(),this->size().height());
    //设置背景
    QPixmap pixmap = QPixmap::fromImage(image);
    m_background->setPixmap(pixmap);
    //设置模糊效果
    QGraphicsBlurEffect *blureffect = new QGraphicsBlurEffect;
    blureffect->setBlurRadius(ZOOM(12));
    m_background->setGraphicsEffect(blureffect);
    //设置层级关系
    m_accountHeadLayer1->raise();
    m_accountHeadLayer2->raise();
    m_accountInfo->raise();
    m_accountUsername->raise();
    m_minisizeBtn->raise();
    m_closeBtn->raise();
    m_verInfo->raise();
    m_pageName->raise();
}
