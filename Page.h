#ifndef PAGE_H
#define PAGE_H

#include "stable.h"
#include "Zoomer.h"

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(QWidget *parent = nullptr);
    void refresh();
    void hide();
    void show();
signals:

};

#endif // PAGE_H
