#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include "ButtonBg.h"
#include "stable.h"
#include "Zoomer.h"

class ScrollArea : public QWidget
{
    Q_OBJECT
public:
    ScrollArea(QWidget *parent = nullptr);
    void refresh();
    qint64 getScrollBarSize();
    QWidget* body(){return m_body;}
    void scrollTo(qint64 pos);
private:
    int alpha=16;
    qint64 nowPos=0,nowStep=0,stepCnt=0;
    QPushButton *bg=new QPushButton(this),
                *bar=new QPushButton(this);
    QWidget *m_body=new QWidget(this);
    double visualScale=0;
protected:
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // SCROLLAREA_H
