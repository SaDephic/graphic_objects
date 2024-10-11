#include "filedir.h"

file::file(){
    if(!QDir(apps).exists()){
        QDir().mkdir(apps);
    }
    if(!QDir(app).exists()){
        QDir().mkdir(app);
    }
    if(!QDir(soft).exists()){
        QDir().mkdir(soft);
    }
    if(!QDir(cross).exists()){
        QDir().mkdir(cross);
    }
    if(!QDir(dump).exists()){
        QDir().mkdir(dump);
    }
    if(!QDir(temp).exists()){
        QDir().mkdir(temp);
    }
    if(!QDir(mem).exists()){
        QDir().mkdir(temp);
    }
    if(!QDir(tempsys).exists()){
        QDir().mkdir(tempsys);
    }
}
