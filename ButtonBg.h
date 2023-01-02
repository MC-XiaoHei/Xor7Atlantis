#ifndef BUTTONBG_H
#define BUTTONBG_H

#include "stable.h"
#include "Zoomer.h"

enum class BtnBgState{
    None,Inactive,WeakActive,StrongActive
};

class ButtonBg : public QPushButton
{
    Q_OBJECT
public:
    ButtonBg(QWidget *parent = nullptr);
    void setQSS(QString nQSS);
    void setColor(QString nColor);
    void setAlpha(int nAlpha);
    void setState(BtnBgState state);
    BtnBgState getNowState(){return nowState;}
    BtnBgState getGoalState(){return goalState;}
    void setPos(QPoint pos);
    void setMaximumSize(QSize size);
    void setMaximumSize(int maxw,int maxh){setMaximumSize(QSize(maxw,maxh));}
protected:
    void timerEvent(QTimerEvent *event);
private:
    int alpha,maxAlpha=160,midAlpha=80,minAlpha=0;
    QString color="255,255,255",qss="border-radius:4px";
    QRect minGeo,maxGeo;
    BtnBgState nowState=BtnBgState::Inactive,
               goalState=BtnBgState::None;
};

#endif // BUTTONBG_H
