#ifndef LENSLAMP_H
#define LENSLAMP_H

#include <QPen>
#include <QBrush>
#include <QObject>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QHoverEvent>

#include <QMenu>
#include <QAction>

#include <QJsonObject>
#include <QJsonArray>

class LensLamp : public QObject, public QGraphicsPathItem{
    Q_OBJECT
    int index;

public: signals:
    void changeState(int id);
    void linkLight(int id);

public:
    bool link = false;
    bool selected = false;

public:
    LensLamp(QGraphicsItem *parent, int id = -1);
    void setSelected(bool select);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

class addGrabLamp: public QObject, public QGraphicsPathItem{
    Q_OBJECT

public: signals:
    void posChanged();//changed for repaint all light

public:
    addGrabLamp(QGraphicsItem *parent);

private slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};


class AddLamp : public QObject, public QGraphicsPathItem{
    Q_OBJECT
    QMenu *menu = nullptr;//menu for manage

public: signals:
    void deleteSelf(AddLamp *item);
    void linkLight(int id);
    void updateAdditional();

public:
    bool link = false;
    bool selected = false;

    int index;

    addGrabLamp *gl = nullptr;
    QVector<addGrabLamp*> ll;

public:
    AddLamp(QGraphicsItem *parent, int id = -1);
    ~AddLamp();

    void setSelected(bool select);
    QMenu *actMenu();
    QVector<QPointF> blockline();

    void setVisibleGrabs(bool state);
    void setDefaultPos(QPointF pos);

    QJsonObject json();
    void setjson(QJsonObject data);

private slots:
    void updateLamp();
    void deleteItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);    
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // LENSLAMP_H
