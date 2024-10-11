#include "cam.h"
#include "custom/geom.h"
#include "custom/dep.h"

grabCam::grabCam(QGraphicsItem *parent, int t){
    setZValue(109);

    setParentItem(parent);
    setVisible(false);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGray);
    setPen(QPen(Qt::black));

    QPainterPath path;
    if(t == 0)
        path.addRect(QRectF(-3,-3,6,6));
    if(t == 1)
        path.addEllipse(QRectF(-3,-3,6,6));
    setPath(path);
}

void grabCam::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void grabCam::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black,2));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void grabCam::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mousePressEvent(event);
}

void grabCam::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseMoveEvent(event);
}

void grabCam::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseReleaseEvent(event);
}

cam::cam(){
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGreen);
    setPen(QPen(Qt::black));

    direct = new grabCam(this);
    connect(direct,&grabCam::posChanged,this,&cam::paintView);
    for(int i=0; i<4; ++i){
        area.push_back(new grabCam(direct,1));
        connect(area[i],&grabCam::posChanged,this,&cam::paintView);
    }

    garea = new QGraphicsPathItem(this);
    garea->setFlag(QGraphicsItem::ItemStacksBehindParent);
    garea->setFlag(QGraphicsItem::ItemIsFocusable,false);
    garea->setFlag(QGraphicsItem::ItemIsSelectable,false);
    garea->setPen(QPen(Qt::black));
    garea->setBrush(Qt::NoBrush);

    gtext = new QGraphicsPathItem(this);
    gtext->setFlag(QGraphicsPathItem::ItemIsMovable,false);
    gtext->setPen(QPen(Qt::black));
    gtext->setBrush(Qt::black);

    QPainterPath path;
    path.addEllipse(QRectF(-4,-4,8,8));
    setPath(path);

    menu = new QMenu;
    QAction *act = nullptr;
    act = new QAction("Редактировать");
    connect(act,&QAction::triggered,this,&cam::editItem);
    menu->addAction(act);
    menu->addSeparator();
    act = new QAction("Удалить");
    connect(act,&QAction::triggered,this,&cam::removeItem);
    menu->addAction(act);
}

cam::~cam(){}

void cam::setPos(QPointF pos){
    //default pos
    direct->setPos(QPointF(55,-55));
    area[0]->setPos(QPointF(-25,-25));
    area[1]->setPos(QPointF(25,-25));
    area[2]->setPos(QPointF(25,25));
    area[3]->setPos(QPointF(-25,25));
    gtext->setPos(QPointF());
    //after pos
    paintView();
    QGraphicsPathItem::setPos(pos);
}

void cam::setVisibleState(bool state){
    enabled = state;
    gtext->setFlag(QGraphicsPathItem::ItemIsMovable,state);
    direct->setVisible(state);
    for(int i=0; i<area.size(); ++i)
        area[i]->setVisible(state);

    paintView();
}

QJsonObject cam::json(){
    QJsonObject data;
    data["camsize"] = (int)camsize;
    data["id"] = (int)id;
    data["pos"] = (QString)dep::posToString(scenePos());
    data["name"] = (QString)text;
    data["color"] = (QString)color.name();
    data["textsize"] = (int)textsize;
    data["url"] = (QString)url;
    data["stop"] = (QString)stop;
    data["up"] = (QString)up;
    data["down"] = (QString)down;
    data["left"] = (QString)left;
    data["right"] = (QString)right;
    data["txtpos"] = (QString)dep::posToString(gtext->pos());
    data["direct"] = (QString)dep::posToString(direct->pos());
    QJsonArray pst;
    for(int i=0; i<area.size(); ++ i)
        pst.push_back(dep::posToString(area[i]->pos()));
    data["area"] = pst;
    return data;
}

