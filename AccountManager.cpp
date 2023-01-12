#include "AccountManager.h"

AccountManager::AccountManager(QObject *parent)
    : QObject{parent}
{
}
void AccountManager::read(){
    QDir().mkpath(CfgPath);
    QFile file(CfgPath+"profiles.json");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        throwX("读取profiles.json","读取账户存储文件时发生错误",0);
        return;
    }
    QByteArray data=file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
    QJsonArray array;
    if(!doc.isEmpty() && doc.isArray()){
        array=doc.array();
        for(auto value:qAsConst(array)){
            QJsonObject obj=value.toObject();
            AuthProfile *profile=new AuthProfile;
            profile->uuid=obj["uuid"].toString();
            profile->email=obj["email"].toString();
            profile->msCode=obj["msCode"].toString();
            profile->skinUrl=obj["skinUrl"].toString();
            profile->username=obj["username"].toString();
            profile->userHash=obj["userHash"].toString();
            profile->xblToken=obj["xblToken"].toString();
            profile->xstsToken=obj["xstsToken"].toString();
            profile->accessToken=obj["accessToken"].toString();
            profile->authServer=obj["authServer"].toString();
            profile->mcAccessToken=obj["mcAccessToken"].toString();
            profile->refreshToken=obj["refreshToken"].toString();
            minecraftProfiles.push_front(profile);
        }
    }
    else{
        AuthCore *ac=new AuthCore(this);
        ac->offline_login(USERNAME);
        minecraftProfiles.push_front(&ac->profile);
        chooseMinecraftProfile(0);
    }
    save();
}
void AccountManager::save(){
    QJsonDocument doc;
    QJsonArray array;
    for(const auto &profile:minecraftProfiles){
        QJsonObject obj;
        obj["uuid"]=profile->uuid;
        obj["email"]=profile->email;
        obj["msCode"]=profile->msCode;
        obj["skinUrl"]=profile->skinUrl;
        obj["username"]=profile->username;
        obj["userHash"]=profile->userHash;
        obj["xblToken"]=profile->xblToken;
        obj["xstsToken"]=profile->xstsToken;
        obj["accessToken"]=profile->accessToken;
        obj["authServer"]=profile->authServer;
        obj["mcAccessToken"]=profile->mcAccessToken;
        obj["refreshToken"]=profile->refreshToken;
        array.append(obj);
    }
    doc.setArray(array);
    QDir().mkpath(CfgPath);
    QFile file(CfgPath+"profiles.json");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        throwX("保存profiles.json","打开账户存储文件时发生错误",0);
        return;
    }
    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}
AuthProfile* AccountManager::getNowMinecraftProfile(){
    return minecraftProfiles.at(mp_now);
}
void AccountManager::chooseMinecraftProfile(quint64 n){
    mp_now=n;
}
QList<AuthProfile *> AccountManager::getMinecraftProfiles(){
    return minecraftProfiles;
}
void AccountManager::pushMinecraftProfile(AuthProfile* profile){
    minecraftProfiles.push_front(profile);
    quint8 cnt=0;
    QList<quint64> needRemoves;
    for(quint64 i=0;i<minecraftProfiles.size();i++){
        AuthProfile* p=minecraftProfiles.at(i);
        if(p->uuid==profile->uuid &&
                p->authServer==profile->authServer){
            if(cnt>=1) needRemoves.append(i);
            cnt++;
        }
    }
    for(auto index:qAsConst(needRemoves))
        minecraftProfiles.removeAt(index);
    mp_now=0;
}
qsizetype AccountManager::minecraftProfileSize(){
    return minecraftProfiles.size();
}
OpenFrpProfile* AccountManager::getNowOpenFrpProfile(){
    return openFrpProfiles.at(ofp_now);
}
void AccountManager::chooseOpenFrpProfile(quint64 n){
    ofp_now=n;
}
QList<OpenFrpProfile *> AccountManager::getOpenFrpProfiles(){
    return openFrpProfiles;
}
void AccountManager::pushOpenFrpProfile(OpenFrpProfile* profile){
    openFrpProfiles.push_front(profile);
    quint8 cnt=0;
    QList<quint64> needRemoves;
    for(quint64 i=0;i<openFrpProfiles.size();i++){
        OpenFrpProfile* p=openFrpProfiles.at(i);
        if(p->id==profile->id){
            if(cnt>=1) needRemoves.append(i);
            cnt++;
        }
    }
    for(auto index:qAsConst(needRemoves))
        openFrpProfiles.removeAt(index);
    ofp_now=0;
}
qsizetype AccountManager::openFrpProfileSize(){
    return openFrpProfiles.size();
}
