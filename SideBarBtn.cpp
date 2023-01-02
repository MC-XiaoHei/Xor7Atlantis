#include "SideBarBtn.h"

SideBarBtn::SideBarBtn(quint8 index,QString text,QString iconPath,QWidget *parent)
    : QObject{parent}
{
//    setObj(btn);
    this->index=index;
    this->text=text;
    this->iconPath=iconPath;
    bg->setParent(parent);
    l_icon=new QLabel(parent);
    l_text=new QLabel(parent);
    l_text->setText(text);
    btn->setParent(parent);
    btn->setStyleSheet("background-color:rgba(255,255,255,0)");
    cursor->setParent(parent);
    cursor->setStyleSheet(QString(
        "background-color:rgba(0,95,184,0);"
        "border-top-right-radius:%1px;"
        "border-bottom-right-radius:%1px;")
        .arg(QString::number(ZOOM(3))));
    connect(btn,&QPushButton::clicked,this,&SideBarBtn::clicked);
//    connect(this,&AlphaSupposedObject::alphaChanged,this,[=](){
//        bg->setStyleSheet(QString(
//            "border-radius:%1px;"
//            "background-color:rgba(255,255,255,%2)")
//            .arg(QString::number(ZOOM(4)),QString::number(getAlpha())));
//    });
//    connect(this,&AlphaSupposedObject::subAlphaChanged,this,[=](){
//        cursor->setStyleSheet(QString(
//            "background-color:rgba(0,95,184,%2);"
//            "border-top-right-radius:%1px;"
//            "border-bottom-right-radius:%1px;")
//            .arg(QString::number(ZOOM(3)),QString::number(Max(0,getSubAlpha()*6-246))));
//    });
    refresh();
}
void SideBarBtn::refresh(){
    QFont font;
    font.setPixelSize(14);
    btn->resize(ZOOM(244),
                ZOOM(41));
    btn->move(ZOOM(1),
              ZOOM(51+index*41));
    bg->resize(ZOOM(213),
               ZOOM(34));
    bg->move(btn->x()+ZOOM(18),
             btn->y()+ZOOM(2));
    QPixmap icon=QPixmap(iconPath);
    l_icon->setPixmap(icon.scaled(ZOOM(28),
                                  ZOOM(28),
                                  Qt::IgnoreAspectRatio,
                                  Qt::SmoothTransformation));
    l_icon->resize(ZOOM(28),
                   ZOOM(28));
    l_icon->move(btn->x()+ZOOM(27),
                 btn->y()+ZOOM(6));
    l_text->setFont(font);
    l_text->resize(ZOOM(164),
                   ZOOM(21));
    l_text->move(l_icon->x()+ZOOM(40),
                 l_icon->y()+ZOOM(4));
    cursor->resize(ZOOM(3),
                   ZOOM(16));
    cursor->move(bg->x(),
                 bg->y()+ZOOM(10));
//    setAlpha(0);
    bg->raise();
    cursor->raise();
    l_icon->raise();
    l_text->raise();
    btn->raise();
}
