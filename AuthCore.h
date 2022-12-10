#ifndef AuthCore_H
#define AuthCore_H

#include "stable.h"
struct AuthProfile{
    QString uuid,
            email,
            msCode,
            skinUrl,
            username,
            userHash,
            xblToken,
            xstsToken,
            accessToken,
            refreshToken,
            mcAccessToken,
            authServer;
    bool demo=false;
    //"offline" = 离线登录
    //"microsoft" = 正版(微软)登录
    //"authlib:${url}" = Authlib登录
};

class AuthCore : public QObject
{
    Q_OBJECT
private:
    AuthProfile *m_profile=new AuthProfile;
    QString redirectUri;
    stefanfrings::HttpListener *m_listener = nullptr;
    bool m_errState=false;
    bool isRunning=false;
public:
    explicit AuthCore(QObject *parent = nullptr);
    void ms_login();
    void ms_getCode(std::function<void(bool,QString)> func);
    void ms_getMSToken(std::function<void(QNetworkReply*)> func);
    void ms_getXBLToken(std::function<void(QNetworkReply*)> func);
    void ms_getXSTSToken(std::function<void(QNetworkReply*)> func);
    void ms_getMCToken(std::function<void(QNetworkReply*)> func);
    void ms_getUUID(std::function<void(QNetworkReply*)> func);
    static QNetworkRequest parseRequest(QString url,QMap<QString,QString> header);
    static void post(QString url,QMap<QString,QString> header,QByteArray data,std::function<void(QNetworkReply*)> func);
signals:
    void authProgressUpdate(bool state,QString msg,QString progress);
};

#endif // AuthCore_H
