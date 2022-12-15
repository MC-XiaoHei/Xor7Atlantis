#include "stable.h"
#include "LaunchCore.h"
#include "AuthCore.h"
#include "MainWindow.h"
#include <QMessageBox>

void startGame(){
    VerInfo ver;
    LaunchInfo launch;
    AuthProfile profile;
    profile.mcAccessToken="accessT";
    profile.uuid="uuid";
    profile.username="player";
    launch.profile=profile;
    launch.height=400;
    launch.width=640;
    launch.mem=1024;
    launch.java=LaunchCore::javaInfoVec.at(2);
    ver.name="1.7.10";
    ver.gamePath="D:\\Xor 7 Championship Client\\.minecraft";
    LaunchCore::getJson(ver);
    QString cmd=LaunchCore::getStartCmd(ver,launch);
    QString path = ver.verPath()+QDir::toNativeSeparators("/X7A/");
    QDir().mkpath(path);
    path+=("start" ESuffix);
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    file.write(cmd.toLocal8Bit());
    file.close();
    CreatePtr(Shell,s);
    s->connect(s.get(),&Shell::onReceive,[=](QString data){qDebug()<<data;});
    LaunchCore::reloadNatives(ver);
    s->start(path,QStringList());
}
int main(int argc, char *argv[]){
    SingleApplication app(
                argc,
                argv,
                true,
                SingleApplication::User|
                SingleApplication::ExcludeAppPath|
                SingleApplication::ExcludeAppVersion);
    if(app.isSecondary()){
        app.sendMessage(app.applicationDirPath().toUtf8());
        app.exit(0);
        return 0;
    }
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Xor7Atlantis_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QObject::connect(&app,&SingleApplication::instanceStarted,&w,[&](){ShowOnTop((&w));});
    QObject::connect(&app,&SingleApplication::receivedMessage,&w,&MainWindow::onReceiveMsg);
    w.show();
    w.activateWindow();
    LaunchCore::getJava();
//    AuthCore * ac=new AuthCore;
//    ac->connect(ac,&AuthCore::authProgressUpdate,ac,[=](bool state,QString msg){
//        qDebug()<<msg;
//    });
//    ac->ms_login();
//    Wait(1000);
//    for(JavaInfo j:LaunchCore::javaInfoVec){
//        qDebug()<<j.path<<" "<<j.fullVer;
//    }
//    startGame();
    return app.exec();
}
void throwX(QString at,QString msg,quint8 level){
    qDebug()<<at<<" "<<msg<<" "<<level;
}
