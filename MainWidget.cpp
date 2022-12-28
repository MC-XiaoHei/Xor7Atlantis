#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    //开启鼠标跟踪
    this->setMouseTracking(true);
    //控件初始化
    m_verInfo->setParent(parent);
    m_closeBtnBg->setParent(parent);
    m_minisizeBtnBg->setParent(parent);
    m_closeBtn->setParent(parent);
    m_minisizeBtn->setParent(parent);
    //更改控件位置
    m_background->move(0,0);
    //设置控件
    setBackground(QImage(":/Images/background.png"));
    m_closeBtn->setIcon(QIcon(":/Images/Icon/Close.png"));
    m_minisizeBtn->setIcon(QIcon(":/Images/Icon/Minisize.png"));
    m_minisizeBtn->setStyleSheet("background-color:rgba(255,255,255,0);"
                                 "border-radius:0px;");
    m_closeBtn->setStyleSheet(m_minisizeBtn->styleSheet());
    m_verInfo->setText(QString("Xor 7 Atlantis %1").arg(X7A_VER));
    //添加侧边栏
    SideBarBtn *homeBtn=new SideBarBtn(
                1,"主页",":/Images/Icon/Home.png",this);
    m_sideBarBtns.insert("home",homeBtn);
    SideBarBtn *instanceSettingsBtn=new SideBarBtn(
                2,"没有游戏",":/Images/Icon/InstanceSettings.png",this);
    m_sideBarBtns.insert("instanceSettings",instanceSettingsBtn);
    SideBarBtn *instanceListBtn=new SideBarBtn(
                3,"游戏列表",":/Images/Icon/InstanceList.png",this);
    m_sideBarBtns.insert("InstanceList",instanceListBtn);
    SideBarBtn *profileManageBtn=new SideBarBtn(
                4,"账号管理",":/Images/Icon/ProfileManage.png",this);
    m_sideBarBtns.insert("profileManage",profileManageBtn);
    SideBarBtn *multiplayerGameBtn=new SideBarBtn(
                5,"联机",":/Images/Icon/MultiplayerGame.png",this);
    m_sideBarBtns.insert("multiplayerGame",multiplayerGameBtn);
    SideBarBtn *settingsBtn=new SideBarBtn(
                6,"设置",":/Images/Icon/Settings.png",this);
    m_sideBarBtns.insert("settings",settingsBtn);
    SideBarBtn *helpBtn=new SideBarBtn(
                7,"帮助",":/Images/Icon/Help.png",this);
    m_sideBarBtns.insert("help",helpBtn);
    for(auto btn:qAsConst(m_sideBarBtns)){
        connect(btn,&SideBarBtn::clicked,this,[=](){
            if(m_nowSideBarBtn==m_sideBarBtns.key(btn)) return;
            m_sideBarBtns.value(m_nowSideBarBtn)->inactive();
            m_nowSideBarBtn=m_sideBarBtns.key(btn);
//                switchPage(m_nowSideBarBtn);
            btn->active();
        });
    }
    homeBtn->setAlpha(82);
    emit homeBtn->clicked();
    //链接事件和槽
    connect(m_closeBtn,&QPushButton::clicked,this,&MainWidget::closeWindow);
    connect(m_minisizeBtn,&QPushButton::clicked,this,&MainWidget::minimizeWindow);
    //启动定时事件
    onTimerEvent();
    startTimer(50);
}
void MainWidget::onTimerEvent(){
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
    m_pages.value(m_nowPage)->flashHide();
    m_pages.value(name)->flashShow();
    m_nowPage=name;
}
void MainWidget::resizeEvent(QResizeEvent* event){
    Q_UNUSED(event);
    ON_ZOOM_UPDATE{//执行仅需要在缩放时
        //更改控件位置
        m_mask->move(ZOOM(1),ZOOM(1));
        //更改控件大小
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
        QFont font;
        font.setPixelSize(ZOOM(12));
        m_verInfo->setFont(font);
        m_verInfo->setStyleSheet("color:rgb(128,128,128)");
        //清空之前的页面
        m_pages.clear();
        Page* homePage=new Page(this);
        homePage->flashHide();
        m_pages.insert("home",homePage);
    UPDATE_OVER;}
    //更改控件位置
    m_verInfo->move(ZOOM(17),
                    this->height()-ZOOM(26));
    m_closeBtn->move(this->width()-ZOOM(47),
                     ZOOM(1));
    m_minisizeBtn->move(this->width()-ZOOM(93),
                        ZOOM(1));
    m_closeBtnBg->move(m_closeBtn->pos());
    m_minisizeBtnBg->move(m_minisizeBtn->pos());
    //更改控件大小
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
    m_minisizeBtn->raise();
    m_closeBtn->raise();
    m_verInfo->raise();
}
