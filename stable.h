#ifndef STABLE_H
#define STABLE_H

#include "./Third-Party/SingleApplication/SingleApplication"
#include "./Third-Party/HttpServer/staticfilecontroller.h"
#include "./Third-Party/HttpServer/httprequesthandler.h"
#include "./Third-Party/HttpServer/httplistener.h"
#include <QDesktopServices>
#include <QGraphicsEffect>
#include <QStackedLayout>
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

//OPENFRP
//https://of-dev-api.bfsea.xyz/api?action=checkupd&os=linux&arch=amd64
//https://obs.cstcloud.cn/share/obs/zgitnetwork/ofclient/frpc/frpc_windows_386.exe
#define RootCfgName "RootCfg.ini"
#ifdef Q_OS_WIN
    #include <windowsx.h>
    #include <windows.h>
    #define NATIVES "natives-windows"
    #define SHELL "cmd.exe"
    #define ESuffix ".bat"
    #define RootPath qgetenv("APPDATA")+"/Xor 7 Studio/Xor 7 Atlantis/"
    #define USERNAME qgetenv("USERNAME")
#endif
#ifdef Q_OS_LINUX
    #define NATIVES "natives-linux"
    #define SHELL "bash"
    #define ESuffix ".sh"
    #define RootPath "/opt/Xor 7 Studio/Xor 7 Atlantis/"
    #define USERNAME qgetenv("USER")
#endif
#ifdef Q_OS_OSX
    #define NATIVES "natives-osx"
    #define RootPath "/opt/Xor 7 Studio/Xor 7 Atlantis/"
    #define USERNAME qgetenv("USER")
#endif

#define X7A_VER QString("Snapshot 0.1.0")
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
#define getBtnTextSize(btn) btn->fontMetrics().boundingRect(btn->text()).size()

void throwX(QString at,QString msg,quint8 level);

#endif // STABLE_H

