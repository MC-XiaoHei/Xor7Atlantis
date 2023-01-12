#ifndef SIDEBARBTN_H
#define SIDEBARBTN_H

#include "SelfLockBtnBgInGroup.h"
#include "stable.h"
#include "Zoomer.h"

class SideBarBtn : public SelfLockBtnBgInGroup
{
    Q_OBJECT
public:
    explicit SideBarBtn(quint64 index,SelfLockBtnBgGroupConfig cfg,QString text,QString iconPath,QWidget *parent = nullptr);
    void setPageName(QString name){pageName=name;}
    void setText(QString t){text=t;}
    QString getName(){return pageName;}
    QString getText(){return text;}
private:
    QString text,iconPath,pageName;
    QLabel *l_icon,*l_text;
};
#endif // SIDEBARBTN_H
