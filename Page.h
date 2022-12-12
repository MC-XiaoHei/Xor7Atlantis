#ifndef PAGE_H
#define PAGE_H

#include "stable.h"

class Page : public QScrollArea
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
    void flush();
    QWidget *body=new QWidget(this);
signals:

private:

};

#endif // PAGE_H
