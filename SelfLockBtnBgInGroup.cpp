#include "SelfLockBtnBgInGroup.h"

SelfLockBtnBgInGroup::SelfLockBtnBgInGroup(quint64 index,SelfLockBtnBgGroupConfig cfg,QWidget *parent)
    : QObject{parent}
{
    m_cfg=cfg;
    this->index=index;
    bg->setAlphaMultiplier(m_cfg.alphaMultiplier);
    bg->setColor(m_cfg.color);
    bg->setParent(parent);
    btn->setParent(parent);
    btn->setStyleSheet("background-color:rgba(255,255,255,0)");
    cursor->setParent(parent);
    connect(btn,&QPushButton::clicked,this,&SelfLockBtnBgInGroup::clicked);
    refresh();
    onTimerEvent();
    startTimer(50);
}
void SelfLockBtnBgInGroup::setDefault(){
    emit onSetDefault();
    cursorAlpha=255;
    bg->setAlpha(80);
    this->click();
    onTimerEvent();
}
void SelfLockBtnBgInGroup::onTimerEvent(){
    if(bg->isActive()) cursorAlpha=Min(255,cursorAlpha+150);
    else cursorAlpha=Max(0,cursorAlpha-150);
    cursor->setStyleSheet(QString(
                "background-color:rgba(0,95,184,%2);"
                "border-top-right-radius:%1px;"
                "border-bottom-right-radius:%1px;")
                .arg(QString::number(ZOOM(3)),QString::number(cursorAlpha)));
}
void SelfLockBtnBgInGroup::refresh(){
    btn->resize(ZOOM(m_cfg.btnSize.width()),
                ZOOM(m_cfg.btnSize.height()));
    btn->move(ZOOM(m_cfg.basePoint.x()),
              ZOOM(m_cfg.basePoint.y()+(index-1)*m_cfg.btnSize.height()));
    bg->setMaximumSize(ZOOM(m_cfg.bgSize.width()),
                       ZOOM(m_cfg.bgSize.height()));
    bg->setPos(QPoint(btn->x()+ZOOM(m_cfg.btnSize.width()-m_cfg.bgSize.width())/2.00,
                      btn->y()+ZOOM(m_cfg.btnSize.height()-m_cfg.bgSize.height())/2.00));
    cursor->resize(ZOOM(3),
                   ZOOM(16));
    cursor->move(bg->x(),
                 bg->y()+ZOOM(m_cfg.btnSize.height()-16)/2.00);
    bg->raise();
    cursor->raise();
    emit onRefresh();
    btn->raise();
}
