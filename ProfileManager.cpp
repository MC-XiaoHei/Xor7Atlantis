#include "ProfileManager.h"

ProfileManager::ProfileManager(QObject *parent)
    : QObject{parent}
{

}
void ProfileManager::read(){
    QFile file(cfgPath+"profiles.json");
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    QJsonParseError parseError;
    QJsonDocument doc=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error==QJsonParseError::NoError){
        throwX("账户管理器","读取账户存储文件时发生错误",0);
        return;
    }
}
QList<AuthProfile> ProfileManager::getAll(){
    return profiles;
}
AuthProfile ProfileManager::get(quint16 n){
    return profiles.at(n);
}
void ProfileManager::push_front(AuthProfile profile){
    profiles.push_front(profile);
}
void ProfileManager::swap(quint16 a,quint16 b){
    profiles.swapItemsAt(a,b);
}
void ProfileManager::remove(quint16 n){
    profiles.remove(n);
}
