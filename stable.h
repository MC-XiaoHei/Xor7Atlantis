#ifndef STABLE_H
#define STABLE_H

#include "httpserver/staticfilecontroller.h"
#include "httpserver/httprequesthandler.h"
#include "HttpServer/httplistener.h"
#include <QDesktopServices>
#include <QGraphicsEffect>
#include <QApplication>
#include <QStyleOption>
#include <QPainterPath>
#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QSettings>
#include <QFileInfo>
#include <QtNetwork>
#include <QPainter>
#include <QLabel>
#include <QWidget>
#include <cassert>

#include <QFile>
#include <QUrl>

#ifdef Q_OS_WIN

#include <windowsx.h>
#include <windows.h>

#endif

#ifdef Q_OS_WIN
    #define NATIVES "natives-windows"
    #define SHELL "cmd.exe"
    #define ESuffix ".bat"
#endif
#ifdef Q_OS_LINUX
    #define NATIVES "natives-linux"
    #define SHELL "bash"
#define ESuffix ".sh"
#endif
#ifdef Q_OS_OSX
    #define NATIVES "natives-osx"
#endif
#ifdef Q_OS_UNIX
    #define NATIVES "natives-unix"
#endif

#define X7A_VER QString("Alpha 0.1")
#define SPTR(t) std::shared_ptr<t>
#define CreatePtrA(t,name,data) SPTR(t) name=std::make_shared<t>(data)
#define CreatePtr(t,name) SPTR(t) name=std::make_shared<t>()
#define Wait(msec) QEventLoop loop;QTimer::singleShot(msec, &loop, SLOT(quit()));loop.exec()

void throwX(QString at,QString msg,quint8 level);
bool inElement(quint32 x,quint32 y,QWidget *e);

#endif // STABLE_H

