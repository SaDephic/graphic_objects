#include "gpoint.h"
#include "custom/dep.h"

gpoint::gpoint(QPointF pos, QGraphicsItem *parent, bool mdm){
    setZValue(200);

    setParentItem(parent);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setPen(QPen(Qt::black));
    setRect(QRectF(-3,-3,6,6));

    setPos(pos);

    menu = new QMenu();
    QAction *act = nullptr;

    pnp = mdm;
    if(pnp){
        act = new QAction("Соединить с ...");
        connect(act,&QAction::triggered,this,&gpoint::linkWithItem);
        menu->addAction(act);

        setBrush(Qt::green);
    }else{
        setBrush(Qt::blue);
    }

    act = new QAction("Удалить");
    connect(act,&QAction::triggered,this,&gpoint::removeItem);
    menu->addAction(act);
}

gpoint::gpoint(bool middle, QPointF pos){
    this->middle = middle;
    setFlag(QGraphicsPathItem::ItemIsMovable);
    setBrush(Qt::yellow);
    setZValue(999);
    setVisible(false);
    setRect(QRectF(-4,-4,8,8));
    setPos(pos);
}

gpoint::~gpoint(){}

void gpoint::setPos(QPointF pos){
    QGraphicsEllipseItem::setPos(pos);
    posChanged();
}

QJsonObject gpoint::json(){
    QJsonObject data;
    data["id"] = (int)id;
    data["pt"] = (QString)dep::posToString(pos());
    return data;
}

void gpoint::setjson(QJsonObject data){
    id = data["id"].toInt();
    setPos(dep::posFromString(data["pt"].toString()));
}

void gpoint::linkWithItem(){
    emit linkWith(this);
}

void gpoint::removeItem(){
    emit removeSelf(this);
}

void gpoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void gpoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsEllipseItem::mouseReleaseEvent(event);
}

void gpoint::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setToolTip(QString::number(id) + " :" + QString::number(scenePos().x()) + "-" + QString::number(scenePos().y()));
    setPen(QPen(Qt::red,2));
    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void gpoint::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black));
    QGraphicsEllipseItem::hoverLeaveEvent(event);
}
