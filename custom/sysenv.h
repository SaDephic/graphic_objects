#ifndef SYSENV_H
#define SYSENV_H

#include <QFile>
#include <QDir>
#include "common/filedir.h"
#include <QObject>
#include <QProcessEnvironment>

#include <QJsonDocument>
#include <QJsonObject>

class sysenv : public QObject{

public:
    QString host_auth;
    QString last_folder;
    QString user_login;
    sysenv();
    ~sysenv(){
        QFile f(file().soft + QDir::separator() + file().a);
        if(f.open(QFile::WriteOnly)){
            QJsonObject o;
            o["lastFolder"] = (QString)last_folder;
            o["lastUser"] = (QString)user_login;

            QJsonDocument doc(o);
            f.write(doc.toJson());
        }
    }
};

#endif // SYSENV_H
