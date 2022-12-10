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
    bool inElement(quint32 x,quint32 y);
signals:
    void onClose();
private:
    QImage m_bg;
    QLabel *m_background=new QLabel(this);
    QPushButton *m_titleBar=new QPushButton(this),
                *m_titleBarClose=new QPushButton(this),
                *m_titleBarMin=new QPushButton(this),
                *m_sideBar=new QPushButton(this),
                *m_sideBarMenu=new QPushButton(this);
protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // MAINWIDGET_H
