#include "MainWidget.h"
#include "InfoButton.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    parent->installEventFilter(this);
    this->installEventFilter(this);
    m_sideBarInfo->setParent(parent);
    m_titleBarClose->setParent(parent);
    m_titleBarMin->setParent(parent);
    m_sideBarMenu->setParent(parent);
    m_sideBarHome->setParent(parent);
    m_sideBarProfile->setParent(parent);
    t_sideBarHome->setParent(m_sideBarInfo);
    t_sideBarProfile->setParent(m_sideBarInfo);
    m_sideBarMenu->setIcon(QIcon(":/Images/Icon/menu.png"));
    m_sideBarHome->setIcon(QIcon(":/Images/Icon/home.png"));
    m_sideBarProfile->setIcon(QIcon(":/Images/Icon/profile.png"));
    m_titleBarMin->setIcon(QIcon(":/Images/Icon/min.png"));
    m_titleBarClose->setIcon(QIcon(":/Images/Icon/close.png"));
    m_sideBarInfo->setStyleSheet("background-color:rgb(255,255,255);"
                                 "border-radius:0px;");
    m_titleBarMin->setStyleSheet("background-color:rgba(255,255,255,0);");
    m_sideBarMenu->setStyleSheet("background-color:rgba(255,255,255,0);");
    m_sideBarHome->setStyleSheet("background-color:rgba(255,255,255,0);");
    m_sideBarProfile->setStyleSheet("background-color:rgba(255,255,255,0);");
    setBackground(QImage(":/Images/background.png"));
    connect(m_titleBarClose,&QPushButton::clicked,this,&MainWidget::closeWindow);
    connect(m_titleBarMin,&QPushButton::clicked,this,&MainWidget::minimizeWindow);
    connect(m_sideBarMenu,&QPushButton::clicked,this,&MainWidget::setSideBarInfo);
    connect(m_sideBarHome,&QPushButton::clicked,this,&MainWidget::onHomeBtnCicked);
    connect(m_sideBarProfile,&QPushButton::clicked,this,&MainWidget::onProfileBtnCicked);
}
void MainWidget::switchPage(QString name){
    if(name==m_nowPage) return;
    m_pages.value(m_nowPage)->flashHide();
    m_pages.value(name)->flashShow();
    m_nowPage=name;
}
void MainWidget::onHomeBtnCicked(){
    switchPage("home");
}
void MainWidget::onProfileBtnCicked(){
    switchPage("profile");
}
bool MainWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched==t_sideBarHome &&
       event->type()==QEvent::MouseButtonPress)
        onHomeBtnCicked();
    if(watched==t_sideBarProfile &&
       event->type()==QEvent::MouseButtonPress)
        onProfileBtnCicked();
    return false;
}
void MainWidget::resizeEvent(QResizeEvent* event){
    Q_UNUSED(event);
    ON_ZOOM_UPDATE{
        m_pages.clear();
        QFont font;
        font.setPixelSize(ZOOM(16));
        t_sideBarHome->setFont(font);
        t_sideBarHome->setAlignment(Qt::AlignVCenter);
        t_sideBarHome->installEventFilter(this);
        t_sideBarProfile->setFont(font);
        t_sideBarProfile->setAlignment(Qt::AlignVCenter);
        t_sideBarProfile->installEventFilter(this);
        Page* home=new Page(this);
        QHBoxLayout *homeHLayout=new QHBoxLayout(home->body),
                    *homeLaunchHLayout=new QHBoxLayout();
        QVBoxLayout *homeVLayout=new QVBoxLayout();
        m_helloArea=new InfoButton(home->body);
        m_helloArea->setMinimumSize(ZOOM(320),
                                  ZOOM(96));
        m_helloArea->setText("你好，Neraxemaplefall");
        m_helloArea->setSubText("开发者   微软登录");
        m_helloArea->flush();
        m_launchArea=new InfoButton(home->body);
        m_launchArea->setMinimumSize(ZOOM(224),
                                     ZOOM(96));
        m_launchArea->setText("启动游戏");
        m_launchArea->setSubText("1.18.2 Fabric");
        m_launchArea->flush();
        m_DIYArea=new QWidget(home->body);
        m_DIYArea->setMinimumSize(ZOOM(320),
                                  ZOOM(128));
        m_homeLaunchChoose=new QPushButton(home->body);
        m_homeLaunchChoose->setMinimumSize(ZOOM(96),
                                           ZOOM(96));
        homeHLayout->addStretch();
        homeHLayout->addLayout(homeVLayout);
        homeVLayout->addStretch();
        homeVLayout->addWidget(m_helloArea);
        homeVLayout->addSpacing(ZOOM(16));
        homeVLayout->addWidget(m_DIYArea);
        homeVLayout->addSpacing(ZOOM(16));
        homeVLayout->addLayout(homeLaunchHLayout);
        homeLaunchHLayout->addWidget(m_launchArea);
        homeLaunchHLayout->addSpacing(ZOOM(16));
        homeLaunchHLayout->addWidget(m_homeLaunchChoose);
        homeVLayout->addStretch();
        homeHLayout->addStretch();
        connect(m_helloArea,&InfoButton::clicked,this,[=](){Point;});
        home->body->setLayout(homeHLayout);
        home->flush();
        home->show();
        m_pages.insert("home",home);
        Page* profile=new Page(this);
        QGridLayout *profileLayout=new QGridLayout(profile->body);
        profile->body->setLayout(profileLayout);
        profile->flush();
        profile->hide();
        m_pages.insert("profile",profile);
        m_homeLaunchChoose->setStyleSheet(QString(
             "border-radius:%1px;"
             "background-color:rgba(255,255,255,200);")
             .arg(ZOOM(8)));
        UPDATE_OVER;
    }
    for(Page* page:qAsConst(m_pages)){
        page->move(ZOOM(48),
                   ZOOM(48));
        page->resize(this->width()-ZOOM(48),
                     this->height()-ZOOM(48));
        page->setStyleSheet(QString(
            "border-radius:0px;"
            "background-color:rgba(255,255,255,64);"
            "border-bottom-right-radius:%1px;")
            .arg(ZOOM(8)));
    }
    m_titleBar->move(ZOOM(48),
                     0);
    m_sideBarMenu->move(ZOOM(8),
                        ZOOM(8));
    m_sideBarHome->move(ZOOM(16),
                        ZOOM(62));
    t_sideBarHome->move(0,
                        ZOOM(54));
    m_sideBarProfile->move(ZOOM(16),
                           ZOOM(102));
    t_sideBarProfile->move(0,
                           ZOOM(94));
    m_titleBar->resize(this->width()-ZOOM(48),
                       ZOOM(48));
    m_titleBarClose->move(this->width()-ZOOM(40),
                          ZOOM(8));
    m_titleBarMin->move(this->width()-ZOOM(91),
                        ZOOM(8));
    m_sideBar->resize(ZOOM(48),
                      this->height());
    m_sideBarInfo->resize(0,
                          this->height());
    m_sideBarInfo->move(ZOOM(56),
                        ZOOM(8));
    QSize size(this->width()-ZOOM(48),
               this->height()),
          imageSize,
          barTextSize(ZOOM(128),
                      ZOOM(24)),
          barBtnSize(ZOOM(48),
                     ZOOM(48)),
          barBtnIconSize(ZOOM(32),
                         ZOOM(23));
    m_titleBarClose->resize(barBtnSize);
    m_titleBarClose->setIconSize(barBtnIconSize);
    m_titleBarMin->resize(barBtnSize);
    m_titleBarMin->setIconSize(barBtnIconSize);
    m_sideBarMenu->resize(barBtnSize);
    m_sideBarMenu->setIconSize(barBtnIconSize);
    barBtnSize=barBtnIconSize;
    m_sideBarHome->resize(barBtnSize);
    m_sideBarHome->setIconSize(barBtnIconSize);
    t_sideBarHome->resize(barTextSize);
    m_sideBarProfile->resize(barBtnSize);
    m_sideBarProfile->setIconSize(barBtnIconSize);
    t_sideBarProfile->resize(barTextSize);
    m_background->resize(this->width()-ZOOM(48),
                         this->height());
    m_background->move(ZOOM(48),0);
    double Iproportion=m_bg.width()/m_bg.height();
    if(Iproportion>=(size.width()*1.00/size.height()))
        imageSize=QSize(size.height()*Iproportion,size.height());
    else
        imageSize=QSize(size.width(),size.width()/Iproportion);
    QImage image = m_bg.scaled(imageSize);
    image=image.copy(0,0,size.width(),size.height());
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), ZOOM(7.9), ZOOM(7.9));
    painter.drawRect(0, 0, ZOOM(8), size.height());
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.setMask(mask);
    m_background->setPixmap(pixmap);
    m_sideBar->setStyleSheet(QString(
        "border-radius:0px;"
        "border-top-left-radius:%1px;"
        "border-bottom-left-radius:%1px;")
        .arg(ZOOM(8)));
    m_titleBar->setStyleSheet(QString(
         "border-radius:0px;"
         "border-top-right-radius:%1px;"
         "background-color:rgba(255,255,255,200);")
         .arg(ZOOM(6)));
    m_titleBarClose->setStyleSheet(QString(
         "background-color:rgba(255,255,255,0);"
         "border-radius:%1px")
         .arg(ZOOM(10)));
    m_sideBarMenu->raise();
    m_titleBarClose->raise();
    m_titleBarMin->raise();
    t_sideBarHome->raise();
}
void MainWidget::setSideBarInfo(){
    if(flash) return;
    QPropertyAnimation *showAnimation=new QPropertyAnimation(m_sideBarInfo,"geometry",this);
    QRect endValue=m_sideBarInfo->geometry();
    if(sideBarInfoVisible)
        endValue.setRight(endValue.right()-ZOOM(128));
    else
        endValue.setRight(endValue.right()+ZOOM(128));
    sideBarInfoVisible=!sideBarInfoVisible;
    showAnimation->setEasingCurve(QEasingCurve::OutCubic);
    showAnimation->setDuration(512);
    showAnimation->setStartValue(m_sideBarInfo->geometry());
    showAnimation->setEndValue(endValue);
    showAnimation->start();
    connect(showAnimation,&QPropertyAnimation::finished,this,[=](){
        if(m_sideBarInfo->width()>ZOOM(128)){
            flash=true;
            QPropertyAnimation *showAnimation=new QPropertyAnimation(m_sideBarInfo,"geometry",this);
            QRect endValue=m_sideBarInfo->geometry();
            endValue.setWidth(0);
            sideBarInfoVisible=false;
            showAnimation->setEasingCurve(QEasingCurve::OutCubic);
            showAnimation->setDuration(512);
            showAnimation->setStartValue(m_sideBarInfo->geometry());
            showAnimation->setEndValue(endValue);
            showAnimation->start();
            connect(showAnimation,&QPropertyAnimation::finished,this,[=](){flash=false;});
        }
    });
}
