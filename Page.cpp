#include "Page.h"

Page::Page(QWidget *parent)
    : QWidget{parent}
{
    hide();
    refresh();
}
void Page::refresh(){
    setMinimumWidth(ZOOM(578));
    setStyleSheet("background-color:rgba(255,255,255,0);"
                  "border-radius:0px;");
}
void Page::hide(){
    QWidget::hide();
}
void Page::show(){
    QWidget::show();
}
