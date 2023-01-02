#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "SideBarBtn.h"
#include "ButtonBg.h"
#include "stable.h"
#include "Zoomer.h"
#include "Page.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void setBackground(QImage bg) { this->m_bg = bg; }
    void switchPage(QString name);
    void onTimerEvent();
signals:
    void closeWindow();
    void minimizeWindow();
private:
    bool flash=false;
    quint8 closeBtnAlpha=0,
           minisizeBtnAlpha=0;
    QPushButton *b=new QPushButton;
    ButtonBg *g=new ButtonBg;
    QImage m_bg;
    QLabel *m_profileHeadLayer1=new QLabel,
           *m_profileHeadLayer2=new QLabel,
           *m_profileUsername=new QLabel,
           *m_profileInfo=new QLabel,
           *m_background=new QLabel(this),
           *m_verInfo=new QLabel;
    QPushButton *m_mask=new QPushButton(this),
                *m_closeBtn=new QPushButton,
                *m_minisizeBtn=new QPushButton,
                *m_closeBtnBg=new QPushButton,
                *m_minisizeBtnBg=new QPushButton;
    QMap<QString,SideBarBtn*> m_sideBarBtns;
    QMap<QString,Page*> m_pages;
    QString m_nowPage="home",
            m_nowSideBarBtn="home";
protected:
    void timerEvent(QTimerEvent *event){onTimerEvent();}
    void resizeEvent(QResizeEvent* event);
};

#endif // MAINWIDGET_H
