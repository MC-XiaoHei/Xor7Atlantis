#include "ButtonBg.h"

ButtonBg::ButtonBg(QWidget *parent)
 : QPushButton{parent}{
    maxGeo=geometry();
    minGeo=geometry();
    setAlpha(minAlpha);
    setGeometry(minGeo);
    startTimer(25);
    lastGeo=minGeo;
    lastAlpha=minAlpha;
}
void ButtonBg::timerEvent(QTimerEvent *event){
    switch (goalState) {
    case BtnBgState::Inactive:{
        setAlpha(Max(alpha-25,minAlpha));
        move(Min(x()+ZOOM(2),minGeo.x()),
             Min(y()+ZOOM(1),minGeo.y()));
        resize(Max(width()-ZOOM(4),minGeo.width()),
               Max(height()-ZOOM(2),minGeo.height()));
        if(alpha==minAlpha && geometry()==minGeo)
            goalState=BtnBgState::None;
        break;
    }
    case BtnBgState::WeakActive:{
        if(nowState==BtnBgState::Inactive)
            setAlpha(Min(alpha+25,midAlpha));
        else
            setAlpha(Max(alpha-25,midAlpha));
        move(Max(x()-ZOOM(2),maxGeo.x()),
             Max(y()-ZOOM(1),maxGeo.y()));
        resize(Min(width()+ZOOM(4),maxGeo.width()),
               Min(height()+ZOOM(2),maxGeo.height()));
        if(alpha==midAlpha && geometry()==maxGeo)
            goalState=BtnBgState::None;
        break;
    }
    case BtnBgState::StrongActive:{
        setAlpha(Min(alpha+25,maxAlpha));
        move(Min(x()+ZOOM(2),minGeo.x()),
             Min(y()+ZOOM(1),minGeo.y()));
        resize(Max(width()-ZOOM(4),minGeo.width()),
               Max(height()-ZOOM(2),minGeo.height()));
        if(alpha==maxAlpha && geometry()==minGeo)
            goalState=BtnBgState::None;
        break;
    }
    default:return;
    }
}
void ButtonBg::setMaximumSize(QSize size){
    maxGeo.setSize(size);
    minGeo.setSize(QSize(size.width()-ZOOM(20),
                         size.height()-ZOOM(2)));
    QPushButton::setMaximumSize(size);
}
void ButtonBg::setPos(QPoint pos){
    move(pos);
    maxGeo.moveTo(pos);
    minGeo.moveTo(maxGeo.topLeft().x()+ZOOM(10),
                  maxGeo.topLeft().y()+ZOOM(1));
}
void ButtonBg::setAlpha(int nAlpha){
    alpha=nAlpha;
    this->setStyleSheet(QString(
        "background-color:rgba(%1,%2);%3")
        .arg(color,QString::number(nAlpha),qss));
}
void ButtonBg::setState(BtnBgState state){
    goalState=state;
}
void ButtonBg::setQSS(QString nQSS){
    qss=nQSS;
    setAlpha(alpha);
}
void ButtonBg::setColor(QString nColor){
    color=nColor;
    setAlpha(alpha);
}
