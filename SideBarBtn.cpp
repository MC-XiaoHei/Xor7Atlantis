#include "SideBarBtn.h"

SideBarBtn::SideBarBtn(QString iconPath, QString text, quint8 pos, QWidget *sideBarInfo, QWidget *parent)
    :QObject{parent}{
    this->pos=pos;
    icon=new QPushButton(parent);
    icon->setStyleSheet("background-color:rgba(255,255,255,0);");
    icon->setIcon(QIcon(iconPath));
    this->text=new QLabel(sideBarInfo);
    this->text->setText(text);
    this->text->setAlignment(Qt::AlignVCenter);
    this->text->installEventFilter(this);
    connect(icon,&QPushButton::clicked,this,&SideBarBtn::clicked);
}
void SideBarBtn::refresh(){
    QFont font;
    font.setPixelSize(ZOOM(16));
    text->setFont(font);
    text->move(0,
               ZOOM(18+pos*40));
    QSize size(ZOOM(32),
               ZOOM(32));
    icon->setIconSize(size);
    icon->setMinimumSize(size);
    icon->resize(size);
    icon->move(ZOOM(16),
               ZOOM(22+pos*40));
}
bool SideBarBtn::eventFilter(QObject *watched, QEvent *event){
    if(watched==text&&event->type()==QEvent::MouseButtonPress)
        emit clicked();
    return false;
}
