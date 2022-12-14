#ifndef MAINWIDGET_H
#define MAINWIDGET_H

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
    void onHomeBtnCicked();
    void onProfileBtnCicked();
    void switchPage(QString name);
signals:
    void closeWindow();
    void minimizeWindow();
private:
    bool sideBarInfoVisible=false,
         flash=false;
    QImage m_bg;
    QWidget *m_DIYArea;
    InfoButton *m_helloArea,
               *m_launchArea;
    QLabel *m_background=new QLabel(this),
           *t_sideBarHome=new QLabel("主页"),
           *t_sideBarProfile=new QLabel("账号管理");
    QPushButton *m_titleBar=new QPushButton(this),
                *m_titleBarClose=new QPushButton(),
                *m_titleBarMin=new QPushButton(),
                *m_sideBar=new QPushButton(this),
                *m_sideBarInfo=new QPushButton(this),
                *m_sideBarHome=new QPushButton(),
                *m_sideBarProfile=new QPushButton(),
                *m_sideBarMenu=new QPushButton(),
                *m_homeLaunchChoose;
    QMap<QString,Page*> m_pages;
    QString m_nowPage="home";
protected:
    void resizeEvent(QResizeEvent* event);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWIDGET_H
