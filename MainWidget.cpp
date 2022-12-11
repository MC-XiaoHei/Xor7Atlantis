#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    this->installEventFilter(this);
    m_titleBarClose->setParent(parent);
    m_titleBarMin->setParent(parent);
    m_sideBarMenu->setParent(parent);
    m_sideBarHome->setParent(parent);
    t_sideBarHome->setParent(m_sideBarInfo);
    m_sideBarMenu->setIcon(QIcon(":/Images/Icon/menu.png"));
    m_sideBarHome->setIcon(QIcon(":/Images/Icon/home.png"));
    m_titleBarMin->setIcon(QIcon(":/Images/Icon/min.png"));
    m_titleBarClose->setIcon(QIcon(":/Images/Icon/close.png"));
    QFont font;
    font.setPixelSize(ZOOM(16));
    t_sideBarHome->setFont(font);
    t_sideBarHome->setAlignment(Qt::AlignVCenter);
    t_sideBarHome->installEventFilter(this);
    m_sideBarInfo->setStyleSheet("border-radius:0px;");
    m_titleBarMin->setStyleSheet("background-color:rgba(255,255,255,0);");
    m_sideBarMenu->setStyleSheet("background-color:rgba(255,255,255,0);");
    m_sideBarHome->setStyleSheet("background-color:rgba(255,255,255,0);");
//    t_sideBarHome->setStyleSheet("background-color:rgb(255,0,255);");
    setBackground(QImage(":/Images/background.png"));
    connect(m_titleBarClose,&QPushButton::clicked,this,&MainWidget::closeWindow);
    connect(m_titleBarMin,&QPushButton::clicked,this,&MainWidget::minimizeWindow);
    connect(m_sideBarMenu,&QPushButton::clicked,this,&MainWidget::setSideBarInfo);
    connect(m_sideBarHome,&QPushButton::clicked,this,&MainWidget::onHomeBtnCicked);
}
void MainWidget::onHomeBtnCicked(){
    Point;
}
bool MainWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched==t_sideBarHome && event->type()==QEvent::MouseButtonPress)
        onHomeBtnCicked();
    return false;
}
void MainWidget::resizeEvent(QResizeEvent* event){
    Q_UNUSED(event);
    m_titleBar->move(ZOOM(48),0);
    m_sideBarMenu->move(ZOOM(8),ZOOM(8));
    m_sideBarHome->move(ZOOM(16),ZOOM(62));
    t_sideBarHome->move(0,ZOOM(54));
    m_titleBar->resize(this->width()-ZOOM(48),ZOOM(48));
    m_titleBarClose->move(ZOOM(8)+this->width()-ZOOM(48),ZOOM(8));
    m_titleBarMin->move(ZOOM(8)+this->width()-ZOOM(96),ZOOM(8));
    m_sideBar->resize(ZOOM(48),this->height());
    m_sideBarInfo->resize(0,this->height());
    m_sideBarInfo->move(ZOOM(48),0);
    QSize size(this->width()-ZOOM(48),this->height()),
          imageSize,
          barTextSize(ZOOM(128),ZOOM(24)),
          barBtnSize(ZOOM(48),ZOOM(48)),
          barBtnIconSize(ZOOM(32),ZOOM(23));
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
    m_background->resize(this->width()-ZOOM(48),this->height());
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
    m_sideBar->setStyleSheet(QString("border-radius:0px;"
                             "border-top-left-radius:%1px;"
                             "border-bottom-left-radius:%1px;").arg(ZOOM(8)));
    m_titleBar->setStyleSheet(QString("border-radius:0px;"
                              "border-top-right-radius:%1px;"
                              "background-color:rgba(255,255,255,200);").arg(ZOOM(6)));
    m_titleBarClose->setStyleSheet(QString("background-color:rgba(255,255,255,0);"
                                           "border-radius:%1px").arg(ZOOM(10)));
    m_sideBarMenu->raise();
    m_titleBarClose->raise();
    m_titleBarMin->raise();

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
