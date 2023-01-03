#include "SelfLockBtnBg.h"

SelfLockBtnBg::SelfLockBtnBg(QPushButton *btn,QWidget *parent)
 : ButtonBg{parent}{
    refresh();
    this->btn=btn;
    startTimer(25);
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
