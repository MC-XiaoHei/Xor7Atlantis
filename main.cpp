#include "stable.h"
#include "LaunchCore.h"
#include "AuthCore.h"
#include "MainWindow.h"
#include "AutomaticInstanceManager.h"
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
    launch.java=LaunchCore::javaInfoVec.first();
    ver.name="1.16.5";
    ver.gamePath="/home/mc_xiaohei/.minecraft";
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
    SingleApplication::setOrganizationDomain("xor7.tk");
    SingleApplication::setOrganizationName("Xor 7 Studio");
    SingleApplication::setApplicationName("Xor 7 Atlantis");
    SingleApplication::setApplicationVersion(X7A_VER);
    SingleApplication app(
                argc,
                argv,
                true,
                SingleApplication::User|
                SingleApplication::ExcludeAppPath|
                SingleApplication::ExcludeAppVersion);
    SET("instancePath",AutomaticInstanceManagerInstance->read());
    QString path=GET("instancePath")+"Xor 7 Atlantis";
    #ifdef Q_OS_WIN
        path+=".exe";
    #endif
    if(SingleApplication::applicationFilePath()!=path){
        QFile file(path);
        if(!file.exists())
            QFile::copy(SingleApplication::applicationFilePath(),
                        path);
        file.close();
//------------------DISABLE WHEN DEBUG------------------
//        QProcess::startDetached(path);
//        return 0;
//------------------------------------------------------
    }
    QCommandLineParser parser;
    parser.setApplicationDescription("line helper");
    parser.addHelpOption();
    parser.addVersionOption();
//    parser.addOption({
//        {"d","dir"},"set log output dir","filedir","C:\\"
//    });
    parser.process(app);
    QStringList positionList = parser.positionalArguments();
    qDebug() << positionList;

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
