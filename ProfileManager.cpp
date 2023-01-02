#include "ProfileManager.h"

ProfileManager::ProfileManager(QObject *parent)
    : QObject{parent}
{
}
void ProfileManager::read(){
    QDir().mkpath(CfgPath);
    QFile file(CfgPath+"profiles.json");
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text)){
        throwX("读取profile.json","读取账户存储文件时发生错误",0);
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
            profiles.push_front(profile);
        }
    }
    else{
        AuthProfile *profile=new AuthProfile;
        profile->username=USERNAME;
        profile->uuid=AuthCore::getOfflinePlayerUUID(profile->username);
        profile->email=
        profile->msCode=
        profile->skinUrl=
        profile->userHash=
        profile->xblToken=
        profile->xstsToken=
        profile->accessToken=
        profile->mcAccessToken=
        profile->refreshToken="";
        profile->authServer="offline";
        profiles.push_front(profile);
        choose(0);
    }
    save();
}
AuthProfile* ProfileManager::getNow(){
    return get(now);
}
void ProfileManager::choose(quint64 n){
    now=n;
}
QList<AuthProfile *> ProfileManager::getAll(){
    return profiles;
}
AuthProfile* ProfileManager::get(quint64 n){
    return profiles[n];
}
void ProfileManager::save(){
    QJsonDocument doc;
    QJsonArray array;
    for(const auto &profile:profiles){
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
        throwX("保存profile.json","打开账户存储文件时发生错误",0);
        return;
    }
    QTextStream stream(&file);
    stream << doc.toJson();
    file.close();
}
void ProfileManager::push_front(AuthProfile* profile){
    profiles.push_front(profile);
    quint8 cnt=0;
    QList<quint64> needRemoves;
    for(quint64 i=0;i<profiles.size();i++){
        AuthProfile* p=profiles.at(i);
        if(p->uuid==profile->uuid &&
                p->authServer==profile->authServer){
            if(cnt>=1) needRemoves.append(i);
            cnt++;
        }
    }
    for(auto index:qAsConst(needRemoves))
        profiles.removeAt(index);
    now=0;
}
void ProfileManager::swap(quint64 a, quint64 b){
    profiles.swapItemsAt(a,b);
}
void ProfileManager::remove(quint64 n){
    profiles.remove(n);
}
