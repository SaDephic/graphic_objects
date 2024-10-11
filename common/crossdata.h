#ifndef CROSSDATA_H
#define CROSSDATA_H

#include "db/dbconnection.h"

#include <QThread>
#include <QMessageBox>

#include "common/rac.h"
extern rac *racoss;

class crossdata : public QObject{
    Q_OBJECT

public: signals:
    void loadData();

public:
    QMap<QString,dbvalue> single_rac;

    QThread *thread = nullptr;
    dbconnection *db = nullptr;

public:
    crossdata(){}

    void createNP(){
        thread = new QThread;
        db = new dbconnection();//object
    }
    void updateRegion(){
        connect(db,&dbconnection::answer,racoss,&rac::setRegion);
        db->setEnv(envdb);
        db->moveToThread(thread);//object in thread
        //delete instanses after executed
        connect(thread,&QThread::started, db,&dbconnection::askDataRegionCross);
        connect(db,&dbconnection::finished, thread,&QThread::quit);
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);
        connect(db,&dbconnection::finished,db,&dbconnection::deleteLater);
        thread->start();
    }
    void sendCurrentCross(QVector<int> rac, QMap<QString,dbvalue> data){
        db->setEnv(envdb);
        db->setDataSend(rac,data);
        connect(db,&dbconnection::statusBase,this,&crossdata::saveResult);
        db->moveToThread(thread);//object in thread
        //delete instanses after executed
        connect(thread,&QThread::started, db,&dbconnection::sendData);
        connect(db,&dbconnection::finished, thread,&QThread::quit);
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);
        connect(db,&dbconnection::finished,db,&dbconnection::deleteLater);
        thread->start();
    }
    void askCurrentCross(QVector<int> rac){
        db->setEnv(envdb);
        db->setAskCross(rac);
        connect(db,&dbconnection::answer,this,&crossdata::loadDataCross);
        db->moveToThread(thread);//object in thread
        //delete instanses after executed
        connect(thread,&QThread::started, db,&dbconnection::askDataCross);
        connect(db,&dbconnection::finished, thread,&QThread::quit);
        connect(thread,&QThread::finished,thread,&QThread::deleteLater);
        connect(db,&dbconnection::finished,db,&dbconnection::deleteLater);
        thread->start();
    }

private slots:
    void saveResult(status v){
        QMessageBox msg;
        msg.setWindowTitle("Сохранение");
        msg.setWindowModality(Qt::ApplicationModal);
        if(v.v == 1){
            msg.setIcon(QMessageBox::Information);
            msg.setText("Перекресток был успешно отправлен!");
        }else{
            msg.setIcon(QMessageBox::Critical);
            msg.setText(v.err);
        }
        msg.exec();
    }
    void loadDataCross(QVector<QMap<QString,dbvalue>> res){
        if(!res.isEmpty()){
            single_rac = res.first();
            emit loadData();
        }
    }
};

#endif // CROSSDATA_H
