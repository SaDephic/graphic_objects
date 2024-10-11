#include "gline.h"

gline::gline(QPointF first, QPointF second, bool parentline, gline *gpline){
    pline = gpline;//parent object link
    this->parentline = parentline;
    b = new gpoint(first,this);
    e = new gpoint(second,this);
    construct();
}

gline::gline(gpoint *first, gpoint *second, bool parentline, gline *gpline){
    pline = gpline;//parent object link
    this->parentline = parentline;
    b = first;
    e = second;
    construct();
}

gline::~gline(){
    if(parentline){
        disconnect(b,&gpoint::posChanged,this,&gline::paintLine);
        disconnect(e,&gpoint::posChanged,this,&gline::paintLine);
    }else{
        delete place;
        delete middle;
        delete sulines;
        delete area;
    }
}

void gline::construct(){
    setPen(QPen(Qt::black,2));
    setZValue(150);
    setAcceptHoverEvents(true);

    middle = new QGraphicsPathItem;
    middle->setPen(QPen(Qt::white,2));
    middle->setFlag(QGraphicsItem::ItemIsFocusable,false);
    middle->setFlag(QGraphicsItem::ItemIsSelectable,false);

    place = new QGraphicsPathItem;
    place->setPen(QPen(Qt::white,2));
    place->setFlag(QGraphicsItem::ItemIsFocusable,false);
    place->setFlag(QGraphicsItem::ItemIsSelectable,false);

    sulines = new QGraphicsPathItem;
    sulines->setPen(QPen(Qt::white,2,Qt::DashLine));
    sulines->setFlag(QGraphicsItem::ItemIsFocusable,false);
    sulines->setFlag(QGraphicsItem::ItemIsSelectable,false);

    area = new QGraphicsPathItem;
    area->setPen(QPen(Qt::gray,2));
    area->setBrush(Qt::gray);
    area->setFlag(QGraphicsItem::ItemIsFocusable,false);
    area->setFlag(QGraphicsItem::ItemIsSelectable,false);

    if(parentline)
        setParentItem(pline);

    connect(b,&gpoint::posChanged,this,&gline::paintLine);
    connect(e,&gpoint::posChanged,this,&gline::paintLine);

    paintLine();

    menu = new QMenu();
    QAction *act = nullptr;
    act = new QAction("Добавить точку");//split
    connect(act,&QAction::triggered,this,&gline::splitItem);
    menu->addAction(act);
    act = new QAction("Удалить связь");//remove link
    connect(act,&QAction::triggered,this,&gline::removeItem);
    menu->addAction(act);

    menu->addSeparator();

    act = new QAction("Редактировать");
    connect(act,&QAction::triggered,this,&gline::editItem);
    menu->addAction(act);
}

bool gline::exist(gpoint *p){
    return b->id==p->id || e->id==p->id;
}

gpoint *gline::getE(gpoint *p){
    if(b->id == p->id)
        return e;
    return nullptr;
}

gpoint *gline::getB(gpoint *p){
    if(e->id == p->id)
        return b;
    return nullptr;
}

QJsonObject gline::json(){
    QJsonObject data;
    data["id"] = (int)id;
    data["try"] = (bool)tramway;

    data["in"] = (int)in;
    data["out"] = (int)out;
    data["sizeline"] = (int)sizeLen;
    data["sizemidline"] = (int)sizeMidLen;
    data["chin"] = (bool)chin;
    data["chout"] = (bool)chout;

    data["b"] = (int) b->id;
    data["e"] = (int) e->id;
    data["pts"] = (QJsonArray) points();
    data["lns"] = (QJsonArray) lines();
    return data;
}

void gline::setjson(QJsonObject data){
    id = data["id"].toInt();
    tramway = data["try"].toBool();

    in = data["in"].toInt();
    out = data["out"].toInt();
    sizeLen = data["sizeline"].toInt();
    sizeMidLen = data["sizemidline"].toInt();
    chin = data["chin"].toBool();
    chout = data["chout"].toBool();

    QJsonArray pts = data["pts"].toArray();
    for(int i=0; i<pts.size(); ++i){
        gpoint *p = new gpoint(QPointF(),this,false);
        p->setjson(pts[i].toObject());
        subpoint.push_back(p);
        connect(p,&gpoint::removeSelf,this,&gline::repairItem);
    }
    QJsonArray lns = data["lns"].toArray();
    for(int i=0; i<lns.size(); ++i){
        QJsonObject o = lns[i].toObject();
        gline *l = new gline(getSubPoint(o["b"].toInt()),
                             getSubPoint(o["e"].toInt()),true,this);
        subline.push_back(l);
    }
    paintAll();
}

void gline::setchanges(QJsonObject data){
    in = data["in"].toInt();
    out = data["out"].toInt();
    tramway = data["try"].toBool();
    sizeLen = data["sizeline"].toInt();
    sizeMidLen = data["sizemidline"].toInt();
    chin = data["chin"].toBool();
    chout = data["chout"].toBool();
    paintAll();
}

bool gline::notEmpty(){
    if(subpoint.size()>1)
        return true;
    return false;
}

