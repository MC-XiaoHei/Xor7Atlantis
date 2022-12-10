#include "Zoomer.h"

Zoomer::Zoomer(QObject *parent)
    : QObject{parent}
{
}
quint64 Zoomer::zoom(double base){
    return m_zoomPercent*0.01*base;
}
quint64 Zoomer::unZoom(quint64 base){
    return base/(m_zoomPercent*0.01);
}
