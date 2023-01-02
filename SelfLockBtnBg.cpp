#include "SelfLockBtnBg.h"

SelfLockBtnBg::SelfLockBtnBg(QWidget *parent)
 : ButtonBg{parent}{
    refresh();
    connect(this,&QPushButton::clicked,this,&SelfLockBtnBg::onClick);
}
void SelfLockBtnBg::refresh(){
    setQSS(QString(
        "border-radius:%1px;")
        .arg(ZOOM(m_radius)));
}
void SelfLockBtnBg::focusInEvent(QFocusEvent *event){
    setState(BtnBgState::WeakActive);
}
void SelfLockBtnBg::focusOutEvent(QFocusEvent *event){
    if(!active) setState(BtnBgState::Inactive);
}
void SelfLockBtnBg::onClick(){
    Point;
    active=!active;
}
void SelfLockBtnBg::onRelease(){
}
