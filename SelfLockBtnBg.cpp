#include "SelfLockBtnBg.h"

SelfLockBtnBg::SelfLockBtnBg(QPushButton *btn,QWidget *parent)
 : ButtonBg{parent}{
    refresh();
    this->btn=btn;
    connect(btn,&QPushButton::clicked,this,[=](){
        if(!active){
            active=true;
            setState(BtnBgState::WeakActive);
        }
        else active=false;
    });
    startTimer(50);
}
void SelfLockBtnBg::refresh(){
    setQSS(QString(
        "border-radius:%1px;")
        .arg(ZOOM(m_radius)));
}
void SelfLockBtnBg::timerEvent(QTimerEvent *event){
    ButtonBg::timerEvent(event);
    if(btn->underMouse() || active)
        setState(BtnBgState::WeakActive);
    else
        setState(BtnBgState::Inactive);
}
