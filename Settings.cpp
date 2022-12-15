#include "Settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{

}
void Settings::set(QString key,QString value){
    if(values.contains(key))
        remove(key);
    values.insert(key,value);
}
void Settings::remove(QString key){
    values.remove(key);
}
QString Settings::get(QString key){
    return values.value(key);
}
