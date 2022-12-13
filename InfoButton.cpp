#include "InfoButton.h"

InfoButton::InfoButton(QWidget *parent)
    : QPushButton{parent}
{
    icon=QIcon(":/Images/Icon/home.png");
    this->setStyleSheet("border-radius:0px;"
                        "background-color:rgb(255,255,255);");
    ui_line->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    l_text->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    l_subText->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui_icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    l_text->setStyleSheet("background-color:rgba(255,255,255,0);");
    l_subText->setStyleSheet("background-color:rgba(255,255,255,0);");
    ui_icon->setStyleSheet("background-color:rgba(255,255,255,0);");
    ui_line->setStyleSheet("background-color:rgb(0,0,0);");
}
void InfoButton::resizeEvent(QResizeEvent *event){
    ui_icon->resize(this->height()*0.9,
                   this->height()*0.9);
    ui_icon->move(this->height()*0.1,
                 this->height()*0.05);
    ui_icon->setIcon(icon);
    ui_icon->setIconSize(QSize(this->height()*0.9,
                               this->height()*0.9));
    ui_line->resize(this->width()*0.60,
                    ZOOM(2));
    ui_line->move(this->height()*0.5+this->width()*0.10,
                  this->height()*0.45);
    l_text->move(this->height()*0.55+this->width()*0.10,
                 this->height()*0.05);
    l_text->resize(this->width()-this->width()*0.1,
                   this->height()*0.45);
    l_subText->move(this->height()*0.55+this->width()*0.10,
                    l_text->height()+this->height()*0.1);
    l_subText->resize(this->width()-this->width()*0.1,
                      this->height()*0.35);
    l_text->setText(text);
    l_subText->setText(subText);

}
