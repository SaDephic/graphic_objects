#ifndef GPOINT_H
#define GPOINT_H

#include <QJsonObject>

#include <QMenu>
#include <QAction>

#include <QPen>
#include <QBrush>

#include <QObject>
#include <QGraphicsEllipseItem>

class gpoint : public QObject, public QGraphicsEllipseItem{
    Q_OBJECT

public: signals:
    void posChanged();

public: signals:
    void linkWith(gpoint *point);
    void removeSelf(gpoint *point);

public:
    int id = 0;
    QMenu *menu = nullptr;
    bool pnp = false;
    bool middle = false;

public:
    gpoint(QPointF pos = QPointF(), QGraphicsItem *parent = nullptr, bool mdm = true);
    gpoint(bool middle = false, QPointF pos = QPointF());
    ~gpoint();

    void setPos(QPointF pos);

    QJsonObject json();
    void setjson(QJsonObject data);

private slots:
    void linkWithItem();
    void removeItem();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // GPOINT_H
