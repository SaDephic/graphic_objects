#include "dbconnection.h"
#include "common/querys.h"

status::status(int val, QString error){
    v = val;
    err = error;
}

dbconnection::dbconnection(){}
dbconnection::~dbconnection(){
    disconnectBase();
}

void dbconnection::setEnv(dbdcon *enviroments){
    env = enviroments;
}

void dbconnection::setDataSend(QVector<int> rac, QMap<QString, dbvalue> data){
    srac = rac;
    sdata = data;
}

void dbconnection::setAskCross(QVector<int> rac){
    srac = rac;
}

void dbconnection::disconnectBase(){
    if(QSqlDatabase::contains(env->name)){
        {
            QSqlDatabase::database(env->name).close();
        }
        QSqlDatabase::removeDatabase(env->name);
    }
}

status dbconnection::checkLink(){
    status v;
    {
        disconnectBase();
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL",env->name);
        db.setHostName(env->ip);
        db.setPort(env->port);
        db.setDatabaseName(env->databasename);
        bool o = db.open(env->username,env->userpassword);
        if(o){
            if(db.isOpen()){
                v = status(1);
            }else{
                v = status(0,db.lastError().text());
            }
        }else{
            v = status(0,db.lastError().text());
        }
    }
    disconnectBase();
    return v;
}

QVector<QMap<QString, dbvalue>> dbconnection::getRecordData(){
    QVector<QMap<QString,dbvalue>> data;
    {
        disconnectBase();
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL",env->name);
        db.setHostName(env->ip);
        db.setPort(env->port);
        db.setDatabaseName(env->databasename);
        if(db.open(env->username,env->userpassword)){
            if(db.isOpen()){
                QSqlQuery qr(db);
                qr.exec(querys().a_region);
                while(qr.next()){
                    QMap<QString,dbvalue> recmem;
                    for(int i=0; i<qr.record().count(); ++i){
                        recmem.insert(qr.record().fieldName(i),{qr.record().value(i)});
                    }

                    //check awaible
                    if(aut->region != -1){
                        if(recmem["region"].value_int() != aut->region){
                            continue;
                        }
                    }
                    if(!aut->areas.contains(-1)){
                        if(!aut->areas.contains(recmem["area"].value_int())){
                            continue;
                        }
                    }

                    emit currentStage(qr.record().value("region").toString() + "/" + qr.record().value("area").toString());

                    QSqlQuery qc(db);
                    qc.exec(querys().a_crosses.arg(QString::number(recmem["region"].value_int()),
                                                   QString::number(recmem["area"].value_int())));

                    QMap<QString,dbvalue> mem;
                    while(qc.next()){
                        for(int i=0; i<qc.record().count(); ++i){
                            mem.insert(qc.record().fieldName(i),{qc.record().value(i)});
                        }

                        mem.insert("nameregion",{qr.record().value("nameregion")});
                        mem.insert("namearea",{qr.record().value("namearea")});
                        data.push_back(mem);
                    }
                }
            }else{
                emit errorConnection(db.lastError().text());
            }
        }else{
            emit errorConnection(db.lastError().text());
        }
    }
    disconnectBase();
    return data;
}

status dbconnection::send(){
    status v;
    {
        disconnectBase();
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL",env->name);
        db.setHostName(env->ip);
        db.setPort(env->port);
        db.setDatabaseName(env->databasename);
        bool o = db.open(env->username,env->userpassword);
        if(o){
            if(db.isOpen()){
                v = status(1);

                QSqlQuery query(db);
                query.prepare(querys().send_cross.arg(srac[0]).arg(srac[1]).arg(srac[2]));
                query.bindValue(":bottom",sdata[":bottom"].value_byte());
                query.bindValue(":picture",sdata[":picture"].value_byte());
                query.bindValue(":extend",sdata[":extend"].value_string());
                query.bindValue(":state",sdata[":state"].value_string());
                query.exec();

                if(!query.lastError().text().isEmpty())
                    v = status(0,query.lastError().text());
            }else{
                v = status(0,db.lastError().text());
            }
        }else{
            v = status(0,db.lastError().text());
        }
    }
    disconnectBase();
    return v;
}

QVector<QMap<QString, dbvalue> > dbconnection::getSingleRecordData(){
    QVector<QMap<QString,dbvalue>> data;
    {
        disconnectBase();
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL",env->name);
        db.setHostName(env->ip);
        db.setPort(env->port);
        db.setDatabaseName(env->databasename);
        bool o = db.open(env->username,env->userpassword);
        if(o){
            if(db.isOpen()){
                QSqlQuery qr(db);
                qr.exec(querys().get_cross.arg(srac[0]).arg(srac[1]).arg(srac[2]));
                while(qr.next()){
                    QMap<QString,dbvalue> recmem;
                    for(int i=0; i<qr.record().count(); ++i){
                        recmem.insert(qr.record().fieldName(i),{qr.record().value(i)});
                    }
                    data.push_back(recmem);
                }
            }else{
                emit errorConnection(db.lastError().text());
            }
        }else{
            emit errorConnection(db.lastError().text());
        }
    }
    disconnectBase();
    return data;
}

void dbconnection::check(){
    emit statusBase(checkLink());
    emit finished();
}

void dbconnection::askDataRegionCross(){
    emit answer(getRecordData());
    emit finished();
}

void dbconnection::sendData(){
    emit statusBase(send());
    emit finished();
}

void dbconnection::askDataCross(){
    emit answer(getSingleRecordData());
    emit finished();
}
