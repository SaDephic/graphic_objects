#ifndef WPSCENE_H
#define WPSCENE_H

#include "common/factorydata.h"
extern factorydata *factory;

#include <QGraphicsScene>
#include <QBuffer>
#include <QGraphicsSceneMouseEvent>

class wpscene : public QGraphicsScene{
    Q_OBJECT

    QGraphicsPathItem *sow = nullptr;
    QVector<QString> lsw = {"С","СЗ","З","ЮЗ","Ю","ЮВ","В","СВ"};

    gpoint *center = nullptr;

    QPointF rcp;
    QPointF mpos;

public:
    linkpts *lpts = nullptr;
    QGraphicsPixmapItem *map = nullptr;

public:
    wpscene();

    void setMap(QByteArray arr);

    QPointF centerPos();
    void updateLinker();
    bool linkBusy();

    static QByteArray emptyMap(QSize size = QSize(450,450));
    QByteArray getMap();

    void createLink(gpoint *p);
    void linkWith(gpoint *p);
    void addAllItems();

public slots:
    void addNode();
    void addRTL();
    void addTTL();
    void addCW();
    void addCM();
    void addMK();
    void setCenter();

private slots:
    void splitLine(gline *line);
    void saveMiddlePos();
    void nullCenter();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};
#endif // WPSCENE_H
