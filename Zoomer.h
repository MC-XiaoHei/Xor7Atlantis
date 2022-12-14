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
    void updateZOOM(qfloat16 newZ);
    void updateOver(){this->needUpdate=false;}
    bool ifNeedUpdate(){return needUpdate;}
private:
    bool needUpdate=true;
    qfloat16 m_zoomPercent=100;
signals:

};
Q_GLOBAL_STATIC(Zoomer,ZoomerInstance);
#define UPDATE_ZOOM(a) ZoomerInstance->updateZOOM(a)
#define ON_ZOOM_UPDATE if(ZoomerInstance->ifNeedUpdate())
#define UPDATE_OVER ZoomerInstance->updateOver()
#define ZOOM(a) ZoomerInstance->zoom(a)
#define UNZOOM(a) ZoomerInstance->unZoom(a)
#endif // ZOOMER_H
