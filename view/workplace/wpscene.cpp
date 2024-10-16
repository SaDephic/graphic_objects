#include "wpscene.h"

wpscene::wpscene(){
    center = new gpoint(true, QPointF());
    connect(center,&gpoint::posChanged,this,&wpscene::saveMiddlePos);
    connect(stash,&stashdata::nullCenter,this,&wpscene::nullCenter);
    addItem(center);

    sow = new QGraphicsPathItem;
    sow->setPen(QPen(Qt::red,2));
    sow->setFlag(QGraphicsItem::ItemIsSelectable,false);
    sow->setFlag(QGraphicsItem::ItemIsFocusable,false);
    addItem(sow);

    map = new QGraphicsPixmapItem;
    setMap(wpscene::emptyMap());
    addItem(map);

    lpts = new linkpts;
    addItem(lpts);
}

void wpscene::setMap(QByteArray arr){
    QPixmap pix;
    pix.loadFromData(arr,"PNG");
    setSceneRect(QRectF(-150,-150,pix.width()+300,pix.height()+300));
    map->setOpacity(1);
    map->setPixmap(pix);

    int stp = 50;
    QFont f = QFont("Times New Roman",14);

    QPainterPath so = QPainterPath();
    so.addText(QPointF(pix.width()/2,0) + QPointF(0,-stp),f,lsw[0]);//с
    so.addText(QPointF(pix.width(),0) + QPointF(stp,-stp),f,lsw[1]);//св
    so.addText(QPointF(pix.width(),pix.height()/2) + QPointF(stp,0),f,lsw[2]);//в
    so.addText(QPointF(pix.width(),pix.height()) + QPointF(stp,stp),f,lsw[3]);//юв
    so.addText(QPointF(pix.width()/2,pix.height()) + QPointF(0,stp),f,lsw[4]);//ю
    so.addText(QPointF(0,pix.height()) + QPointF(-stp,stp),f,lsw[5]);//юз
    so.addText(QPointF(0,pix.width()/2) + QPointF(-stp,0),f,lsw[6]);//з
    so.addText(QPointF(0,0) + QPointF(-stp,-stp),f,lsw[7]);//сз
    sow->setPath(so);
}

QPointF wpscene::centerPos(){
    return center->pos();
}

void wpscene::updateLinker(){
    lpts->updateLink(mpos);
}

bool wpscene::linkBusy(){
    return lpts->busy();
}

QByteArray wpscene::emptyMap(QSize size){
    QByteArray map;
    QPixmap pix(size);
    pix.fill();
    QBuffer buffer(&map);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer, "PNG");
    buffer.close();
    return map;
}

QByteArray wpscene::getMap(){
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    map->pixmap().save(&buffer, "PNG");
    return bArray;
}

void wpscene::createLink(gpoint *p){
    if(!lpts->busy()){
        lpts->startLink(p);
    }
}

void wpscene::linkWith(gpoint *p){
    if(linkBusy()){
        if(lpts->doneLink(p)){
            gline *l = lpts->getLink();//linkser is done
            connect(l,&gline::updateMid,this,&wpscene::paintMidArea);
            connect(l,&gline::splitLine,this,&wpscene::splitLine);
            connect(l,&gline::editSelf,factory->vel,&veledit::setIO);
            addItem(l);
            //*****************************
            addItem(l->place);
            addItem(l->area);
            addItem(l->middle);
            addItem(l->sulines);
            //*****************************
            factory->addLine(l);
        }
    }
}

void wpscene::addAllItems(){
    center->setPos(stash->mid);
    for(int i=0; i<stash->vecpoint.size(); ++i){
        connect(stash->vecpoint[i],&gpoint::linkWith,this,&wpscene::createLink);
        addItem(stash->vecpoint[i]);
    }
    for(int i=0; i<stash->vecline.size(); ++i){
        connect(stash->vecline[i],&gline::splitLine,this,&wpscene::splitLine);
        connect(stash->vecline[i],&gline::updateMid,this,&wpscene::paintMidArea);
        addItem(stash->vecline[i]);
        //************************************
        addItem(stash->vecline[i]->place);
        addItem(stash->vecline[i]->area);
        addItem(stash->vecline[i]->middle);
        addItem(stash->vecline[i]->sulines);
        //************************************
    }
    for(int i=0; i<stash->vectraffic.size(); ++i){
        addItem(stash->vectraffic[i]);
    }
    for(int i=0; i<stash->veccam.size(); ++i){
        addItem(stash->veccam[i]);
    }
    for(int i=0; i<stash->vecmark.size(); ++i){
        addItem(stash->vecmark[i]);
    }
    for(int i=0; i<stash->vecwalk.size(); ++i){
        addItem(stash->vecwalk[i]);
    }

    //add mid area
    paintMidArea();//update after add middle
}

void wpscene::addNode(){
    gpoint *p = factory->getPoint(rcp);
    connect(p,&gpoint::linkWith,this,&wpscene::createLink);
    addItem(p);
}

void wpscene::addRTL(){
    trafficlight *t = factory->getTrafficLight(rcp);
    addItem(t);
}

void wpscene::addTTL(){
    trafficlight *t = factory->getTrafficLight(rcp,1);
    addItem(t);
}

void wpscene::addCW(){
    crosswalk *c = factory->getCrossWalk(rcp);
    addItem(c);
}

void wpscene::addCM(){
    cam *c = factory->getCam(rcp);
    addItem(c);
}

void wpscene::addMK(){
    mark *m = factory->getMark(rcp);
    addItem(m);
}

void wpscene::setCenter(){
    center->setPos(rcp);
    center->setVisible(true);
}

void wpscene::splitLine(gline *line){
    line->split(rcp);
}

void wpscene::saveMiddlePos(){
    stash->mid = center->scenePos();
}

void wpscene::nullCenter(){
    center->setPos(QPointF());
}

void wpscene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(linkBusy()){
            QGraphicsItem *it = itemAt(event->scenePos().toPoint(),QTransform());
            if(it){
                gpoint *igpi = dynamic_cast<gpoint*>(it);//gpoint
                if(igpi){
                    //create new link
                    linkWith(igpi);
                }
            }
        }else{
            QGraphicsItem *item = itemAt(event->scenePos(),QTransform());
            if(item && item != map){
            }else{
                center->setVisible(false);
            }
        }
    }

    if(event->button() == Qt::RightButton){
        rcp = event->scenePos();
        if(linkBusy()){
            lpts->null();
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void wpscene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    mpos = event->scenePos();
    QGraphicsScene::mouseMoveEvent(event);
}
