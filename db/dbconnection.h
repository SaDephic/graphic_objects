#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include "dbdcon.h"
#include "dbvalue.h"

#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlResult>
#include <QSqlRecord>

#include "auth/stateauth.h"
extern stateauth *aut;

struct status{
    status(int val = -1, QString error = QString());
    int v = -1;
    QString err = QString();
};

class dbconnection : public QObject{
    Q_OBJECT

    QVector<int> srac;
    QMap<QString,dbvalue> sdata;

public:
    dbdcon *env;

signals:
    void statusBase(status v);
    void finished();//for unlinked thread
    void answer(QVector<QMap<QString,dbvalue>> res);//ask data massive
    void errorConnection(QString error);//message error execution
    void currentStage(QString info);

public:
    dbconnection();
    ~dbconnection();

    void setEnv(dbdcon *enviroments);
    void setDataSend(QVector<int> rac, QMap<QString,dbvalue> data);
    void setAskCross(QVector<int> rac);

    void disconnectBase();

private:
    status checkLink();
    QVector<QMap<QString,dbvalue>> getRecordData();
    status send();
    QVector<QMap<QString,dbvalue>> getSingleRecordData();


public slots:
    void check();
    void askDataRegionCross();
    void sendData();
    void askDataCross();
};

#endif // DBCONNECTION_H
