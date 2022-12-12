#include "Page.h"

Page::Page(QWidget *parent)
    : QScrollArea{parent}
{

}
void Page::flush(){
    this->setWidget(body);
    this->setWidgetResizable(true);
}
