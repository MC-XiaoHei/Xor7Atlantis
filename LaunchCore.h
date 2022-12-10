#ifndef LAUNCHCORE_H
#define LAUNCHCORE_H
#include "stable.h"
#include "Shell.h"
#include "AuthCore.h"

struct JavaInfo{
    quint8 liteVer;
    QString path,
            fullVer;
    bool amd64=false;
};
struct GameClassInfo{
    QString name,
            path,
            url,
            sha1;
    bool isNatives=true,
         jump=false;
};
struct JsonInfo{
    quint8 mainVer;
    QString assetsIndex,jvm,argu,gArguments,jArguments;
    QVector<GameClassInfo> gameClass;
};
struct LaunchInfo{
    qint32 mem,
           width,
           height;
    JavaInfo java;
    AuthProfile profile;
};
struct VerInfo{
    QString gamePath,
            name,
            javaPath;
    bool useIndependentInfo=false,
         verDivide=false;
    LaunchInfo independentInfo;
    QString verPath() const{
        return QDir::toNativeSeparators(
            QString("%1/versions/%2")
                .arg(gamePath,name));
    }
    QString jsonPath() const{
        return QDir::toNativeSeparators(
            QString("%1/%2.json")
                .arg(verPath(),name));
    }
    QString filePath() const{
        return QDir::toNativeSeparators(
            verDivide?gamePath:verPath());
    }
    friend bool operator<(VerInfo a,VerInfo b){
        return a.jsonPath()<b.jsonPath();
    }
};

class LaunchCore : public QObject
{
    Q_OBJECT
public:
    explicit LaunchCore(QObject *parent = nullptr);
    static QVector<JavaInfo> javaInfoVec;
    static QMap<VerInfo,JsonInfo> jsonCache;
    static void checkJavaInPath(QString path);
    static void getJson(VerInfo ver);
    static void reloadNatives(VerInfo ver);
    static QStringList getUnzipNativeCmd(VerInfo ver,QString npath);
    static bool haveNatives(VerInfo ver);
    static void getJava();
    static QString getStartCmd(VerInfo ver,LaunchInfo lInfo);
    //    static void startGame();
signals:

};

#endif // LAUNCHCORE_H
