#ifndef GLINE_H
#define GLINE_H

#include "../gpoint.h"

#include "custom/geom.h"

#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsPathItem>
#include <QGraphicsScene>

#include "custom/gin_index.h"

class gline : public QObject, public QGraphicsPathItem{
    Q_OBJECT

public:
    QGraphicsPathItem *place = nullptr;
    QGraphicsPathItem *middle = nullptr;
    QGraphicsPathItem *sulines = nullptr;
    QGraphicsPathItem *area = nullptr;

private:
    gin_index idsl;

    gpoint *b = nullptr;
    gpoint *e = nullptr;
    gline *pline = nullptr;

    QVector<gpoint*> subpoint;//only for parentline
    QVector<gline*> subline;//only for parentline

    int in = 1;
    int out = 0;
    int sizeLen = 20;
    int sizeMidLen = 5;
    bool chin = false;
    bool chout = false;

    bool tramway = false;//!!!

public: signals:
    void updateLine();
    void splitLine(gline *line);
    void removeSelf(gline *line);
    void editSelf(gline *line);

public:
    bool parentline = false;
    int id = 0;
    QMenu *menu = nullptr;

public:
    gline(QPointF first, QPointF second, bool parentline = false, gline *gpline = nullptr);
    gline(gpoint *first, gpoint* second, bool parentline = false, gline *gpline = nullptr);
    ~gline();

    void construct();

    bool exist(gpoint *p);
    gpoint *getE(gpoint *p);
    gpoint *getB(gpoint *p);

    QJsonObject json();
    void setjson(QJsonObject data);
    void setchanges(QJsonObject data);

    bool notEmpty();

public:
    void split(QPointF pos);
    void repair(gpoint *p);

private slots:
    void splitItem();
    void repairItem(gpoint *p);
    void setSubOrder();
    void editItem();

private:
    void removeItem();
    gline *getParentLine();
    gpoint *getSubPoint(int id);

    QJsonObject subjson();
    QJsonArray lines();
    QJsonArray points();

    QVector<QPointF> getMainLine();

    void paintRoad();
    void paintSuline();
    void paintMiddle();
    void paintBords();
    void paintPlace();

    void paintTramway();
    void paintRails();
    void paintSurfase(){
        QPainterPath p = QPainterPath();
        if(in==0 && out == 0){
            area->setPath(p);
            return;
        }
        QVector<QPointF> mline = getMainLine();
        int count = in+out;
        if(count>0){
            if(in==0 || out==0){
                if(count&1){
                    QVector<QPointF> vec = geom::getBezie(geom::getParralelLine(mline,sizeLen/2+sizeMidLen*count/2+sizeLen*count/2,true));
                    std::reverse(vec.begin(),vec.end());
                    vec.append(geom::getBezie(geom::getParralelLine(mline,sizeLen/2+sizeMidLen*count/2+sizeLen*count/2,false)));
                    p.addPath(ptsConv::pts2Path(vec,false));
                }else{
                    QVector<QPointF> vec = geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeMidLen*count/2+sizeLen*count/2,true));
                    std::reverse(vec.begin(),vec.end());
                    vec.append(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeMidLen*count/2+sizeLen*count/2,false)));
                    p.addPath(ptsConv::pts2Path(vec,false));
                }
            }else{
                QVector<QPointF> vec = geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeMidLen*in+sizeLen*in,true));
                std::reverse(vec.begin(),vec.end());
                vec.append(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeMidLen*out+sizeLen*out,false)));
                p.addPath(ptsConv::pts2Path(vec,false));
            }
        }
        area->setPath(p);
    }
    void freshArea(){
        place->setPath(QPainterPath());
        middle->setPath(QPainterPath());
        sulines->setPath(QPainterPath());
        area->setPath(QPainterPath());
    }

private slots:
    //from parentline
    void paintAll();
    void paintLine();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // GLINE_H
