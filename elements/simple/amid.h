#ifndef AMID_H
#define AMID_H

#include <QObject>

#include "elements/simple/gpoint.h"
#include "elements/simple/line/gline.h"

class amid : public QObject, public QGraphicsPathItem{
    Q_OBJECT

public:
    gpoint *m;
    QVector<gline*> sync;

public:
    amid(gpoint *gm, QVector<gline*> gsync){
        setPen(QPen(Qt::red,2));
        setFlag(QGraphicsItem::ItemIsFocusable,false);
        setFlag(QGraphicsItem::ItemIsSelectable,false);
        // setZValue(101);//road
        setZValue(100);//tramway

        //qDebug() << "mid " << m->id;// multy asks from elements gline
        m = gm;
        sync = gsync;
        paintCurrentConfig();
    }
    ~amid(){}
    void update_mid(QVector<gline*> gsync){
        //qDebug() << "update " << gsync.size() << ":" << sync.size();// multy asks from elements gline
        sync = gsync;
        paintCurrentConfig();
    }
    bool containsLine(gline *l){
        for(int i=0; i<sync.size(); ++i)
            if(sync[i]->id == l->id)
                return true;
        return false;
    }
    void paintCurrentConfig(){
        QVector<QPointF> pt;

        //link all area by radiant
        for(int i=0; i<sync.size(); ++i){
            pt.append(sync[i]->getLRPT(m));
        }

        //sort by radiance
        QMap<double,QPointF> lps;
        for(int i=0; i<pt.size(); ++i){
            double r = geom::getAngleRad(m->scenePos(),pt[i]);
            lps.insert(r,pt[i]);
        }
        pt = lps.values();

        if(pt.isEmpty())
            return;

        QPainterPath p = QPainterPath();
        p.moveTo(pt.first());
        for(int i=1; i<pt.size(); ++i){
            p.lineTo(pt[i]);
        }
        p.lineTo(pt.first());
        setPath(p);
    }
};

#endif // AMID_H
