#ifndef AuthCore_H
#define AuthCore_H

#include "stable.h"
#include "DownloadCore.h"
#include "UpdateManager.h"
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
            authServer,
            extraInfo="普通用户";
    bool demo=false;
    //authServer:
    //"offline" = 离线账户
    //"microsoft" = 微软账户
    //"authlib:${url}" = Authlib账户
    //"universal:${code}" = 统一通行证账户
};

class AuthCore : public QObject
{
    Q_OBJECT
private:
    QString redirectUri;
    stefanfrings::HttpListener *m_listener = nullptr;
    bool m_errState=false;
    bool isRunning=false;
public:
    AuthProfile profile;
    explicit AuthCore(QObject *parent = nullptr);
    void offline_login(QString username, bool demo=false);
    void ms_login();
    void ms_getCode(std::function<void(bool,QString)> func);
    void ms_getMSToken(std::function<void(QNetworkReply*)> func);
    void ms_getXBLToken(std::function<void(QNetworkReply*)> func);
    void ms_getXSTSToken(std::function<void(QNetworkReply*)> func);
    void ms_getMCToken(std::function<void(QNetworkReply*)> func);
    void ms_getUUID(std::function<void(QNetworkReply*)> func);
    void parseSkin();
    static bool isAlexDefault(QString uuid);
    static QString getOfflinePlayerUUID(QString username);
    static QNetworkRequest parseRequest(QString url,QMap<QString,QString> header);
    static void post(QString url,QMap<QString,QString> header,QByteArray data,std::function<void(QNetworkReply*)> func);
signals:
    void finished();
    void authProgressUpdate(bool state,QString msg,QString progress);
};

#endif // AuthCore_H
