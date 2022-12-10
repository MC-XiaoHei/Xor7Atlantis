#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget{parent}
{
    m_titleBarClose->setParent(parent);
    m_titleBarMin->setParent(parent);
    m_sideBarMenu->setParent(parent);
    m_sideBarMenu->setIcon(QIcon(":/Images/Icon/menu.png"));
    m_titleBarMin->setIcon(QIcon(":/Images/Icon/min.png"));
    m_titleBarClose->setIcon(QIcon(":/Images/Icon/close.png"));
    m_titleBarMin->setStyleSheet("background-color:rgba(255,255,255,0);");
    setBackground(QImage(":/Images/background.png"));
    connect(m_titleBarClose,&QPushButton::clicked,this,[=](){emit onClose();});
}
void MainWidget::resizeEvent(QResizeEvent* event){
    Q_UNUSED(event);
    m_titleBar->move(ZOOM(48),0);
    m_sideBarMenu->move(ZOOM(8),ZOOM(8));
    m_titleBar->resize(this->width()-ZOOM(48),ZOOM(48));
    m_titleBarClose->move(ZOOM(8)+this->width()-ZOOM(48),ZOOM(8));
    m_titleBarMin->move(ZOOM(8)+this->width()-ZOOM(96),ZOOM(8));
    m_sideBar->resize(ZOOM(48),this->height());
    QSize size(this->width()-ZOOM(48),this->height()),
          imageSize,
          sideBarBtnSize(ZOOM(48),ZOOM(48)),
          sideBarBtnIconSize(ZOOM(32),ZOOM(23));
    m_titleBarClose->resize(sideBarBtnSize);
    m_titleBarClose->setIconSize(sideBarBtnIconSize);
    m_titleBarMin->resize(sideBarBtnSize);
    m_titleBarMin->setIconSize(sideBarBtnIconSize);
    m_sideBarMenu->resize(sideBarBtnSize);
    m_sideBarMenu->setIconSize(sideBarBtnIconSize);
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
    m_background->show();
    m_sideBar->show();
    m_titleBar->show();
    m_titleBarClose->raise();
    m_titleBarMin->show();
    m_sideBarMenu->show();
}
