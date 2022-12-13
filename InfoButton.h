#ifndef INFOBUTTON_H
#define INFOBUTTON_H

#include "stable.h"
#include "Zoomer.h"

class InfoButton : public QPushButton
{
    Q_OBJECT
public:
    explicit InfoButton(QWidget *parent = nullptr);
    void flush(){resize(this->size());}
    void setIcon(QIcon i){this->icon=i;}
    void setText(QString s){this->text=s;}
    void setSubText(QString s){this->subText=s;}
signals:

protected:
    void resizeEvent(QResizeEvent *event);
private:
    QIcon icon;
    QString text,subText;
    QPushButton *ui_line=new QPushButton(this),
                *ui_icon=new QPushButton(this);
    QLabel *l_text=new QLabel(this),
           *l_subText=new QLabel(this);
};

#endif // INFOBUTTON_H
