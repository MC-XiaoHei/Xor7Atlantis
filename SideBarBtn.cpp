#include "SideBarBtn.h"

SideBarBtn::SideBarBtn(quint64 index,SelfLockBtnBgGroupConfig cfg, QString text, QString iconPath, QWidget *parent)
    : SelfLockBtnBgInGroup{index,cfg,parent}
{
    this->text=text;
    pageName=text;
    this->iconPath=iconPath;
    l_icon=new QLabel(parent);
    l_text=new QLabel(parent);
    l_text->setText(text);
    connect(this,&SelfLockBtnBgInGroup::onRefresh,this,[=](){
        QFont font;
        font.setPixelSize(14);
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
        l_icon->raise();
        l_text->raise();
    });
    refresh();
}
