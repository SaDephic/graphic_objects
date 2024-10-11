#ifndef DEP_H
#define DEP_H

#include <QString>
#include <QPointF>

#include <QJsonObject>
#include <QJsonArray>

class dep{
public:
    static QString posToString(QPointF p){
        return QString::number(p.x()) + ":" + QString::number(p.y());
    }
    static QPointF posFromString(QString sp){
        auto a = sp.split(":");
        if(a.size() < 2 || a.size() > 2)
            return QPointF();
        return QPointF(a[0].toDouble(),a[1].toDouble());
    }
    static QVector<int> fromJsonValInt(QJsonArray a){
        QVector<int> r;
        for(int i=0; i<a.size(); ++i){
            r.push_back(a[i].toInt());
        }
        return r;
    }
    static QVector<QString> fromJsonValString(QJsonArray a){
        QVector<QString> r;
        for(int i=0; i<a.size(); ++i){
            r.push_back(a[i].toString());
        }
        return r;
    }
    static QVector<int> fromVecString(QVector<QString> val){
        QVector<int> r;
        for(int i=0; i<val.size(); ++i){
            r.push_back(val[i].toInt());
        }
        return r;
    }
};

#endif // DEP_H
