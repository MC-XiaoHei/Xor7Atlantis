#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "stable.h"
#include "Zoomer.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void setBackground(QImage bg){this->m_bg=bg;}
    void setSideBarInfo();
    void onHomeBtnCicked();
signals:
    void closeWindow();
    void minimizeWindow();
private:
    bool sideBarInfoVisible=false,
         flash=false;
    QImage m_bg;
    QLabel *m_background=new QLabel(this),
           *t_sideBarHome=new QLabel("启动游戏");
    QPushButton *m_titleBar=new QPushButton(this),
                *m_titleBarClose=new QPushButton(),
                *m_titleBarMin=new QPushButton(),
                *m_sideBar=new QPushButton(this),
                *m_sideBarInfo=new QPushButton(this),
                *m_sideBarHome=new QPushButton(),
                *m_sideBarMenu=new QPushButton();
    QMap<QString,QWidget*> pages;
protected:
    void resizeEvent(QResizeEvent* event);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWIDGET_H