void gline::split(QPointF pos){
    //parentline
    gline *pl = getParentLine();
    //new point
    gpoint *p = new gpoint(pos,pl,false); p->id = idsl.get();
    pl->subpoint.push_back(p);//added new point
    connect(p,&gpoint::removeSelf,pl,&gline::repairItem);
    //cutted lines
    gline *f = new gline(b,p,true,pl);
    gline *s = new gline(p,e,true,pl);
    //mechanic add subs
    if(parentline){
        int indx = pl->subline.indexOf(this);
        pl->subline.insert(indx,f);
        pl->subline.insert(pl->subline.indexOf(f),s);
        pl->subline.removeOne(this);
        delete this;
        return;
    }else{
        pl->subline.push_back(f);
        pl->subline.push_back(s);
    }

    setSubOrder();

    pl->paintAll();
}

void gline::repair(gpoint *p){
    int indx = 0;
    gpoint *brp = nullptr;
    gpoint *erp = nullptr;

    foreach (gline *l, subline) {
        if(brp && erp)
            break;

        gpoint *bpt = l->getB(p);
        gpoint *ept = l->getE(p);


        if(!brp && bpt){
            brp = bpt;
            indx = subline.indexOf(l);
            subline.removeOne(l);
            delete l;
            continue;
        }
        if(!erp && ept){
            erp = ept;
            subline.removeOne(l);
            delete l;
            continue;
        }
    }

    if(!subline.isEmpty()){
        gline *r = new gline(brp,erp,true,this);
        subline.insert(indx,r);
    }

    subpoint.removeOne(p);
    delete p;

    setSubOrder();

    paintAll();
}

void gline::splitItem(){
    emit getParentLine()->splitLine(this);
}

void gline::repairItem(gpoint *p){
    getParentLine()->repair(p);
}

void gline::setSubOrder(){
    std::sort(subline.begin(), subline.end(), [](gline* a, gline* b) {
        return a->b->id == b->e->id;
    });
}

void gline::editItem(){
    gline *pl = getParentLine();
    emit pl->editSelf(pl);
}

void gline::removeItem(){
    gline *pl = getParentLine();
    emit pl->removeSelf(pl);
}

gline *gline::getParentLine(){
    gline *pl = this;
    if(parentline){
        pl = pline;
    }
    return pl;
}

gpoint *gline::getSubPoint(int id){
    gpoint *point = nullptr;
    QVector<gpoint*> fls = subpoint;
    fls.push_back(b);
    fls.push_back(e);
    for(int i=0; i<fls.size(); ++i){
        if(fls[i]->id == id){
            point = fls[i];
            break;
        }
    }
    return point;
}

QJsonObject gline::subjson(){
    QJsonObject data;
    data["b"] = (int)b->id;
    data["e"] = (int)e->id;
    return data;
}

QJsonArray gline::lines(){
    QJsonArray data;
    for(int i=0; i<subline.size(); ++i){
        data.push_back(subline[i]->subjson());
    }
    return data;
}

QJsonArray gline::points(){
    QJsonArray data;
    for(int i=0; i<subpoint.size(); ++i){
        data.push_back(subpoint[i]->json());
    }
    return data;
}

QVector<QPointF> gline::getMainLine(){
    //paint road
    QVector<QPointF> pts;
    if(!subline.isEmpty()){
        //pts.push_back(subline.first()->e->scenePos());
        for(int i=1; i<subline.size(); ++i){
            pts.push_back(subline[i]->e->scenePos());
        }
        //pts.push_back(subline.last()->b->scenePos());
    }/*else{
            pts.push_back(e->scenePos());
            pts.push_back(b->scenePos());
        }*/
    return pts;
}

void gline::paintRoad(){
    middle->setPen(QPen(Qt::white,2));
    place->setPen(QPen(Qt::white,2));
    sulines->setPen(QPen(Qt::white,2,Qt::DashLine));
    area->setPen(QPen(Qt::gray,2));
    area->setBrush(Qt::gray);

    middle->setZValue(104);
    place->setZValue(104);
    sulines->setZValue(104);
    area->setZValue(101);

    paintSuline();
    paintMiddle();
    paintBords();
    paintPlace();
}

void gline::paintSuline(){
    QPainterPath p = QPainterPath();
    if(in==0 && out == 0){
        sulines->setPath(p);
        return;
    }

    QVector<QPointF> mline = getMainLine();
    int count = in+out;
    if(count>0){
        if(in==0 || out==0){
            if(count&1){
                for(int i=0; i<count/2; ++i){
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2 + i*sizeLen,true)),false));
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2 + i*sizeLen,false)),false));
                }
            }else{
                for(int i=0; i<count/2; ++i){
                    if(i==0){
                        p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,i*sizeLen,true)),false));
                        continue;
                    }
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,i*sizeLen,true)),false));
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,i*sizeLen,false)),false));
                }
            }
        }else{
            for(int i=1; i<in; ++i)
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeLen*i,true)),false));
            for(int i=1; i<out; ++i)
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeLen*i,false)),false));
        }
    }

    sulines->setPath(p);
}

