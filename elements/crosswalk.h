#ifndef CROSSWALK_H
#define CROSSWALK_H

#include <QObject>
#include <QGraphicsPathItem>

#include <QPen>
#include <QBrush>
#include <QDomDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMenu>
#include <QAction>

#include "custom/dep.h"

class grabCW : public QObject, public QGraphicsPathItem{
    Q_OBJECT

public: signals:
    void posChanged();//changed for repaint

public:
    grabCW(QGraphicsItem *parent);

private slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class crosswalk : public QObject, public QGraphicsPathItem{
    Q_OBJECT

    QVector<grabCW*> g;

public:
    int id = -1;
    QMenu *menu = nullptr;//menu for manage
    QDomDocument dom;

signals:
    void removeSelf(crosswalk *mrk);

public:
    crosswalk(){
        setZValue(107);

        setFlag(QGraphicsItem::ItemIsMovable);
        setAcceptHoverEvents(true);

        setBrush(Qt::darkGreen);
        setPen(QPen(Qt::black));

        menu = new QMenu;
        QAction *act = nullptr;
        act = new QAction("Удалить");
        connect(act,&QAction::triggered,this,&crosswalk::removeItem);
        menu->addAction(act);

        QPainterPath path;
        path.addRect(QRectF(-3,-3,6,6));
        setPath(path);

        for(int i=0; i<4; ++i){
            grabCW *gcw = new grabCW(this);
            connect(gcw,&grabCW::posChanged,this,&crosswalk::paintCrosswalk);
            g.push_back(gcw);
        }
    }
    ~crosswalk(){}

    void setVisiblePot(bool state){
        if(state){
            QPainterPath path;
            path.addRect(QRectF(-3,-3,6,6));
            setPath(path);
        }else{
            setPath(QPainterPath());
        }
    }

    void setPos(QPointF pos){
        g[0]->setPos(QPointF(-25,-50));
        g[1]->setPos(QPointF(25,-50));
        g[2]->setPos(QPointF(25,50));
        g[3]->setPos(QPointF(-25,50));
        QGraphicsPathItem::setPos(pos);
    }

    void setVisibleGarbs(bool state){
        for(int i=0; i<g.size(); ++i){
            g[i]->setVisible(state);
        }
    }

    QJsonObject json(){
        QJsonObject data;
        data["id"] = id;
        data["pos"] = (QString)dep::posToString(scenePos());
        QJsonArray ag;
        for(int i=0; i<g.size(); ++i){
            ag.push_back(dep::posToString(g[i]->pos()));
        }
        data["g"] = ag;
        return data;
    }
    void setjson(QJsonObject data){
        id = data["id"].toInt();
        QJsonArray ag = data["g"].toArray();
        for(int i=0; i<ag.size(); ++i){
            g[i]->setPos(dep::posFromString(ag[i].toString()));
        }
        QGraphicsPathItem::setPos(dep::posFromString(data["pos"].toString()));
    }

private slots:
    void removeItem(){
        emit removeSelf(this);
    }

private:
    void paintCrosswalk(){

    }

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event){
        setPen(QPen(Qt::red,2));
        QGraphicsPathItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
        setPen(QPen(Qt::black));
        QGraphicsPathItem::hoverLeaveEvent(event);
    }
};

#endif // CROSSWALK_H
