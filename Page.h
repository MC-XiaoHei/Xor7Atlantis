#ifndef PAGE_H
#define PAGE_H

#include "stable.h"

class Page : public QScrollArea
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
    void flush();
    void flashHide();
    void flashShow();
    QWidget *body(){return m_body;}
signals:

private:
    QWidget *m_body=new QWidget(this);
};

#endif // PAGE_H
