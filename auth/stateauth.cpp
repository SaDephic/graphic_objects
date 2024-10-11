#include "stateauth.h"

stateauth::stateauth(){}

stateauth::~stateauth(){}

void stateauth::setUser(QString _user){
    user = _user;
}

void stateauth::setStatesAuth(bool _state){
    state = _state;
}

void stateauth::setPrevileges(QVector<QString> _permissions){
    permissions = _permissions;
}

void stateauth::setRegion(int _region){
    region = _region;
}

void stateauth::setAreas(QVector<int> _areas){
    areas = _areas;
}

QString stateauth::areas_text(){
    if(areas.isEmpty())
        return QString();
    if(areas.contains(-1)){
        return "*";
    }
    QString r;
    for(int i=0; i<areas.size(); ++i){
        r += QString::number(areas[i]) + " ";
    }
    return r;
}

QString stateauth::permissions_text(){
    if(permissions.isEmpty())
        return QString();
    QString r;
    for(int i=0; i<permissions.size()-1; ++i){
        r += permissions[i] + "\n";
    }
    return r;
}

QString stateauth::uperm(){
    return user + "\n" +
           QString::number(region) + "\n" +
           areas_text() + "\n" +
           permissions_text();
}