void cam::setjson(QJsonObject data){
    camsize = data["camsize"].toInt();
    id = data["id"].toInt();
    QGraphicsPathItem::setPos(dep::posFromString(data["pos"].toString()));
    text = data["name"].toString();
    color = QColor(data["color"].toString());
    textsize = data["textsize"].toInt();
    url = data["url"].toString();
    stop = data["stop"].toString();
    up = data["up"].toString();
    down = data["down"].toString();
    left = data["left"].toString();
    right = data["right"].toString();
    direct->setPos(dep::posFromString(data["direct"].toString()));
    QJsonArray pst = data["area"].toArray();
    for(int i=0; i<pst.size(); ++i){
        area[i]->setPos(dep::posFromString(pst[i].toString()));
    }
    gtext->setPos(dep::posFromString(data["txtpos"].toString()));
    paintView();
}

void cam::setchanges(QJsonObject data){
    camsize = data["camsize"].toInt();
    text = data["name"].toString();
    color = QColor(data["color"].toString());
    textsize = data["textsize"].toInt();
    url = data["url"].toString();
    stop = data["stop"].toString();
    up = data["up"].toString();
    down = data["down"].toString();
    left = data["left"].toString();
    right = data["right"].toString();
    paintView();
}

void cam::paintView(){
    setBrush(color);
    garea->setPen(QPen(color));
    QVector<QPointF> areapos;
    for(int i=0; i<area.size(); ++i)
        areapos.push_back(area[i]->pos() + direct->pos());
    garea->setPath(ptsConv::pts2Path(areapos,true));
    QPainterPath p = QPainterPath();
    p.addText(QPointF(),QFont(style,textsize),text);
    gtext->setPath(p);
    //linear
    QPainterPath path;
    if(enabled){
        path.moveTo(QPointF());
        path.lineTo(direct->pos());
    }
    //paint phisical camera
    QPointF box = geom::getPointByLenght(direct->pos(),QPointF(),camsize*1.4);
    QMap<int,QPointF> p0 = geom::getRectLen(box,geom::getABC(box,direct->pos()),camsize);
    path.addPath(ptsConv::pts2Path(p0.values(),true));

    QPointF lens = (p0[1]+p0[2])/2;
    QPointF bbx = geom::getPointByLenght(direct->pos(),lens,camsize*0.9);
    geom::abc ml = geom::getABC(lens,bbx);
    geom::abc ppml = ml.getPerpendicular(bbx);
    geom::abc up = ml.getDown(camsize*0.3);
    geom::abc down = ml.getUp(camsize*0.3);
    QPointF l = geom::getIntLL(ppml,up);
    QPointF r = geom::getIntLL(ppml,down);
    path.addPath(ptsConv::pts2Path({lens,l,r},true));
    path.addEllipse(QRectF(-4,-4,8,8));
    setPath(path);

    //dom element to svg data
    dom = QDomDocument();
    QDomElement g = dom.createElement("g");
    g.setAttribute("id",id);
    g.setAttribute("transform","translate(" +
                   QString::number(scenePos().x()) + " " +
                   QString::number(scenePos().y()) + ")");
    g.appendChild(ptsConv::createElement("path",
                                         ptsConv::pts2XML(p0.values(),true),
                                         true,Qt::black,2,
                                         true,color));
    g.appendChild(ptsConv::createElement("path",
                                         ptsConv::pts2XML({lens,l,r},true),
                                         true,Qt::black,2,
                                         true,color));
    g.appendChild(ptsConv::createElement("path",
                                         ptsConv::pts2XML(areapos,true),
                                         true,Qt::black,2,
                                         true,color));
    QDomElement label = dom.createElement("text");
    label.setAttribute("x",gtext->pos().x());
    label.setAttribute("y",gtext->pos().y());
    label.setAttribute("style","font-famyly: " + style);
    label.setAttribute("font-size",QString::number(textsize));
    label.setAttribute("fill",Qt::black);
    QDomText t = dom.createTextNode(text);
    label.appendChild(t);
    g.appendChild(label);
    dom.appendChild(g);
}

void cam::editItem(){
    setVisibleState(true);
    emit editSelf(this);
}

void cam::removeItem(){
    emit removeSelf(this);
}

void cam::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void cam::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void cam::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
}

void cam::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    paintView();
    QGraphicsPathItem::mouseReleaseEvent(event);
}
