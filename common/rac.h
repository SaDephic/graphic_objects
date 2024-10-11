#ifndef RAC_H
#define RAC_H

#include "db/dbvalue.h"
#include <QVector>
#include <QMap>

#include "common/filedir.h"

#include "db/dbdcon.h"
extern dbdcon *envdb;

struct racobject{
    int region = 0;//id region
    int area = 0;//id area
    int subarea = 0;//id subarea
    int number = 0;//id number
    QString descRegion = QString();//string of region
    QString descArea = QString();//string of area
    QString descSubarea = QString();//string of subarea
    QString descObject = QString();//string of object
    QString ledit = QString();//string of last send on server
    QString text();//title
    QString path();//cat path to cross folder
    QString nameTitle();//check in console readed data
    bool operator == (const racobject& o);//equal
};

class rac : public QObject{
    Q_OBJECT

    //current work cross data
    int r=0,
        a=0,
        c=0;

public:
    QVector<racobject> cross;
    QString lastFolder = file().cross;

signals:
    void loaded();
    void currentSelected(QString title);
    void loadDataSelectedCross();

public:
    rac(){}
    void clearDataCross(){
        while(!cross.isEmpty()){
            cross.removeFirst();
        }
    }
    void setCurrentIDsCross(int reg, int are, int cro){
        r = reg;
        a = are;
        c = cro;
        emit currentSelected(QString::number(r) + "/" +
                             QString::number(a) + "/" +
                             QString::number(c) + " : " + getName());
    }
    QVector<int> getCurrentCross(){
        return {r,a,c};
    }

public slots:
    void setRegion(QVector<QMap<QString,dbvalue>> data){
        cross.clear();
        for(int i=0; i<data.size(); ++i){
            QMap<QString,dbvalue> c = data[i];
            racobject dcross;
            dcross.number = c["id"].value_int();
            dcross.descObject = c["describ"].value_string();
            dcross.subarea = c["subarea"].value_int();
            dcross.descSubarea = QString::number(dcross.subarea);
            dcross.region = c["region"].value_int();
            dcross.descRegion = c["nameregion"].value_string();
            dcross.area = c["area"].value_int();
            dcross.descArea = c["namearea"].value_string();
            dcross.ledit = c["ledit"].value_string();
            cross.push_back(dcross);
        }
        setCurrentIDsCross(r,a,c);
        emit loaded();
    }

private:
    QString getName(){
        for(int i=0; i<cross.size(); ++i){
            if(cross[i].region == r &&
                cross[i].area == a &&
                cross[i].number == c)
                return cross[i].descObject;
        }
        return "Не существует";
    }
};

#endif // RAC_H
