#include "stable.h"
#include "LaunchCore.h"
#include "AuthCore.h"
#include "MainWindow.h"

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
    launch.java=LaunchCore::javaInfoVec.at(1);
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
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Xor7Alu_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    QFont font;
    font.setFamily("Microsoft YaHei");
    a.setFont(font);
    LaunchCore::getJava();
    AuthCore * ac=new AuthCore;
    ac->connect(ac,&AuthCore::authProgressUpdate,ac,[=](bool state,QString msg){
        qDebug()<<msg;
    });
//    ac->ms_login();
    MainWindow w;
    w.show();
    w.activateWindow();
    Wait(1000);
    for(JavaInfo j:LaunchCore::javaInfoVec){
        qDebug()<<j.path<<" "<<j.fullVer;
    }
//    startGame();
    return a.exec();
}
void throwX(QString at,QString msg,quint8 level){
    qDebug()<<at<<" "<<msg<<" "<<level;
}
