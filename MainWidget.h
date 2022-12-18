#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "SideBarBtn.h"
#include "stable.h"
#include "Zoomer.h"
#include "InfoButton.h"
#include "Page.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void setBackground(QImage bg){this->m_bg=bg;}
    void setSideBarInfo();
    void switchPage(QString name);
signals:
    void closeWindow();
    void minimizeWindow();
private:
    bool sideBarInfoVisible=false,
         flash=false;
    QImage m_bg;
    QWidget *m_homeRightTopArea,
            *m_homeRightBottomArea,
            *m_homeLeftArea;
    InfoButton *m_helloArea;
    QLabel *m_background=new QLabel(this);
    QPushButton *m_titleBar=new QPushButton(this),
                *m_titleBarClose=new QPushButton(),
                *m_titleBarMin=new QPushButton(),
                *m_sideBar=new QPushButton(this),
                *m_sideBarInfo=new QPushButton(this),
                *m_sideBarMenu=new QPushButton();
    QMap<QString,Page*> m_pages;
    QMap<QString,SideBarBtn*> m_sideBarBtns;
    QString m_nowPage="home";
protected:
    void timerEvent(QTimerEvent *e);
    void resizeEvent(QResizeEvent* event);
};

#endif // MAINWIDGET_H
