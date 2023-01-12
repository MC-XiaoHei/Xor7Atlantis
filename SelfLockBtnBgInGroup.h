#ifndef SELFLOCKBTNBGINGROUP_H
#define SELFLOCKBTNBGINGROUP_H

#include "SelfLockBtnBg.h"
#include "stable.h"

struct SelfLockBtnBgGroupConfig{
    QSize btnSize,bgSize;
    QString color;
    QPoint basePoint;
    double alphaMultiplier=1.00;
};

class SelfLockBtnBgInGroup : public QObject
{
    Q_OBJECT
public:
    explicit SelfLockBtnBgInGroup(quint64 index,SelfLockBtnBgGroupConfig cfg,QWidget *parent = nullptr);
    void refresh();
    void release(){bg->release();}
    void click(){bg->click();}
    bool isActive(){return bg->isActive();}
    void onTimerEvent();
    void setDefault();
signals:
    void clicked();
    void onSetDefault();
    void onRefresh();
protected:
    SelfLockBtnBgGroupConfig m_cfg;
    void timerEvent(QTimerEvent *event){onTimerEvent();}
    quint64 index;
    int cursorAlpha=0;
    QPushButton *btn=new QPushButton,
                *cursor=new QPushButton;
    SelfLockBtnBg *bg=new SelfLockBtnBg(btn);
};

#endif // SELFLOCKBTNBGINGROUP_H
