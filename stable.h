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
#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMouseEvent>
#include <QScrollArea>
#include <QBoxLayout>
#include <QScrollBar>
#include <QDateTime>
#include <QSettings>
#include <QFileInfo>
#include <QtNetwork>
#include <QPainter>
#include <QWidget>
#include <cassert>
#include <QLabel>
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

#define X7A_VER QString("Snapshot 0.0.2")
#define MAIN_SIZE_X 840
#define MAIN_SIZE_Y 480
#define Point qDebug()<<__FILE__<<" "<<__LINE__
#define SPTR(t) std::shared_ptr<t>
#define Max(a,b) a>b?a:b
#define Min(a,b) a>b?b:a
#define CreatePtrA(t,name,data) SPTR(t) name=std::make_shared<t>(data)
#define CreatePtr(t,name) SPTR(t) name=std::make_shared<t>()
#define Wait(msec) QEventLoop loop;QTimer::singleShot(msec, &loop, SLOT(quit()));loop.exec()

void throwX(QString at,QString msg,quint8 level);

#endif // STABLE_H

