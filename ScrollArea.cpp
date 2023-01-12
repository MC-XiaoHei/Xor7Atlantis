#include "ScrollArea.h"

ScrollArea::ScrollArea(QWidget *parent)
    : QWidget{parent}{

    bar->setStyleSheet("background-color:rgba(255,255,255,0);");
    scrollTo(0);
    startTimer(10);
}
void ScrollArea::refresh(){
    m_body->move((this->width()-m_body->width())/2.00,
                 0-nowPos);
    if(m_body->height()<height()) return;
    visualScale=height()*1.00/m_body->height();
    bar->resize(ZOOM(12),
                getScrollBarSize());
    bg->resize(ZOOM(4),
               getScrollBarSize());
    bar->move(this->width()-ZOOM(16),
              this->y()+nowPos*1.00*(height())/m_body->height());
    bg->move(this->width()-ZOOM(12),
             this->y()+bar->y());
    bg->setStyleSheet(QString(
        "background-color:rgba(0,0,0,%2%);"
        "border-radius:%1px;").arg(
        QString::number(ZOOM(2)),
        QString::number(alpha)));
}
qint64 ScrollArea::getScrollBarSize(){
    return height()*visualScale;
}
void ScrollArea::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);
    refresh();
}
void ScrollArea::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    if(m_body->height()<height()) return;
    nowPos=Min(Max(0,nowPos+nowStep),m_body->height()-height());
    if(stepCnt<10) stepCnt++;
    else nowStep=0;
    if(bar->underMouse()) alpha=Min(32,alpha+2);
    else alpha=Max(16,alpha-2);
    refresh();
}
void ScrollArea::wheelEvent(QWheelEvent *event){
    if(m_body->height()<height()) return;
    scrollTo(nowPos-event->angleDelta().ry());
}
void ScrollArea::scrollTo(qint64 pos){
    stepCnt=0;
    nowStep=(pos-nowPos)/10.00;
}
