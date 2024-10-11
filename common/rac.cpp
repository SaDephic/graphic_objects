#include "rac.h"

QString racobject::path(){
    return QDir::separator() + QString::number(region) + QDir::separator() + QString::number(area) + QDir::separator() + QString::number(number) + QDir::separator();
}

QString racobject::nameTitle(){
    return QString::number(region) + QDir::separator()
           + QString::number(area) + QDir::separator()
           + QString::number(number) + " : "
           + descObject;
}

bool racobject::operator ==(const racobject &o){
    return region == o.region && area == o.area && number == o.number;
}
