#ifndef ZOOMER_H
#define ZOOMER_H
#include "stable.h"

class Zoomer : public QObject
{
    Q_OBJECT
public:
    explicit Zoomer(QObject *parent = nullptr);
    quint64 zoom(double base);
    quint64 unZoom(quint64 base);
private:
    qfloat16 m_zoomPercent=100;
signals:

};
Q_GLOBAL_STATIC(Zoomer,ZoomerInstance);
#define ZOOM(a) ZoomerInstance->zoom(a)
#define UNZOOM(a) ZoomerInstance->unZoom(a)
#endif // ZOOMER_H
