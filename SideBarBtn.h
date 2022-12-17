#ifndef SIDEBARBTN_H
#define SIDEBARBTN_H

#include "stable.h"
#include "Zoomer.h"

class SideBarBtn : public QObject{
    Q_OBJECT
public:
    QPushButton *icon;
    QLabel *text;
    quint8 pos;
    explicit SideBarBtn(QString iconPath, QString text,quint8 pos,QWidget *sideBarInfo, QWidget *parent);
    void refresh();
signals:
    void clicked();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
};


#endif // SIDEBARBTN_H
