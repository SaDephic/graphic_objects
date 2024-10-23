#include "factorydata.h"

factorydata::factorydata(){
    vel = new veledit;
}

void factorydata::addPoint(gpoint *p){
    connect(p,&gpoint::removeSelf,this,&factorydata::removePoint);
    p->id = stash->id.igpoint.get();
    stash->vecpoint.push_back(p);
}

void factorydata::addLine(gline *l){
    connect(l,&gline::removeSelf,this,&factorydata::removeLine);
    l->id = stash->id.igline.get();
    stash->vecline.push_back(l);
}

void factorydata::addTrafficLight(trafficlight *t){
    connect(t,&trafficlight::removeSelf,this,&factorydata::removeTrafficlight);
    t->id = stash->id.itraffic.get();
    stash->vectraffic.push_back(t);
}

void factorydata::addMark(mark *m){
    connect(m,&mark::removeSelf,this,&factorydata::removeMark);
    m->id = stash->id.imark.get();
    stash->vecmark.push_back(m);
}

void factorydata::addCam(cam *c){
    connect(c,&cam::removeSelf,this,&factorydata::removeCam);
    c->id = stash->id.icam.get();
    stash->veccam.push_back(c);
}

void factorydata::addCrosswalk(crosswalk *c){
    connect(c,&crosswalk::removeSelf,this,&factorydata::removeCrosswalk);
    c->id = stash->id.icrosswalk.get();
    stash->vecwalk.push_back(c);
}

void factorydata::addMid(amid *m){
    stash->vecmid.push_back(m);
}

gpoint *factorydata::getPoint(QPointF pos){
    gpoint *p = new gpoint(pos);
    addPoint(p);
    return p;
}

gpoint *factorydata::getPointById(int id){
    gpoint *point = nullptr;
    for(int i=0; i<stash->vecpoint.size(); ++i){
        if(id == stash->vecpoint[i]->id){
            point = stash->vecpoint[i];
        }
    }
    return point;
}

gline *factorydata::getLine(gpoint *b, gpoint *e){
    gline *l = new gline(b,e);
    addLine(l);
    connect(l,&gline::editSelf,vel,&veledit::setIO);
    return l;
}

trafficlight *factorydata::getTrafficLight(QPointF pos, int t){
    trafficlight *tl = new trafficlight(t);
    tl->setPos(pos);
    addTrafficLight(tl);
    connect(tl,&trafficlight::editSelf,vel,&veledit::setTL);
    return tl;
}

cam *factorydata::getCam(QPointF pos){
    cam *c = new cam();
    c->setPos(pos);
    addCam(c);
    connect(c,&cam::editSelf,vel,&veledit::setCM);
    return c;
}

mark *factorydata::getMark(QPointF pos){
    mark *m = new mark();
    m->setPos(pos);
    addMark(m);
    connect(m,&mark::editSelf,vel,&veledit::setMK);
    return m;
}

crosswalk *factorydata::getCrossWalk(QPointF pos){
    crosswalk *c = new crosswalk();
    c->setPos(pos);
    addCrosswalk(c);
    return c;
}

amid *factorydata::getMidRes(int idmid){
    amid *m = new amid(getPointById(idmid));
    addMid(m);
    return m;
}

amid *factorydata::getMid(gpoint *p){
    for(int i=0; i<stash->vecmid.size(); ++i){
        if(stash->vecmid[i]->m == p)
            return stash->vecmid[i];
    }
    return nullptr;
}

void factorydata::removeLine(gline *l){
    stash->id.igline.remove(l->id);
    stash->vecline.removeOne(l);

    //remove from mid
    foreach (amid *m, stash->vecmid) {
        if(m->containsLine(l)){
            m->sync.removeOne(l);
            if(m->sync.size()<2){
                stash->vecmid.removeOne(m);
                delete m;
            }else{
                m->paintCurrentConfig();
            }
        }
    }

    //removed single link-line
    delete l;
}

void factorydata::removePoint(gpoint *p){
    removeLinkedLines(p);
    stash->id.igpoint.remove(p->id);
    stash->vecpoint.removeOne(p);

    //****************************************
    //remove single point
    //****************************************
    for(int i=0; i<stash->vecmid.size(); ++i){
        if(stash->vecmid[i]->m == p){
            delete stash->vecmid.takeAt(i);
        }
    }
    //update VIEW
    for(int i=0; i<stash->vecmid.size(); ++i){
        stash->vecmid[i]->paintCurrentConfig();
    }
    //****************************************

    delete p;
}

void factorydata::removeTrafficlight(trafficlight *t){
    stash->id.itraffic.remove(t->id);
    stash->vectraffic.removeOne(t);
    delete t;
}

void factorydata::removeMark(mark *m){
    stash->id.imark.remove(m->id);
    stash->vecmark.removeOne(m);
    delete m;
}

void factorydata::removeCam(cam *c){
    stash->id.icam.remove(c->id);
    stash->veccam.removeOne(c);
    delete c;
}

void factorydata::removeCrosswalk(crosswalk *c){
    stash->id.icrosswalk.remove(c->id);
    stash->vecwalk.removeOne(c);
    delete c;
}

void factorydata::removeLinkedLines(gpoint *p){
    foreach (gline *l, stash->vecline) {
        if(l->exist(p)){
            emit l->removeSelf(l);
        }
    }
}
