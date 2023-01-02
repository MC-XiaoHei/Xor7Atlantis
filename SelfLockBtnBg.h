#ifndef SELFLOCKBTNBG_H
#define SELFLOCKBTNBG_H

#include "ButtonBg.h"

class SelfLockBtnBg : public ButtonBg
{
    Q_OBJECT
public:
    SelfLockBtnBg(QWidget *parent = nullptr);
    void refresh();
    void onClick();
    void onRelease();
    void setBorderRadius(quint64 radius);
private:
    quint64 m_radius=4;
    bool active=false;
protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};

#endif // SELFLOCKBTNBG_H
