#include "linkpts.h"

linkpts::linkpts(){
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);

    setBrush(Qt::NoBrush);
    setPen(QPen(Qt::green,2,Qt::DashLine));
}

bool linkpts::busy(){
    if(b)
        return true;
    return false;
}

void linkpts::null(){
    b = nullptr;
    e = nullptr;
    setPath(QPainterPath());
}

void linkpts::startLink(gpoint *p){
    b = p;
}

bool linkpts::doneLink(gpoint *p){
    if(p->pnp){
        if(p!=b){
            e = p;
            return true;
        }
    }
    return false;
}

gline *linkpts::getLink(){
    gline *l = new gline(b,e);
    null();
    return l;
}

void linkpts::updateLink(QPointF pos){
    QPainterPath p = QPainterPath();
    p.moveTo(b->scenePos());
    p.lineTo(pos);
    setPath(p);
}
