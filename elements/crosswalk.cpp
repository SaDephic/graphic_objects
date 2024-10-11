#include "crosswalk.h"

grabCW::grabCW(QGraphicsItem *parent){
    setParentItem(parent);
    //setVisible(false);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGray);
    setPen(QPen(Qt::black));

    QPainterPath path;
    path.addRect(QRectF(-3,-3,6,6));
    setPath(path);
}

void grabCW::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsItem::hoverEnterEvent(event);
}

void grabCW::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black));
    QGraphicsItem::hoverLeaveEvent(event);
}

void grabCW::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsItem::mousePressEvent(event);
}

void grabCW::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsItem::mouseMoveEvent(event);
}

void grabCW::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsItem::mouseReleaseEvent(event);
}
