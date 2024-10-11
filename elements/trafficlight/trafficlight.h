#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "lenslamp.h"

#include <QObject>
#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#include <QDomDocument>
#include <QDomElement>

#include <QJsonObject>
#include <QJsonArray>

#include <QMenu>

class grabLamp: public QObject, public QGraphicsPathItem{
    Q_OBJECT

public: signals:
    void posChanged();//changed for repaint all light

public:
    grabLamp(QGraphicsItem *parent);

private slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

//lens/lamp state
struct section{
    bool enabled = false;
    bool visbleState = false;
    bool RL = false;
    section();
    void rev();
};

class trafficlight: public QObject, public QGraphicsPathItem{
    Q_OBJECT

    QAction *addsect = nullptr;

    bool enabled = false;//enable for edit
    QGraphicsPathItem *skelet = nullptr;//basic structure
    QGraphicsPathItem *selectView = nullptr;//graphics view

    int size = 25;//trafficlight size

    QVector<LensLamp*> ll;//lenslamps [16]
    QVector<section> llst;//state for lenses[16]
    QVector<grabLamp*> gl;//grab for direction lamps [4]
    QVector<AddLamp*> almp;//additional lenses[XXX]

    //animate
    QMap<QString,QPainterPath> lensesitem;
    QPainterPath stoklens;

public:
    int id = -1;//unique index
    int t;
    QMenu *menu = nullptr;//context menu for manage
    QDomDocument dom;//carcass item

signals:
    void removeSelf(trafficlight *it);//delete item from cross
    void editSelf(trafficlight *it);//send item to editor
    void linkLight(QString light);//link to cross change

public:
    trafficlight(int typelight = 0);
    ~trafficlight();
    void setPos(QPointF pos);//set global position light
    void setVisibleState(bool state);//visible manage elements
    QJsonObject json();
    void setjson(QJsonObject data);
    void setchanges(QJsonObject data);
    //mode link for connect to prew directions
    void setLinkState(bool state);
    void setVisisbleActiveLenses(bool state);
    //selected items
    void setSelected(QVector<QString> llns);
    void dropSelected();
    //selected graphics
    void setVisibleSelected(QVector<QString> llns);
    void dropVisibleSelected();
    //for animate view
    QPainterPath getStock();
    QMap<QString,QPainterPath> getLensesAnimate();

private:
    void setDefaultPosition();//default position

private slots:
    void changeState(int id);
    void setLLPosition();//set postion lens/lamp and repaint skelet
    //slot add new lens
    AddLamp *addLens();//slot add additional lens
    void editItem();//slot edit self
    void removeItem();//slot delete self
    //traslations
    void controlLight(int lid);//translate signal from lens/lamp
    //remove item
    void deleteAddLamp(AddLamp *lmp);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TRAFFICLIGHT_H
