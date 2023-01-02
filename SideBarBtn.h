#ifndef SIDEBARBTN_H
#define SIDEBARBTN_H

#include "stable.h"
#include "Zoomer.h"

class SideBarBtn : public QObject
{
    Q_OBJECT
public:
    explicit SideBarBtn(quint8 index,QString text,QString iconPath,QWidget *parent = nullptr);
    void refresh();
signals:
    void clicked();
private:
    quint8 index;
    QString text,iconPath;
    QPushButton *btn=new QPushButton,
                *bg=new QPushButton,
                *cursor=new QPushButton;
    QLabel *l_icon,*l_text;
};

#endif // SIDEBARBTN_H
