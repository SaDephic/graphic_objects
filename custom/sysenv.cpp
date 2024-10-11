#include "sysenv.h"

sysenv::sysenv(){
    //host_auth
    host_auth = QProcessEnvironment::systemEnvironment().value("HOST_AUTH_CRE");//,"https://localhost:8089/StreetBox/authorization");

    //load prefs
    QFile f(file().soft + QDir::separator() + file().a);
    if(f.open(QFile::ReadOnly)){
        QJsonObject doc = QJsonDocument::fromJson(f.readAll()).object();
        QString lf = doc["lastFolder"].toString();
        QString lu = doc["lastUser"].toString();
        if(!lf.isEmpty()) last_folder = lf;
        if(!lu.isEmpty()) user_login = lu;
        f.close();
    }
}
