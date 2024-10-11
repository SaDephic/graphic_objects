#ifndef FILEDIR_H
#define FILEDIR_H

#include <QString>
#include <QDir>

struct file {
    //files
    QString m = "map.png";//map
    QString t = "template.tmpl";//template
    QString s = "cross.svg";//svg
    QString e = "excross";//extend_data
    QString c = "con";//connection_settings
    QString a = "app";//app_settings
    QString u = "cre";//aut data

    //local directory paths
    QString tempsys = QDir::tempPath() + QDir::separator() + "cross_editor";//basic folder
    QString apps = QDir::homePath() + QDir::separator() + ".ASUDD";//basic folder
    QString app = apps + QDir::separator() + "cross_editor";//app
    QString soft = app + QDir::separator() + "app";//app_data
    QString cross = app + QDir::separator() + "cross";//local_crosses
    QString dump = app + QDir::separator() + "dump";//dump_local_crosses
    QString temp = app + QDir::separator() + "temp";//save_how
    QString mem = app + QDir::separator() + "mem";//saving steps

    file();
};

#endif // FILEDIR_H
