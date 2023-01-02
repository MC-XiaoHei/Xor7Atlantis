#include "Page.h"

Page::Page(QWidget *parent)
    : QScrollArea{parent}
{

}
void Page::flush(){
    this->setWidget(m_body);
    this->setWidgetResizable(true);
}
void Page::flashHide(){
    this->hide();
}
void Page::flashShow(){
    this->show();
}
