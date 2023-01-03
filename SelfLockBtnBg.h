#ifndef SELFLOCKBTNBG_H
#define SELFLOCKBTNBG_H

#include "ButtonBg.h"

class SelfLockBtnBg : public ButtonBg
{
    Q_OBJECT
public:
    SelfLockBtnBg(QPushButton* btn,QWidget *parent = nullptr);
    void refresh();
    void release(){active=false;}
    void click(){active=true;}
    bool isActive(){return active;}
    void setBorderRadius(quint64 radius);
protected:
    void timerEvent(QTimerEvent *event);
private:
    quint64 m_radius=4;
    bool active=false;
    QPushButton *btn;
};

#endif // SELFLOCKBTNBG_H
