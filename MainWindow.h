#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stable.h"
#include "Zoomer.h"
#include "MainWidget.h"

struct SideWidth{
    quint8 top=48,
           bottom=16,
           right=16;
};
enum class Action{
    NOTHING,
    MOVE,
    RESIZE
};
enum class CursorPosFlag{
    BODY,
    TITLE,
    RSIDE,
    BOTTOM,
    RBOTTOM
};
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    QWidget *m_background=new QWidget(this);
    MainWidget *m_body=new MainWidget(this);
    SideWidth m_sideWidth;
    Action m_windowAction=Action::NOTHING;
    CursorPosFlag  m_cursorPosFlag=CursorPosFlag::BODY;
    QLabel *m_titleLable=new QLabel(this),
           *m_rsideLabel=new QLabel(this),
           *m_rbottomLabel=new QLabel(this),
           *m_bottomLabel=new QLabel(this);
    QPointF m_movePos,
            m_resizePos;
    QRect m_resizeLocation;
    bool flash=false,
         visible=true,
         running=false;
signals:
    void minimizeWindow();
    void closeWindow();
protected:
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
