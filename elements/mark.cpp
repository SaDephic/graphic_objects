#include "mark.h"
#include "custom/geom.h"
#include "custom/dep.h"

grabMark::grabMark(QGraphicsItem *parent){
    setParentItem(parent);
    setVisible(false);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGray);
    setPen(QPen(Qt::black));

    QPainterPath path;
    path.addRect(QRectF(-3,-3,6,6));
    setPath(path);
}

void grabMark::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void grabMark::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black,2));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void grabMark::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mousePressEvent(event);
}

void grabMark::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseMoveEvent(event);
}

void grabMark::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseReleaseEvent(event);
}

mark::mark(){
    setZValue(108);

    gl = new grabMark(this);
    connect(gl,&grabMark::posChanged,this,&mark::paintView);

    gtext = new QGraphicsPathItem(this);
    gtext->setFlag(QGraphicsItem::ItemStacksBehindParent);
    gtext->setFlag(QGraphicsItem::ItemIsFocusable,false);
    gtext->setFlag(QGraphicsItem::ItemIsSelectable,false);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGreen);
    setPen(QPen(Qt::black));

    QPainterPath path;
    path.addEllipse(QRectF(-4,-4,8,8));
    setPath(path);

    menu = new QMenu;
    QAction *act = nullptr;
    act = new QAction("Редактировать");
    connect(act,&QAction::triggered,this,&mark::editItem);
    menu->addAction(act);
    menu->addSeparator();
    act = new QAction("Удалить");
    connect(act,&QAction::triggered,this,&mark::removeItem);
    menu->addAction(act);

}

void mark::setPos(QPointF pos){
    gl->setPos(QPointF(60,0));//default position grab
    paintView();
    QGraphicsPathItem::setPos(pos);
}

void mark::setVisibleState(bool state){
    enabled = state;
    gl->setVisible(state);
    QPainterPath path = QPainterPath();
    if(state){
        path.addEllipse(QRectF(-4,-4,8,8));
        path.moveTo(QPointF());
        path.lineTo(gl->pos());
    }else{
        path.addEllipse(QRectF(-4,-4,8,8));
    }
    setPath(path);
}

QJsonObject mark::json(){
    QJsonObject data;
    data["id"] = (int)id;
    data["pos"] = (QString)dep::posToString(scenePos());
    data["gl"] = (QString)dep::posToString(gl->pos());
    data["color"] = (QString)color.name();
    data["text"] = (QString)text;
    data["size"] = (int)size;
    data["style"] = (QString)style;
    return data;
}

void mark::setjson(QJsonObject data){
    id = data["id"].toInt();
    QGraphicsPathItem::setPos(dep::posFromString(data["pos"].toString()));
    gl->setPos(dep::posFromString(data["gl"].toString()));
    color = QColor(data["color"].toString());
    text = data["text"].toString();
    size = data["size"].toInt();
    style = data["style"].toString();
    paintView();
}

void mark::setchanges(QJsonObject data){
    id = data["id"].toInt();
    color = QColor(data["color"].toString());
    text = data["text"].toString();
    size = data["size"].toInt();
    style = data["style"].toString();
    paintView();
}

void mark::paintView(){
    dom.clear();
    //sets for text color
    gtext->setBrush(color);
    gtext->setPen(QPen(color));
    //view in soft
    QPainterPath p = QPainterPath();
    p.addText(QPointF(),QFont(style,size),text);
    gtext->setRotation(geom::getAngle(QPointF(),gl->pos()));
    gtext->setPath(p);
    //element of item
    if(enabled){
        QPainterPath path;
        path.addEllipse(QRectF(-4,-4,8,8));
        path.moveTo(QPointF());
        path.lineTo(gl->pos());
        setPath(path);
    }
    //view on svg
    QDomElement g = dom.createElement("g");
    g.setAttribute("id",id);
    g.setAttribute("transform","translate(" +
                   QString::number(scenePos().x()) + " " +
                   QString::number(scenePos().y()) + ")");
    QDomElement label = dom.createElement("text");
    label.setAttribute("x",gtext->pos().x());
    label.setAttribute("y",gtext->pos().y());
    label.setAttribute("style","font-famyly: " + style);
    label.setAttribute("font-size",QString::number(size));
    label.setAttribute("fill",color.name());
    label.setAttribute("transform","rotate(" + QString::number(geom::getAngle(QPointF(),gl->pos()))
                       + " " + QVariant(gtext->pos().x()).toString()
                       + " " + QVariant(gtext->pos().y()).toString() + ")");
    QDomText t = dom.createTextNode(text);
    label.appendChild(t);
    g.appendChild(label);
    dom.appendChild(g);
}

void mark::editItem(){
    setVisibleState(true);
    emit editSelf(this);
}

void mark::removeItem(){
    emit removeSelf(this);
}

void mark::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void mark::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void mark::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
}

void mark::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    paintView();
    QGraphicsPathItem::mouseReleaseEvent(event);
}
