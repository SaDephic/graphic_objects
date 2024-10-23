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

    bool tramway = false;//!!!

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

    //area
    QPointF bl;//b
    QPointF br;
    QPointF el;//e
    QPointF er;

    //road bords
    QPointF abl;//b
    QPointF abr;
    QPointF ael;//e
    QPointF aer;

public: signals:
    void updateLine();
    void splitLine(gline *line);
    void removeSelf(gline *line);
    void editSelf(gline *line);
    void updateMid();

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

    QPointF getSUPT(gpoint *pt);
    QVector<QPointF> getLRPT(gpoint *pt);
    QVector<QPointF> getBLRPT(gpoint *pt);

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

    void paintRoad();//f
    void paintSuline();//line m/u
    void paintMiddle();//line mid
    void paintBords();//white bord
    void paintPlace();//area pls

    void paintTramway();//f
    void paintRails();//black rails
    void paintSurface();//area pls

    void freshArea();//free all space
    void setArea(QVector<QPointF> l, QVector<QPointF> r);
    void setRoadBArea(QVector<QPointF> l, QVector<QPointF> r);

private slots:
    //from parentline
    void paintAll();
    void paintLine();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // GLINE_H
