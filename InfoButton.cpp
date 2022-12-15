#include "InfoButton.h"

InfoButton::InfoButton(QWidget *parent)
    : QPushButton{parent}
{
    this->setLayout(layout);
    layout->addWidget(ui_icon);
    layout->addLayout(vLayout,this->height());
    vLayout->addStretch();
    vLayout->addWidget(l_text);
    vLayout->addWidget(ui_line);
    vLayout->addWidget(l_subText);
    vLayout->addStretch();
    icon=QIcon(":/Images/Icon/home.png");
    ui_line->setMaximumHeight(ZOOM(2));
    ui_line->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    l_text->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    l_subText->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    ui_icon->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    l_text->setStyleSheet("background-color:rgba(255,255,255,0);");
    l_subText->setStyleSheet("background-color:rgba(255,255,255,0);");
    ui_icon->setStyleSheet("background-color:rgba(255,255,255,0);");
    ui_line->setStyleSheet("background-color:rgb(0,0,0);");
    QFont font;
    font.setPixelSize(ZOOM(16));
    l_text->setFont(font);
    font.setPixelSize(ZOOM(12));
    l_subText->setFont(font);
}
void InfoButton::resizeEvent(QResizeEvent *event){
    ui_icon->setIcon(icon);
    ui_icon->setIconSize(QSize(this->height()*0.9,
                               this->height()*0.9));
    l_text->setText(text);
    l_subText->setText(subText);
    if(transparent) this->setStyleSheet(QString(
        "border-radius:%1px;"
        "background-color:rgba(255,255,255,0);")
        .arg(ZOOM(8)));
    else this->setStyleSheet(QString(
        "border-radius:%1px;"
        "background-color:rgba(255,255,255,200);")
        .arg(ZOOM(8)));
}
