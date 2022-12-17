#include "LaunchCore.h"

QVector<JavaInfo> LaunchCore::javaInfoVec;
QMap<VerInfo,JsonInfo> LaunchCore::jsonCache;

LaunchCore::LaunchCore(QObject *parent)
    : QObject{parent}
{

}
void LaunchCore::checkJavaInPath(QString path){
    CreatePtr(Shell,s);
    QStringList argu;
    argu.push_back("-version");
    s->connect(s.get(),&Shell::onReceive,[=](QString data){
        QString ver;
        QStringList list;
        if(!data.isNull() && data.contains("\"")){
            JavaInfo info;
            info.path=path;
            list=data.split("\"");
            if(data.contains(QStringLiteral("64-Bit"))) info.amd64=true;
            if(list.size()>0) ver=list[1];
            info.fullVer=ver;
            list=ver.split(".");
            if(list[0]=="1") info.liteVer=list[1].toInt();
            else info.liteVer=list[0].toInt();
            javaInfoVec.push_back(info);
        }
    });
    s->start(path,argu);
    s->waitForFinished();
}
void LaunchCore::getJson(VerInfo ver){
    QVector<GameClassInfo> GameClass;
    GameClass.clear();
    QString jvm,argu,gArguments,jArguments,assetsIndex;
    quint8 verI=0;
    QFile file(ver.jsonPath());
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString value = file.readAll();
    file.close();
    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
    if(!(parseJsonErr.error == QJsonParseError::NoError)){
        throwX("LaunchCore->getJson->readGameCfg",parseJsonErr.errorString(),2);
        return;
    }
    QJsonObject libObj = document.object();
    if(libObj.contains(QStringLiteral("assets"))){
        QJsonValue assetsValue = libObj.value(QStringLiteral("assets"));
        assetsIndex=assetsValue.toString();
        QStringList verlist;
        if(libObj.value(QStringLiteral("assetsIndex")).toObject().value(QStringLiteral("id")).toString()=="legacy"){
            QJsonValue idValue = libObj.value(QStringLiteral("id"));
            verlist = idValue.toString().split(".");
        }else{
            verlist = assetsIndex.split(".");
        }
        if(verlist.size()>0) {verI=verlist.at(1).toInt();}
        else {
            throwX("LaunchCore->getJson->readGameCfg","在读取AssetsIndex时发生错误。",2);
            return;
        }
    }else{
        throwX("LaunchCore->getJson->readGameCfg","在读取Assets时发生错误。",2);
        return;
    }
    if(libObj.contains(QStringLiteral("mainClass"))){
        QJsonValue assetsValue = libObj.value(QStringLiteral("mainClass"));
        argu=QString(" %1").arg(assetsValue.toString());
    }else{
        throwX("LaunchCore->getJson->readGameCfg","在读取MainClass时发生错误。",2);
        return;
    }
    QString arguname=((verI>=13)?("arguments"):("minecraftArguments"));
    if(libObj.contains(arguname)){
        QJsonValue argumentsValue = libObj.value(arguname);
        if(verI>=13){
            QJsonObject argumentsObj = argumentsValue.toObject();
            if(argumentsObj.contains(QStringLiteral("game"))){
                QJsonValue garguValue = argumentsObj.value(QStringLiteral("game"));
                QJsonArray garguArray = garguValue.toArray();
                for(quint16 i=0;i<garguArray.size();i++){
                    QJsonValue garguV=garguArray.at(i);
                    if(garguV.toObject().isEmpty()) argu+=QString(" %1").arg(garguV.toString());
                }
            }else{
                throwX("LaunchCore->getJson->readGameCfg","在读取GameArguments时发生错误。",2);
                return;
            }
            if(argumentsObj.contains(QStringLiteral("jvm"))){
                QJsonValue jarguValue = argumentsObj.value(QStringLiteral("jvm"));
                QJsonArray jarguArray = jarguValue.toArray();
                for(quint16 i=0;i<jarguArray.size();i++){
                    QJsonValue jarguV=jarguArray.at(i);
                    QJsonObject jarguObj=jarguV.toObject();
                    if(!jarguObj.isEmpty()){}
                    else jvm+=QString(" %1").arg(jarguV.toString());
                }
            }else{
                throwX("LaunchCore->getJson->readGameCfg","在读取JvmArguments时发生错误。",2);
                return;
            }
        }else argu+=QString(" %1").arg(argumentsValue.toString());
    }else{
        throwX("LaunchCore->getJson->readGameCfg",QString("在读取%1时发生错误。").arg(arguname),2);
        return;
    }
    quint16 lsize;
    if(libObj.contains(QStringLiteral("libraries"))){
        QJsonValue libValue = libObj.value(QStringLiteral("libraries"));
        if(libValue.isArray()){
            QJsonArray libArray = libValue.toArray();
            lsize=libArray.size();
            for(quint16 i=0;i<lsize;i++){
                GameClassInfo tmpInfo;
                QJsonValue libA = libArray.at(i);
                QJsonObject ArrayObj = libA.toObject();
                tmpInfo.name=ArrayObj["name"].toString();
                if(ArrayObj.contains(QStringLiteral("downloads"))){
                    QJsonValue downloadsValue = ArrayObj.value(QStringLiteral("downloads"));
                    QJsonObject downloadsObj = downloadsValue.toObject();
                    if(!downloadsObj.contains(QStringLiteral("classifiers"))){
                        QJsonValue artifactValue = downloadsObj.value(QStringLiteral("artifact"));
                        QJsonObject artifactObj = artifactValue.toObject();
                        QStringList nameList = tmpInfo.name.split(":");
                        quint8 size=nameList.size();
                        QStringList fList = nameList[0].split(".");
                        quint8 fsize=fList.size();
                        for(quint8 j=0;j<fsize;j++){
                            tmpInfo.path.append(QDir::toNativeSeparators(QString("%1/").arg(fList.at(j))));
                        }
                        for(quint8 j=1;j<size;j++){
                            tmpInfo.path.append(QDir::toNativeSeparators(QString("%1/").arg(nameList.at(j))));
                        }
                        QString t=nameList.at(size-2);
                        tmpInfo.path+=QString("%1-%2.jar").arg(t,nameList.at(size-1));
                        tmpInfo.url=artifactObj["url"].toString();
                        tmpInfo.sha1=artifactObj["sha1"].toString();
                        tmpInfo.isNatives=false;
                        if(GameClass.size()>0){
                            nameList = GameClass.at(GameClass.size()-1).name.split(":");
                            if(nameList.at(nameList.size()-2)==t) GameClass[GameClass.size()-1].jump=true;
                        }
                    }else{
                        QJsonValue NativesValue = downloadsObj.value(QStringLiteral("classifiers"));
                        QJsonObject NativesObj = NativesValue.toObject();
                        if(NativesObj.contains(NATIVES)){
                            QJsonValue nValue = NativesObj.value(NATIVES);
                            QJsonObject nlib = nValue.toObject();
                            if(i>0){
                                tmpInfo.path=nlib["path"].toString();
                                tmpInfo.url=nlib["url"].toString();
                                tmpInfo.sha1=nlib["sha1"].toString();
                            }
                        }
                    }
                }else{
                    QStringList nameList = tmpInfo.name.split(":");
                    quint8 size=nameList.size();
                    QStringList fList = nameList[0].split(".");
                    quint8 fsize=fList.size();
                    for(quint8 j=0;j<fsize;j++){
                        tmpInfo.path.append(QDir::toNativeSeparators(QString("%1/")).arg(fList.at(j)));
                    }
                    for(quint8 j=1;j<size;j++){
                        tmpInfo.path.append(QDir::toNativeSeparators(QString("%1/")).arg(nameList.at(j)));
                    }
                    tmpInfo.path+=QString("%1-%2.jar").arg(nameList.at(size-2),nameList.at(size-1));
                    tmpInfo.url=ArrayObj["url"].toString();
                    tmpInfo.sha1="";
                    tmpInfo.isNatives=false;
                }
                GameClass.push_back(tmpInfo);
            }
        }else{
            throwX("LaunchCore->getJson->readGameCfg","在读取Libraries时发生错误。",2);
            return;
        }
    }else{
        throwX("LaunchCore->getJson->readGameCfg","在读取Libraries时发生错误。",2);
        return;
    }
    if(jsonCache.contains(ver))
        jsonCache.remove(ver);
    JsonInfo jsonI;
    jsonI.argu=argu;
    jsonI.jvm=jvm;
    jsonI.gArguments=gArguments;
    jsonI.jArguments=jArguments;
    jsonI.mainVer=verI;
    jsonI.assetsIndex=assetsIndex;
    jsonI.gameClass=GameClass;
    jsonCache.insert(ver,jsonI);
}
bool LaunchCore::haveNatives(VerInfo ver){
    QDir nDir=QString(ver.verPath()).replace("\"","");
    QFileInfoList list = nDir.entryInfoList();
    return ((list.count()==0)?false:true)&&(nDir.exists());
}
QStringList LaunchCore::getUnzipNativeCmd(VerInfo ver,QString npath){
    if(npath!=""){
        QStringList res;
        QString jarDir=QDir::toNativeSeparators(QString("%1/libraries/%2").arg(ver.gamePath,npath));
        res.push_back(QDir::toNativeSeparators(QString("7z e \"%1\" -o\"%2/natives\" *%3 -r -y").arg(jarDir,ver.verPath(),
                                                                                #ifdef Q_OS_WIN
                                                                                    "dll"
                                                                                #else
                                                                                    "so"
                                                                                #endif
        )));
        res.push_back(QDir::toNativeSeparators(QString("7z e \"%1\" -o\"%2/natives/sha1\" *sha1 -r -y").arg(jarDir,ver.verPath())));
        return res;
    }else{
        throwX("LaunchCore->UnzipNative","Native路径为空！",1);
        return QStringList();
    }
}
void LaunchCore::reloadNatives(VerInfo ver){
    getJson(ver);
    CreatePtr(Shell,s);
    QVector<GameClassInfo> gcInfo=jsonCache.value(ver).gameClass;
    QString path = ver.verPath()+QDir::toNativeSeparators("/X7A/");
    QDir().mkpath(path);
    path+=("reloadNatives" ESuffix);
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    for(quint16 i=0;i<gcInfo.size();i++){
        if(gcInfo[i].isNatives){
            QStringList data=getUnzipNativeCmd(ver,gcInfo[i].path);
            if(!(data.size()>1)) continue;
            file.write(data[0].toLocal8Bit());
            file.write("\n");
            file.write(data[1].toLocal8Bit());
            file.write("\n");
        }
    }
    file.close();
    s->start(path,QStringList());
    s->waitForFinished();
}
void LaunchCore::getJava(){
    checkJavaInPath("java");
    #ifdef Q_OS_WIN
        checkJavaInPath(qgetenv("JAVA_HOME")+"bin\\java");
        CreatePtr(Shell,s);
        s->connect(s.get(),&Shell::onReceive,[=](QString data){
            data=data.replace("\r","");
            QStringList javas=data.split("\n");
            for(auto & str:javas)
                checkJavaInPath(str);
        });
        s->start("where",QStringList("java.exe"));
        Wait(1000);
    #endif
}
QString LaunchCore::getStartCmd(VerInfo ver,LaunchInfo lInfo){
    QString cp="",version="",assetsDir="",cmd="";
    JsonInfo jInfo=jsonCache.value(ver);
    version=QString("Xor 7 Atlantis %1").arg(X7A_VER);
    assetsDir=QDir::toNativeSeparators(QString("%1/assets")).arg(ver.gamePath);
    /*if(jInfo.mainVer<13){*/jInfo.jvm=QString(
        " -Djava.library.path=${natives_directory}"
        " -Dminecraft.launcher.brand=${launcher_name}"
        " -Dminecraft.launcher.version=${launcher_version}"
        " -cp ${classpath}");/*}*/
    jInfo.jvm.insert(0,QDir::toNativeSeparators(QString("%1"
        " -Dminecraft.client.jar=\".minecraft/versions/%2/%2.jar\""
        " -XX:+UnlockExperimentalVMOptions"
        " -XX:+UseG1GC"
        " -XX:G1NewSizePercent=20"
        " -XX:G1ReservePercent=20"
        " -XX:MaxGCPauseMillis=50"
        " -XX:G1HeapRegionSize=16M"
        " -XX:-UseAdaptiveSizePolicy"
        " -XX:-OmitStackTraceInFastThrow"
        " -Xmn128M"
        " -Xmx%3M"
        " -Dfml.ignoreInvalidMinecraftCertificates=true"
        " -Dfml.ignorePatchDiscrepancies=true"
        " -Dlog4j2.formatMsgNoLookups=true"
        " %4").arg(
        lInfo.java.path,
        ver.name,
        QString::number(lInfo.mem),
        #ifdef Q_OS_WIN
            -XX:HeapDumpPath=MojangTricksIntelDriversForPerformance_javaw.exe_minecraft.exe.heapdump/*XX:-DontCompileHugeMethods*/""
        #else
            ""
        #endif
        )));
    QVector<GameClassInfo> gcInfo=jInfo.gameClass;
    if(haveNatives(ver)){
        for(quint16 i=0;i<gcInfo.size();i++){
            if((!gcInfo[i].isNatives)&&!gcInfo[i].jump)
                cp+=QDir::toNativeSeparators(QString(
                    "%1/libraries/%2%3").arg(ver.gamePath,gcInfo[i].path,
                             #ifdef Q_OS_WIN
                                ";"
                             #else
                                ":"
                             #endif
                ));
        }
    }else reloadNatives(ver);
    cp+=QDir::toNativeSeparators(QString("%1/%2.jar").arg(ver.verPath(),ver.name));
    cp=QDir::toNativeSeparators(QString("\"%1\"").arg(cp));
    jInfo.jvm.replace("${classpath}",
                cp);
    jInfo.jvm.replace("-Djava.library.path=${natives_directory}",
                QDir::toNativeSeparators(QString("\"-Djava.library.path=%1/natives\"").arg(ver.verPath())));
    jInfo.jvm.replace("${launcher_name}",
                "\"Xor 7 Atlantis\"");
    jInfo.jvm.replace("${launcher_version}",
                QString("\"Xor 7 Atlantis %1\"").arg(X7A_VER));
    jInfo.argu.replace("${auth_player_name}",
                 QString("\"%1\"").arg(lInfo.profile.username));
    jInfo.argu.replace("${version_name}",QString("\"%1\"").arg(version));
    jInfo.argu.replace("${assets_index_name}",
                 jInfo.assetsIndex);
    jInfo.argu.replace("${auth_access_token}",
                 lInfo.profile.mcAccessToken);
    jInfo.argu.replace("${user_type}",
                 "mojang");
    jInfo.argu.replace("${version_type}",
                 QString("\"Xor 7 Atlantis %1\"").arg(X7A_VER));
    jInfo.argu.replace("${user_properties}","{}");
    if(jInfo.mainVer<=6){
        jInfo.argu.replace("${auth_session}",
                     lInfo.profile.uuid);
        jInfo.argu.replace("${game_assets}",
                     QString("\"%1\\virtual\\legacy\"").arg(assetsDir));
        jInfo.argu.replace("${game_directory}",
                     QString("\"%1\"").arg(ver.gamePath));
    }else{
        jInfo.argu.replace("${assets_root}",
                     QString("\"%1\"").arg(assetsDir));
        jInfo.argu.replace("${auth_uuid}",
                     lInfo.profile.uuid);
        jInfo.argu.replace("${game_directory}",
                     QString("\"%1\"").arg(ver.gamePath));
    }
    if(!jInfo.argu.contains(" --width"))
        jInfo.argu+=QString(" --width %1").arg(QString::number(lInfo.width));
    if(!jInfo.argu.contains(" --height"))
        jInfo.argu+=QString(" --height %1").arg(QString::number(lInfo.width));
    if(lInfo.profile.demo)
        jInfo.argu.append(" --demo");
    cmd=jInfo.jvm+jInfo.argu;
    if(cmd.contains("-DFabricMcEmu\u003d net.minecraft.client.main.Main ")){
        cmd.replace("-DFabricMcEmu\u003d net.minecraft.client.main.Main ","\"-DFabricMcEmu\u003d net.minecraft.client.main.Main \"");
        qDebug()<<"fabric";
    }
    cmd=QDir::toNativeSeparators(cmd);
    return cmd;
    return QString("ERR Ver=%1").arg(QString::number(jInfo.mainVer));
}
