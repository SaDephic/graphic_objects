#include "amid.h"
#include "custom/dep.h"

amid::amid(gpoint *gm, QVector<gline *> gsync){
    setFlag(QGraphicsItem::ItemIsFocusable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);

    //bc
    for(int i=0; i<gsync.size(); ++i){
        if(gsync[i]->tramway){
            setPen(QPen(Qt::yellow,2));
            setBrush(Qt::yellow);
            setZValue(100);
            break;
        }
        setZValue(100);
        setPen(QPen(Qt::gray,2));
        setBrush(Qt::gray);
    }

    bord = new QGraphicsPathItem;
    bord->setPen(QPen(Qt::white,2));
    bord->setBrush(Qt::NoBrush);
    bord->setFlag(QGraphicsItem::ItemIsFocusable,false);
    bord->setFlag(QGraphicsItem::ItemIsSelectable,false);
    bord->setZValue(104);//road

    m = gm;
    sync = gsync;

    varea = new QGraphicsPathItem;
    vbord = new QGraphicsPathItem;
}

amid::~amid(){
    delete varea;
    delete vbord;
    delete bord;
    while(!blr.isEmpty()){
        delete blr.takeFirst();
    }
}

void amid::update_mid(QVector<gline *> gsync){
    if(sync.size() != gsync.size()){
        while(!blr.isEmpty()){
            delete blr.takeFirst();
        }
    }

    sync = gsync;
    paintCurrentConfig();
}

bool amid::containsLine(gline *l){
    for(int i=0; i<sync.size(); ++i)
        if(sync[i]->id == l->id)
            return true;
    return false;
}

void amid::paintCurrentConfig(){
    QMap<double,gline*> l;
    //*************************************************
    for(int i=0; i<sync.size(); ++i){
        if(!sync[i]->tramway){
            l.insert(geom::getAngleRad(m->scenePos(),sync[i]->getSUPT(m)),
                     sync[i]);
        }
    }
    //*************************************************
    QVector<gline*> ll = l.values();
    if(!ll.isEmpty() && ll.size()>1){
        gline *lr0;
        gline *lr1;

        //begin
        for(int i=1; i<ll.size(); ++i){
            lr0 = ll[i-1];
            lr1 = ll[i];
            if(existSumid(lr0,lr1)){
                continue;
            }else{
                lr *adi = new lr(m,lr0,lr1);
                blr.push_back(adi);
                emit addItemToScene(adi);
                adi->repaintBords();
                connect(adi->p0,&pt::posChanged,this,&amid::paintCurrentConfig);
                connect(adi->p1,&pt::posChanged,this,&amid::paintCurrentConfig);
                connect(adi->p0,&pt::hovered,this,&amid::colorHover);
                connect(adi->p1,&pt::hovered,this,&amid::colorHover);
            }
        }

        //end
        lr0 = ll.last();
        lr1 = ll.first();
        if(!existSumid(lr0,lr1)){
            lr *adi = new lr(m,lr0,lr1);
            blr.push_back(adi);
            emit addItemToScene(adi);
            adi->repaintBords();
            connect(adi->p0,&pt::posChanged,this,&amid::paintCurrentConfig);
            connect(adi->p1,&pt::posChanged,this,&amid::paintCurrentConfig);
            connect(adi->p0,&pt::hovered,this,&amid::colorHover);
            connect(adi->p1,&pt::hovered,this,&amid::colorHover);
        }
    }

    QVector<QPointF> ara;
    //update points
    bool trmw = false;
    for(int i=0; i<sync.size(); ++i){
        if(sync[i]->tramway){
            trmw = true;
        }
    }

    QPainterPath pb = QPainterPath();
    if(trmw){
        while(!blr.isEmpty()){
            delete blr.takeFirst();
        }
        vbord->setPath(pb);
        varea->setPath(pb);
        return;
    }

    for(int i=0; i<blr.size(); ++i){
        blr[i]->repaintBords();
        pb.addPath(ptsConv::pts2Path(blr[i]->bpts,false));
        ara.append(blr[i]->pts);
    }

    vbord->setZValue(104);
    vbord->setPen(QPen(Qt::white,2,Qt::SolidLine));
    p = Qt::white;
    varea->setZValue(101);
    varea->setPen(QPen(Qt::gray,2));
    varea->setBrush(Qt::gray);

    vbord->setPath(pb);
    varea->setPath(ptsConv::pts2Path(ara,true));
}

bool amid::existSumid(gline *l, gline *r){
    for(int i=0; i<blr.size(); ++i){
        if(blr[i]->l == l && blr[i]->r == r){
            return true;
        }
    }
    return false;
}

void amid::colorHover(bool state){
    if(state){
        vbord->setPen(QPen(Qt::red,2));
    }else{
        vbord->setPen(QPen(p,2));
    }
}

QJsonObject lr::json(){
    QJsonObject data;
    data["l"] = l->id;
    data["r"] = r->id;
    data["p0"] = (QString)dep::posToString(p0->scenePos());
    data["p1"] = (QString)dep::posToString(p1->scenePos());
    return data;
}

void lr::setjson(QJsonObject data){
    p0->setPos(dep::posFromString(data["p0"].toString()));
    p1->setPos(dep::posFromString(data["p1"].toString()));
}
