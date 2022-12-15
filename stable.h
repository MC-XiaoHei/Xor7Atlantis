#ifndef STABLE_H
#define STABLE_H

#include "Third-Party/SingleApplication/SingleApplication"
#include "Third-Party/httpserver/staticfilecontroller.h"
#include "Third-Party/httpserver/httprequesthandler.h"
#include "Third-Party/HttpServer/httplistener.h"
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
#include <cstdlib>
#include <QWidget>
#include <cassert>
#include <QLabel>
#include <QFile>
#include <QUrl>

#define AutomaticFileManagerCfgName "automaticFileManager.ini"
#ifdef Q_OS_WIN
    #include <windowsx.h>
    #include <windows.h>
    #define NATIVES "natives-windows"
    #define SHELL "cmd.exe"
    #define ESuffix ".bat"
    #define AutomaticFileManagerCfgPath "C:/Xor 7 Studio/Xor 7 Atlantis/"
#endif
#ifdef Q_OS_LINUX
    #define NATIVES "natives-linux"
    #define SHELL "bash"
    #define ESuffix ".sh"
    #define AutomaticFileManagerCfgPath "/opt/Xor 7 Studio/Xor 7 Atlantis/"
#endif
#ifdef Q_OS_OSX
    #define NATIVES "natives-osx"
    #define AutomaticFileManagerCfgPath "/opt/Xor 7 Studio/Xor 7 Atlantis/"
#endif
#ifdef Q_OS_UNIX
    #define NATIVES "natives-unix"
    #define AutomaticFileManagerCfgPath "/opt/Xor 7 Studio/Xor 7 Atlantis/"
#endif

#define X7A_VER QString("Snapshot 0.0.3")
#define MAIN_SIZE_X 840
#define MAIN_SIZE_Y 480
#define Point qDebug()<<__FILE__<<" "<<__LINE__
#define SPTR(t) std::shared_ptr<t>
#define Max(a,b) a>b?a:b
#define Min(a,b) a>b?b:a
#define CreatePtrA(t,name,data) SPTR(t) name=std::make_shared<t>(data)
#define CreatePtr(t,name) SPTR(t) name=std::make_shared<t>()
#define Wait(msec) QEventLoop loop;QTimer::singleShot(msec, &loop, SLOT(quit()));loop.exec()
#define ShowOnTop(a) Qt::WindowFlags flags=a->windowFlags();flags|=Qt::WindowStaysOnTopHint;a->setWindowFlags(flags);a->show();flags&=~Qt::WindowStaysOnTopHint;a->setWindowFlags(flags);a->showNormal()

void throwX(QString at,QString msg,quint8 level);

#endif // STABLE_H