void gline::paintMiddle(){
    QPainterPath p = QPainterPath();
    if(in==0 || out == 0){
        middle->setPath(p);
        return;
    }

    QVector<QPointF> mline = getMainLine();
    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2,true)),false));//left
    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2,false)),false));//right
    middle->setPath(p);
}

void gline::paintBords(){
    QPainterPath p = QPainterPath();
    if(in==0 && out == 0){
        place->setPath(p);
        return;
    }

    QVector<QPointF> mline = getMainLine();
    if(in>0 && out>0){
        p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeLen*in,true)),false));//left
        p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeLen*out,false)),false));//right
    }else{
        int count = in+out;
        if(count&1){
            p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2 + ((count-1)/2)*sizeLen,true)),false));
            p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2 + ((count-1)/2)*sizeLen,false)),false));
        }else{
            p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen + ((count-1)/2)*sizeLen,true)),false));
            p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen + ((count-1)/2)*sizeLen,false)),false));
        }
    }
    place->setPath(p);
}

void gline::paintPlace(){
    QPainterPath p = QPainterPath();
    if(in==0 && out == 0){
        area->setPath(p);
        return;
    }

    QVector<QPointF> mline = getMainLine();
    if(in>0 && out>0){
        QVector<QPointF> vec = geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeLen*out + 2,false));
        std::reverse(vec.begin(),vec.end());
        vec.append(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2+sizeLen*in + 2,true)));
        p.addPath(ptsConv::pts2Path(vec,false));
    }else{
        int count = in+out;
        if(count&1){
            QVector<QPointF> vec = geom::getBezie(geom::getParralelLine(mline,sizeLen/2 + ((count-1)/2)*sizeLen + 2,true));
            std::reverse(vec.begin(),vec.end());
            vec.append(geom::getBezie(geom::getParralelLine(mline,sizeLen/2 + ((count-1)/2)*sizeLen+ 2,false)));
            p.addPath(ptsConv::pts2Path(vec,false));
        }else{
            QVector<QPointF> vec = geom::getBezie(geom::getParralelLine(mline,sizeLen + ((count-1)/2)*sizeLen + 2,true));
            std::reverse(vec.begin(),vec.end());
            vec.append(geom::getBezie(geom::getParralelLine(mline,sizeLen + ((count-1)/2)*sizeLen + 2,false)));
            p.addPath(ptsConv::pts2Path(vec,false));
        }
    }
    area->setPath(p);
}

void gline::paintTramway(){
    sulines->setPen(QPen(Qt::black,2,Qt::DashLine));
    area->setPen(QPen(Qt::yellow,2));
    area->setBrush(Qt::yellow);

    sulines->setZValue(105);
    area->setZValue(100);

    paintRails();
    paintSurfase();
}

void gline::paintRails(){
    QPainterPath p = QPainterPath();
    if(in==0 && out == 0){
        sulines->setPath(p);
        return;
    }

    QVector<QPointF> mline = getMainLine();
    int count = in+out;
    if(count>0){
        if(in==0 || out==0){
            if(count&1){
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2,true)),false));
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2,false)),false));
                for(int i=1; i<count/2+1; ++i){
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2+sizeMidLen*i+sizeLen*i-sizeLen,true)),false));
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2+sizeMidLen*i+sizeLen*i-sizeLen,false)),false));
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2+sizeMidLen*i+sizeLen*i,true)),false));
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeLen/2+sizeMidLen*i+sizeLen*i,false)),false));
                }
            }else{
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2,true)),false));
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2,false)),false));
                int nxt = sizeMidLen/2;
                for(int i=1; i<count/2+1; ++i){
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,true)),false));
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,false)),false));
                    if(i<count/2){
                        nxt += sizeMidLen;
                        p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,true)),false));
                        p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,false)),false));
                    }
                }
            }
        }else{
            p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2,true)),false));
            int nxt = sizeMidLen/2;
            for(int i=1; i<in+1; ++i){
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,true)),false));
                if(i<in){
                    nxt += sizeMidLen;
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,true)),false));
                }
            }
            p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,sizeMidLen/2,false)),false));
            nxt = sizeMidLen/2;
            for(int i=1; i<out+1; ++i){
                p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,false)),false));
                if(i<out){
                    nxt += sizeMidLen;
                    p.addPath(ptsConv::pts2Path(geom::getBezie(geom::getParralelLine(mline,nxt+sizeLen*i,false)),false));
                }
            }
        }
    }
    sulines->setPath(p);
}

void gline::paintAll(){
    if(!parentline)
        paintLine();
    for(int i=0; i<subline.size(); ++i){
        subline[i]->paintLine();
    }
}

void gline::paintLine(){
    QPainterPath p = QPainterPath();
    if(subline.isEmpty() && (b&&e)){
        p.moveTo(b->pos());
        p.lineTo(e->pos());
    }
    setPath(p);

    freshArea();//clear before data
    if(getParentLine()->tramway){
        getParentLine()->paintTramway();
    }else{
        getParentLine()->paintRoad();
    }
}

void gline::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setToolTip(QString::number(getParentLine()->id));
    setPen(QPen(Qt::red,5));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void gline::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black,2));
    QGraphicsPathItem::hoverLeaveEvent(event);
}