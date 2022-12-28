#include "AuthCore.h"
#include "AuthWebController.h"

AuthCore::AuthCore(QObject *parent)
    : QObject{parent}{
}
void AuthCore::ms_login(){
    emit authProgressUpdate(true,"微软登录:正在获取微软验证Code","正在获取微软验证Code...");
    ms_getCode([=](bool state,QString data){
    if(!state){
        this->m_errState=true;
        emit authProgressUpdate(false,"微软登录:用户已取消登录.","失败");
        return;
    }
    m_profile->msCode=data;
    emit authProgressUpdate(true,"微软登录:成功获取到微软验证Code","正在获取微软验证Token...");
    ms_getMSToken([=](QNetworkReply* reply){
    QJsonDocument *doc=new QJsonDocument(QJsonDocument::fromJson(reply->readAll()));
    m_profile->accessToken=doc->object().value("access_token").toString();
    m_profile->refreshToken=doc->object().value("refresh_token").toString();
    emit authProgressUpdate(true,"微软登录:成功获取到微软验证Token","正在获取Xbox Live验证Token...");
    ms_getXBLToken([=](QNetworkReply* reply){
    QJsonDocument *doc=new QJsonDocument(QJsonDocument::fromJson(reply->readAll()));
    m_profile->xblToken=doc->object().value("Token").toString();
    m_profile->userHash=doc->object()
            .value("DisplayClaims").toObject()
            .value("xui").toArray()
            .begin()->toObject().value("uhs").toString();
    emit authProgressUpdate(true,"微软登录:成功获取到Xbox Live验证Token","正在获取XSTS验证Token...");
    ms_getXSTSToken([=](QNetworkReply* reply){
    QJsonDocument *doc=new QJsonDocument(QJsonDocument::fromJson(reply->readAll()));
    m_profile->xstsToken=doc->object().value("Token").toString();
    QString userHash=doc->object()
            .value("DisplayClaims").toObject()
            .value("xui").toArray()
            .begin()->toObject().value("uhs").toString();
    if(userHash!=m_profile->userHash){
        this->m_errState=true;
        emit authProgressUpdate(false,"微软登录:微软API返回的两个User Hash不匹配.","失败");
        return;
    }
    emit authProgressUpdate(true,"微软登录:成功获取到XSTS验证Token","正在获取Minecraft Token...");
    ms_getMCToken([=](QNetworkReply* reply){
    QJsonDocument *doc=new QJsonDocument(QJsonDocument::fromJson(reply->readAll()));
    m_profile->mcAccessToken=doc->object().value("access_token").toString();
    emit authProgressUpdate(true,"微软登录:成功获取到Minecraft Token","正在获取Minecraft Profile...");
    ms_getUUID([=](QNetworkReply* reply){
    QJsonDocument *doc=new QJsonDocument(QJsonDocument::fromJson(reply->readAll()));
    m_profile->uuid=doc->object().value("id").toString();
    m_profile->username=doc->object().value("name").toString();
    QJsonArray skins=doc->object().value("skins").toArray();
    bool flag=false;
    for(QJsonValueRef ref:skins){
        QJsonObject obj=ref.toObject();
        if(obj.value("state")=="ACTIVE"){
            m_profile->skinUrl=obj.value("url").toString();
            flag=true;
            break;
        }
    }
    if(!flag){
        this->m_errState=true;
        emit authProgressUpdate(true,"微软登录:成功获取到Minecraft Profile,但没有活动状态的皮肤","登录成功");
    }else{
        emit authProgressUpdate(true,"微软登录:成功获取到Minecraft Profile","登录成功");
    }
});});});});});});}
void AuthCore::ms_getCode(std::function<void(bool,QString)> func){
    QTcpServer *server=new QTcpServer();
    server->listen(QHostAddress::LocalHost);
    QString port=QString("%1").arg(server->serverPort());
    server->close();
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QSettings *listenerSettings=new QSettings;
    listenerSettings->beginGroup("listener");
    listenerSettings->setValue("port",port);
    this->redirectUri=QString("http%3A%2F%2Flocalhost%3A%1").arg(port);
    AuthWebController *controller=new AuthWebController(qApp);
    if(m_listener!=nullptr)
        delete m_listener;
    m_listener=new HttpListener(listenerSettings,controller,qApp);
    QUrl *url=new QUrl(QString(
        "https://login.microsoftonline.com/consumers/oauth2/v2.0/authorize?"
        "client_id=153b7e99-4545-4c18-b1c1-619121bb36b6&"
        "response_type=code&"
        "redirect_uri=http%3A%2F%2Flocalhost%3A%1&"
        "response_mode=query&"
        "prompt=select_account&"
        "scope=XboxLive.signin%20XboxLive.offline_access").arg(port));
    QDesktopServices::openUrl(*url);
    connect(controller,&AuthWebController::over,this,[&](){m_listener->close();});
    connect(controller,&AuthWebController::over,this,func);
}
void AuthCore::ms_getMSToken(std::function<void(QNetworkReply*)> func){
    QMap<QString,QString> header;
    header["Content-Type"]="application/x-www-form-urlencoded";
    QString url="https://login.microsoftonline.com/consumers/oauth2/v2.0/token";
    AuthCore::post(url,header,QString("client_id=153b7e99-4545-4c18-b1c1-619121bb36b6&"
                                      "code=%1&"
                                      "grant_type=authorization_code&"
                                      "redirect_uri=%2&"
                                      "scope=XboxLive.signin%20XboxLive.offline_access").arg(m_profile->msCode).arg(this->redirectUri).toUtf8(),func);
}
void AuthCore::ms_getXBLToken(std::function<void(QNetworkReply*)> func){
    QMap<QString,QString> header;
    header["Content-Type"]=header["Accept"]="application/json";
    QJsonDocument doc;
    QJsonObject obj,properties;
    properties["AuthMethod"]="RPS";
    properties["SiteName"]="user.auth.xboxlive.com";
    properties["RpsTicket"]="d=%1";
    obj["RelyingParty"]="http://auth.xboxlive.com";
    obj["TokenType"]="JWT";
    obj["Properties"]=properties;
    doc.setObject(obj);
    QString request=doc.toJson();
    request=request.arg(m_profile->accessToken);
    AuthCore::post("https://user.auth.xboxlive.com/user/authenticate",
                   header,request.toUtf8(),func);
}
void AuthCore::ms_getXSTSToken(std::function<void(QNetworkReply*)> func){
    QMap<QString,QString> header;
    header["Content-Type"]=header["Accept"]="application/json";
    QJsonDocument doc;
    QJsonObject obj,properties;
    QJsonArray userTokens;
    userTokens.append(m_profile->xblToken);
    properties["SandboxId"]="RETAIL";
    properties["UserTokens"]=userTokens;
    obj["RelyingParty"]="rp://api.minecraftservices.com/";
    obj["TokenType"]="JWT";
    obj["Properties"]=properties;
    doc.setObject(obj);
    AuthCore::post("https://xsts.auth.xboxlive.com/xsts/authorize",
                   header,doc.toJson(),func);
}
void AuthCore::ms_getMCToken(std::function<void(QNetworkReply*)> func){
    QMap<QString,QString> header;
    header["Content-Type"]=header["Accept"]="application/json";
    QJsonDocument doc;
    QJsonObject obj;
    obj["identityToken"]=QString("XBL3.0 x=%1;%2")
            .arg(m_profile->userHash)
            .arg(m_profile->xstsToken);
    doc.setObject(obj);
    AuthCore::post("https://api.minecraftservices.com/authentication/login_with_xbox",
                   header,doc.toJson(),func);
}
void AuthCore::ms_getUUID(std::function<void(QNetworkReply*)> func){
    QMap<QString,QString> header;
    header["Accept"]="application/json";
    header["Authorization"]=QString("Bearer %1").arg(m_profile->mcAccessToken);
    QNetworkAccessManager *manager=new QNetworkAccessManager;
    connect(manager,&QNetworkAccessManager::finished,func);
    manager->get(parseRequest(
        "https://api.minecraftservices.com/minecraft/profile",header));
}
QNetworkRequest AuthCore::parseRequest(QString url,QMap<QString,QString> header){
    QNetworkRequest request(url);
    for(QString key:header.keys())
        request.setRawHeader(key.toUtf8(),header.value(key).toUtf8());
    return request;
}
void AuthCore::post(QString url,QMap<QString,QString> header,QByteArray data,std::function<void(QNetworkReply*)> func){
    QNetworkAccessManager *manager=new QNetworkAccessManager;
    connect(manager,&QNetworkAccessManager::finished,func);
    manager->post(parseRequest(url,header),data);
}
