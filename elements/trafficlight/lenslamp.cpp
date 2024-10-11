#include "lenslamp.h"
#include "custom/dep.h"

LensLamp::LensLamp(QGraphicsItem *parent, int id){
    index = id;
    setParentItem(parent);
    setVisible(false);

    setFlag(QGraphicsItem::ItemIsMovable,false);
    setAcceptHoverEvents(true);

    setBrush(Qt::magenta);
    setPen(QPen(Qt::black));

    QPainterPath path;
    path.addEllipse(QRectF(-3,-3,6,6));
    setPath(path);
}

void LensLamp::setSelected(bool select){
    selected = select;
    if(select)
        setPen(QPen(Qt::blue,2));
    else
        setPen(QPen(Qt::black));
}

void LensLamp::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(link){
        setSelected(true);
        emit linkLight(index);
    }else{
        emit changeState(index);
    }
    QGraphicsPathItem::mousePressEvent(event);
}

void LensLamp::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void LensLamp::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(selected)
        setPen(QPen(Qt::blue,2));
    else
        setPen(QPen(Qt::black));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

addGrabLamp::addGrabLamp(QGraphicsItem *parent){
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

void addGrabLamp::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void addGrabLamp::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black,1));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void addGrabLamp::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mousePressEvent(event);
}

void addGrabLamp::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseMoveEvent(event);
}

void addGrabLamp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseReleaseEvent(event);
}

AddLamp::AddLamp(QGraphicsItem *parent, int id){
    index = id;
    setParentItem(parent);
    setVisible(false);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    setBrush(Qt::magenta);
    setPen(QPen(Qt::black));

    QPainterPath path;
    path.addEllipse(QRectF(-3,-3,6,6));
    setPath(path);

    gl = new addGrabLamp(this);
    gl->setPos(QPointF(0,-50));
    connect(gl,&addGrabLamp::posChanged,this,&AddLamp::updateLamp);
    for(int i=0; i<3; ++i){
        ll.push_back(new addGrabLamp(parent));
        connect(ll[i],&addGrabLamp::posChanged,this,&AddLamp::updateLamp);
    }

    menu = new QMenu;
    QAction *act = nullptr;
    act = new QAction("Удалить");
    connect(act,&QAction::triggered,this,&AddLamp::deleteItem);
    menu->addAction(act);
}

AddLamp::~AddLamp(){
    while(!ll.isEmpty()){
        delete ll.takeFirst();
    }
    delete gl;
}

void AddLamp::setSelected(bool select){
    selected = select;
    if(select)
        setPen(QPen(Qt::blue,2));
    else
        setPen(QPen(Qt::black));
}

QMenu *AddLamp::actMenu(){
    return menu;
}

QVector<QPointF> AddLamp::blockline(){
    QVector<QPointF> bl;
    for(int i=0; i<ll.size(); ++i)
        bl.push_front(ll[i]->pos());
    bl.push_back(pos());
    return bl;
}

void AddLamp::setVisibleGrabs(bool state){
    setVisible(state);
    for(int i=0; i<ll.size(); ++i)
        ll[i]->setVisible(state);
    gl->setVisible(state);
}

void AddLamp::setDefaultPos(QPointF pos){
    this->setPos(pos);
    QPointF n0 = (QPointF()+pos)/2;
    QPointF n1 = (n0+pos)/2;
    QPointF n2 = (n0+QPointF())/2;
    ll[0]->setPos(n1);
    ll[1]->setPos(n0);
    ll[2]->setPos(n2);
}

QJsonObject AddLamp::json(){
    QJsonObject data;
    data["pos"] = (QString)dep::posToString(pos());
    QJsonArray pts;
    for(int i=0; i<ll.size(); ++i){
        pts.push_back((QString)dep::posToString(ll[i]->pos()));
    }
    data["pts"] = pts;
    data["gl"] = (QString)dep::posToString(gl->pos());
    return data;
}

void AddLamp::setjson(QJsonObject data){
    setPos(dep::posFromString(data["pos"].toString()));
    QJsonArray pts = data["pts"].toArray();
    for(int i=0; i<pts.size(); ++i){
        ll[i]->setPos(dep::posFromString(pts[i].toString()));
    }
    gl->setPos(dep::posFromString(data["gl"].toString()));
}

void AddLamp::updateLamp(){
    emit updateAdditional();
}

void AddLamp::deleteItem(){
    emit deleteSelf(this);
}

void AddLamp::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(link){
        emit linkLight(index+100);
        setSelected(true);
    }
    emit updateAdditional();
    QGraphicsPathItem::mousePressEvent(event);
}

void AddLamp::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit updateAdditional();
    QGraphicsPathItem::mouseMoveEvent(event);
}

void AddLamp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit updateAdditional();
    QGraphicsPathItem::mouseReleaseEvent(event);
}

void AddLamp::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void AddLamp::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    if(selected)
        setPen(QPen(Qt::blue,2));
    else
        setPen(QPen(Qt::black));
    QGraphicsPathItem::hoverLeaveEvent(event);
}
