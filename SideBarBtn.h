#ifndef SIDEBARBTN_H
#define SIDEBARBTN_H

#include "SelfLockBtnBg.h"
#include "stable.h"
#include "Zoomer.h"

class SideBarBtn : public QObject
{
    Q_OBJECT
public:
    explicit SideBarBtn(quint8 index,QString text,QString iconPath,QWidget *parent = nullptr);
    void refresh();
    void release(){bg->release();}
    void click(){bg->click();}
    bool isActive(){return bg->isActive();}
    void onTimerEvent();
    void setDefault();
signals:
    void clicked();
protected:
    void timerEvent(QTimerEvent *event){onTimerEvent();}
private:
    quint8 index;
    int cursorAlpha=0;
    QString text,iconPath;
    QPushButton *btn=new QPushButton,
                *cursor=new QPushButton;
    SelfLockBtnBg *bg=new SelfLockBtnBg(btn);
    QLabel *l_icon,*l_text;
};
#endif // SIDEBARBTN_H
