#include "AutomaticInstanceManager.h"

AutomaticInstanceManager::AutomaticInstanceManager(QObject *parent)
    : QObject{parent}
{

}
QString AutomaticInstanceManager::read(){
    QDir().mkpath(QDir::toNativeSeparators(AutomaticFileManagerCfgPath));
    QSettings settings(AutomaticFileManagerCfgPath
                       AutomaticFileManagerCfgName,
                       QSettings::IniFormat);
    QString instancePath=settings.contains("instancePath")?
                settings.value("instancePath").toString():
                AutomaticFileManagerCfgPath;
    settings.beginGroup("automaticInstance");
    settings.setValue("instancePath",instancePath);
    settings.endGroup();
    settings.sync();
    return instancePath;
}
void AutomaticInstanceManager::checkInstance(){

}
