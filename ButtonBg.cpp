#include "ButtonBg.h"

ButtonBg::ButtonBg(QWidget *parent)
 : QPushButton{parent}{
    maxGeo=this->geometry();
    minGeo=this->geometry();
    setAlpha(minAlpha);
    setGeometry(minGeo);
    startTimer(50);
}
void ButtonBg::timerEvent(QTimerEvent *event){
    int deltaAlpha,dx,dy,dw,dh;
    switch (goalState) {
    case BtnBgState::Inactive:{
        deltaAlpha=minAlpha-alpha;
        dx=geometry().x()-minGeo.x();
        break;
    }
    case BtnBgState::WeakActive:{
        deltaAlpha=midAlpha-alpha;
        break;
    }
    case BtnBgState::StrongActive:{
        deltaAlpha=maxAlpha-alpha;

        break;
    }
    default:
        break;
    }
    setAlpha(alpha+deltaAlpha/5);
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
    qDebug()<<maxGeo<<minGeo;
}
void ButtonBg::setAlpha(int nAlpha){
    alpha=nAlpha;
    this->setStyleSheet(QString(
        "background-color:rgba(%1,%2);%3")
        .arg(color,QString::number(nAlpha),qss));
}
void ButtonBg::setState(BtnBgState state){
    if(state==goalState) return;
    goalState=state;
    switch(state){
    case BtnBgState::Inactive:{
        Point;
        ALPHA_ANIMATION(minAlpha,250);
        GEOMETRY_ANIMATION(minGeo,250);
        QTimer::singleShot(240, this, [=]() mutable{
            Point;
            if(geoAnimation->Running){
                hide();
                state=BtnBgState::None;
            }
        });
        break;
    }
    case BtnBgState::WeakActive:{
        Point;
        ALPHA_ANIMATION(midAlpha,250);
        GEOMETRY_ANIMATION(maxGeo,250);
        show();
        QTimer::singleShot(240, this, [=]() mutable{
            Point;
            if(geoAnimation->Running)
                state=BtnBgState::None;
        });
        break;
    }
    case BtnBgState::StrongActive:{
        ALPHA_ANIMATION(maxAlpha,125);
        GEOMETRY_ANIMATION(minGeo,125);
        QTimer::singleShot(240, this, [=]() mutable{
            if(geoAnimation->Running)
                state=BtnBgState::None;
        });
        break;
    }
    case BtnBgState::None:break;
    }
}
void ButtonBg::setQSS(QString nQSS){
    qss=nQSS;
    setAlpha(alpha());
}
void ButtonBg::setColor(QString nColor){
    color=nColor;
    setAlpha(alpha());
}
