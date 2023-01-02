#include "UpdateManager.h"

UpdateManager::UpdateManager(QObject *parent)
    : QObject{parent}
{

}
QString UpdateManager::read(){
    QDir().mkpath(QDir::toNativeSeparators(RootPath));
    QSettings settings(RootPath
                       RootCfgName,
                       QSettings::IniFormat);
    QString instancePath=settings.contains("instancePath")?
                settings.value("instancePath").toString():
                RootPath;
    settings.beginGroup("updateManager");
    settings.setValue("instancePath",instancePath);
    settings.endGroup();
    settings.sync();
    return instancePath;
}
void UpdateManager::checkInstance(){

}
