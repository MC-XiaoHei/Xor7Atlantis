#ifndef MINECRAFTHEAD_H
#define MINECRAFTHEAD_H

#include "stable.h"

class MinecraftHead : public QWidget
{
    Q_OBJECT
public:
    explicit MinecraftHead(QWidget *parent = nullptr);
    void setSize(quint64 size);
signals:

};

#endif // MINECRAFTHEAD_H
