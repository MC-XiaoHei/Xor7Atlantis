#ifndef SIDEBARBTN_H
#define SIDEBARBTN_H

#include "stable.h"
#include "Zoomer.h"

class SideBarBtn : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int alpha
               READ getAlpha
               WRITE setAlpha
               NOTIFY alphaChanged)
public:
    explicit SideBarBtn(quint8 index,QString text,QString iconPath,QWidget *parent = nullptr);
    void active();
    void inactive();
    void refresh();
    int getAlpha();
    void alphaChanged();
    void setAlpha(int alpha);
signals:
    void clicked();
private:
    int alpha;
    quint8 index;
    QString text,iconPath;
    QPushButton *btn,*bg,*cursor;
    QLabel *l_icon,*l_text;
};

#endif // SIDEBARBTN_H
