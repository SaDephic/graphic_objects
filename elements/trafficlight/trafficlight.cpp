#include "trafficlight.h"
#include "custom/geom.h"
#include "custom/dep.h"

grabLamp::grabLamp(QGraphicsItem *parent){
    setParentItem(parent);
    setVisible(false);

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGray);
    setPen(QPen(Qt::black,2));

    QPainterPath path;
    path.addRect(QRectF(-3,-3,6,6));
    setPath(path);
}

void grabLamp::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void grabLamp::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black,2));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void grabLamp::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mousePressEvent(event);
}

void grabLamp::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseMoveEvent(event);
}

void grabLamp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit posChanged();
    QGraphicsPathItem::mouseReleaseEvent(event);
}

section::section(){}

void section::rev(){
    enabled = !enabled;
}

trafficlight::trafficlight(int typelight){
    setZValue(110);

    t = typelight;

    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);

    setBrush(Qt::darkGreen);
    setPen(QPen(Qt::black));

    skelet = new QGraphicsPathItem(this);
    skelet->setFlag(QGraphicsItem::ItemStacksBehindParent);
    skelet->setFlag(QGraphicsItem::ItemIsFocusable,false);
    skelet->setFlag(QGraphicsItem::ItemIsSelectable,false);
    skelet->setBrush(Qt::NoBrush);
    skelet->setPen(QPen(Qt::black,2));

    selectView = new QGraphicsPathItem(this);
    selectView->setFlag(QGraphicsItem::ItemIsFocusable,false);
    selectView->setFlag(QGraphicsItem::ItemIsSelectable,false);
    selectView->setBrush(Qt::red);
    selectView->setPen(QPen(Qt::NoPen));

    QPainterPath path;
    path.addRect(QRectF(-4,-4,8,8));
    setPath(path);

    for(int i=0; i<16; i++){
        ll.push_back(new LensLamp(this,i));
        connect(ll[i],&LensLamp::linkLight,this,&trafficlight::controlLight);
        connect(ll[i],&LensLamp::changeState,this,&trafficlight::changeState);
        llst.push_back(section());
        //middle
        if(t == 0){
            if(i==1||i==5||i==9||i==13
                    ||i==0||i==4||i==8||i==12)
                llst[i].visbleState = true;
        }
        if(t == 1){
            if(i==1||i==5||i==9||i==13)
                llst[i].visbleState = true;
        }
    }
    for(int i=0; i<4; i++){
        gl.push_back(new grabLamp(this));
        connect(gl[i],&grabLamp::posChanged,this,&trafficlight::setLLPosition);
    }

    menu = new QMenu;
    QAction *act = nullptr;
    if(t == 0){
        addsect = new QAction("Добавить секцию");
        addsect->setEnabled(false);
        connect(addsect,&QAction::triggered,this,&trafficlight::addLens);
        menu->addAction(addsect);
    }
    act = new QAction("Редактировать");
    connect(act,&QAction::triggered,this,&trafficlight::editItem);
    menu->addAction(act);
    menu->addSeparator();
    act = new QAction("Удалить");
    connect(act,&QAction::triggered,this,&trafficlight::removeItem);
    menu->addAction(act);
}

trafficlight::~trafficlight(){}

void trafficlight::setPos(QPointF pos){
    setDefaultPosition();
    QGraphicsPathItem::setPos(pos);
}

void trafficlight::setVisibleState(bool state){
    enabled = state;
    if(t == 0){
        addsect->setEnabled(state);
        for(int i=0; i<gl.size(); ++i)
            gl[i]->setVisible(state);
        if(state){
            for(int i=0; i<16; i++){
                ll[i]->setVisible(llst[i].visbleState);
            }
        }else{
            for(int i=0; i<16; i++){
                ll[i]->setVisible(false);
            }
        }
        for(int i=0; i<almp.size(); ++i){
            almp[i]->setVisibleGrabs(state);
        }
    }
    if(t == 1){
        for(int i=0; i<gl.size(); ++i)
            gl[i]->setVisible(state);
        for(int i=0; i<llst.size(); ++i){
            if(state){
                if(i==1||i==5||i==9||i==13)
                    ll[i]->setVisible(llst[i].visbleState);
            }else{
                for(int i=0; i<16; i++){
                    ll[i]->setVisible(false);
                }
            }
        }
    }
    setLLPosition();
}

QJsonObject trafficlight::json(){
    QJsonObject data;
    data["id"] = (int)id;
    data["size"] = (int)size;
    data["type"] = (int)t;
    data["pos"] = (QString)dep::posToString(scenePos());
    QJsonArray allst;
    for(int i=0; i<llst.size(); ++i){
        if(llst[i].enabled){
            allst.push_back(i);
        }
    }
    data["ll"] = allst;
    QJsonArray agl;
    for(int i=0; i<gl.size(); ++i){
        agl.push_back((QString)(dep::posToString(gl[i]->pos())));
    }
    data["gl"] = agl;
    QJsonArray addgrb;
    for(int i=0; i<almp.size(); ++i){
        addgrb.push_back(almp[i]->json());
    }
    data["adl"] = addgrb;
    return data;
}

void trafficlight::setjson(QJsonObject data){
    id = data["id"].toInt();
    size = data["size"].toInt();
    qDebug() << dep::posFromString(data["pos"].toString());
    QGraphicsPathItem::setPos(dep::posFromString(data["pos"].toString()));
    QJsonArray allst = data["ll"].toArray();
    for(int i=0; i<allst.size(); ++i){
        int p = allst[i].toInt();
        llst[p].enabled = true;
        if(t==0)
            if(p==1||p==5||p==9||p==13){
                llst[p].RL = true;
                llst[p+1].visbleState=llst[p].RL;
                llst[p+2].visbleState=llst[p].RL;
            }
    }
    QJsonArray agl = data["gl"].toArray();
    for(int i=0; i<agl.size(); ++i){
        gl[i]->setPos(dep::posFromString(agl[i].toString()));
    }
    QJsonArray addgrb = data["adl"].toArray();
    for(int i=0; i<addgrb.size(); ++i){
        AddLamp *it = addLens();
        it->setVisibleGrabs(false);
        it->setjson(addgrb[i].toObject());
    }
    setLLPosition();//update after setValues
}

void trafficlight::setchanges(QJsonObject data){
    id = data["id"].toInt();
    size = data["size"].toInt();
    setLLPosition();
}

void trafficlight::setLinkState(bool state){
    for(int i=0; i<almp.size(); ++i){
        almp[i]->link = state;
    }
    for(int i=0; i<ll.size(); ++i){
        ll[i]->link = state;
    }
}

void trafficlight::setVisisbleActiveLenses(bool state){
    if(t == 0){
        for(int i=0; i<llst.size(); ++i){
            if(llst[i].enabled){
                ll[i]->setVisible(state);
            }
        }
        for(int i=0; i<almp.size(); ++i){
            almp[i]->setVisible(state);
        }
    }
    if(t == 1){
        for(int i=0; i<llst.size(); ++i){
            if(llst[i].enabled){
                if(i==1 || i==5 || i==9 || i==13){
                    ll[i-1]->setVisible(state);
                    ll[i]->setVisible(state);
                    ll[i+1]->setVisible(state);
                    ll[i+2]->setVisible(state);
                }
            }
        }
    }
}

void trafficlight::setSelected(QVector<QString> llns){
    for(int i=0; i<llns.size(); ++i){
        auto spl = llns[i].split(".");
        if(spl[0] == QString::number(id)){
            if(spl[1].toInt()<100){
                ll[spl[1].toInt()]->setSelected(true);
            }else{
                for(int e=0; e<almp.size(); ++e){
                    if((almp[e]->index + 100) == spl[1].toInt())
                        almp[e]->setSelected(true);
                }
            }
        }
    }
}

void trafficlight::dropSelected(){
    for(int i=0; i<ll.size(); ++i)
        ll[i]->setSelected(false);
    for(int i=0; i<almp.size(); ++i)
        almp[i]->setSelected(false);
}

void trafficlight::setVisibleSelected(QVector<QString> llns){
    QPainterPath pp = QPainterPath();
    for(int i=0; i<llns.size(); ++i){
        auto spl = llns[i].split(".");
        if(spl[0] == QString::number(id)){
            if(spl[1].toInt()<100){
                pp.addEllipse(ll[spl[1].toInt()]->pos(),6,6);//ll[spl[1].toInt()]->setSelected(true);
            }else{
                for(int e=0; e<almp.size(); ++e){
                    if((almp[e]->index + 100) == spl[1].toInt()){
                        pp.addEllipse(almp[e]->pos(),6,6);//almp[e]->setSelected(true);
                    }
                }
            }
        }
    }
    selectView->setPath(pp);
}

void trafficlight::dropVisibleSelected(){
    selectView->setPath(QPainterPath());
}

QPainterPath trafficlight::getStock(){
    return stoklens;
}

QMap<QString, QPainterPath> trafficlight::getLensesAnimate(){
    return lensesitem;
}

void trafficlight::setDefaultPosition(){
    gl[0]->setPos(QPointF(0,-80));
    gl[1]->setPos(QPointF(80,0));
    gl[2]->setPos(QPointF(0,80));
    gl[3]->setPos(QPointF(-80,0));
    setLLPosition();
}

void trafficlight::changeState(int id){
    llst[id].rev();
    if(t == 0){
        if(id==1||id==5||id==9||id==13){
            llst[id].RL=llst[id].enabled;
            llst[id+1].visbleState=llst[id].RL;
            llst[id+2].visbleState=llst[id].RL;
            llst[id+1].enabled=false;
            llst[id+2].enabled=false;
        }
    }
    if(t == 1){
        if(id==1||id==5||id==9||id==13){
            llst[id].RL=llst[id].enabled;
        }
    }
    setLLPosition();
}

void trafficlight::setLLPosition(){
    stoklens = QPainterPath();
    lensesitem.clear();

    dom.clear();//clear view
    QPainterPath section;//painter view
    //for generator
    QDomElement gsect = dom.createElement("g");
    gsect.setAttribute("id",QString::number(id));
    gsect.setAttribute("transform","translate(" +
                       QString::number(scenePos().x()) + " " +
                       QString::number(scenePos().y()) + ")");
    for(int g=0; g<gl.size(); ++g){
        QDomElement sect = dom.createElement("g");
        //sizes
        int mu = size/3;
        int up = g*4;
        //index lenses
        int cw = up;
        int m = up+1;
        int l = up+2;
        int r = up+3;
        //main line
        geom::abc mline = geom::getABC(gl[g]->pos(),QPointF());
        //points light
        QPointF cw_pos = geom::getPointByLenght(QPointF(),gl[g]->pos(),mu+(size/4));//crosswalk
        QPointF m_pos;
        QPointF l_pos;
        QPointF r_pos;
        //middle section;
        t==1
                ?m_pos = geom::getPointByLenght(QPointF(),cw_pos,(size/4)*1.5+mu)//TTL
                :m_pos = geom::getPointByLenght(QPointF(),cw_pos,(size/4)*2+mu);//RTL
        t==1
                ?l_pos = geom::getIntLL(mline.getPerpendicular(m_pos),mline.getUp(size*0.8))//left section TTL
                :l_pos = geom::getIntLL(mline.getPerpendicular(m_pos),mline.getUp(size));//left section RTL
        t==1
                ?r_pos = geom::getIntLL(mline.getPerpendicular(m_pos),mline.getDown(size*0.8))//right section TTL
                :r_pos = geom::getIntLL(mline.getPerpendicular(m_pos),mline.getDown(size));//right section RTL

        geom::abc labc = geom::getABC(l_pos,m_pos).getPerpendicular(l_pos);
        geom::abc rabc = geom::getABC(m_pos,r_pos).getPerpendicular(r_pos);
        //position of manage lens
        ll[cw]->setPos(cw_pos);
        ll[l]->setPos(l_pos);
        ll[m]->setPos(m_pos);
        ll[r]->setPos(r_pos);
        //cube point
        QMap<int,QPointF> p0 = geom::getRect(cw_pos,mline,size/2,true);//crosswalk
        QMap<int,QPointF> p1 = geom::getRect(m_pos,mline,size/2);//mid
        QMap<int,QPointF> p2 = geom::getRect(l_pos,labc,size/2);//left
        QMap<int,QPointF> p3 = geom::getRect(r_pos,rabc,size/2);//right
        //lenses path
        QVector<QPointF> lencw = p0.values();
        QVector<QPointF> lenm = geom::getBezie(p1.values());
        QVector<QPointF> lenl = geom::getBezie(p2.values());
        QVector<QPointF> lenr = geom::getBezie(p3.values());
        //grab -> (cw_len o-(\-\=\ 0 mid_len)
        QVector<QPointF> stickpt0 = {geom::getIntLLPoint({QPointF(),gl[g]->pos()},{p0[1],p0[2]}),//p0[1],p0[2];//top
                                     geom::getIntLLPoint({QPointF(),gl[g]->pos()},{p1[3],p1[0]})};//p1[3],p1[0];//low
        //stock to middle
        QVector<QPointF> stickpt1 = {QPointF(),
                                     geom::getIntLLPoint({QPointF(),gl[g]->pos()},lenm)};
        //stock to crosswalk
        QVector<QPointF> stickpt2 = {QPointF(),
                                     geom::getIntLLPoint({QPointF(),gl[g]->pos()},{p0[1],p0[2]})};//p0[1],p0[2];//top
        //ROAD TRAFFICLIGHT
        if(t == 0){
            //add resulted lens
            if(llst[cw].enabled){
                section.addPath(ptsConv::pts2Path(lencw,true));

                //animate
                QPainterPath a = ptsConv::pts2Path(lencw,true);
                lensesitem[QString::number(id) + "." + QString::number(cw)] = a;

                sect.appendChild(ptsConv::createElement("path",
                                                        ptsConv::pts2XML(lencw,true),
                                                        true,Qt::black,2,
                                                        true,Qt::darkGray,
                                                        true,QString::number(id) + "." + QString::number(cw)));

            }
            if(llst[m].enabled){
                section.addPath(ptsConv::pts2Path(lenm,true));

                //animate
                QPainterPath a = ptsConv::pts2Path(lenm,true);
                lensesitem[QString::number(id) + "." + QString::number(m)] = a;

                sect.appendChild(ptsConv::createElement("path",
                                                        ptsConv::pts2XML(lenm,true),
                                                        true,Qt::black,2,
                                                        true,Qt::darkGray,
                                                        true,QString::number(id) + "." + QString::number(m)));
            }
            if(llst[l].enabled){
                section.addPath(ptsConv::pts2Path(lenl,true));

                //animate
                QPainterPath a = ptsConv::pts2Path(lenl,true);
                lensesitem[QString::number(id) + "." + QString::number(l)] = a;

                sect.appendChild(ptsConv::createElement("path",
                                                        ptsConv::pts2XML(lenl,true),
                                                        true,Qt::black,2,
                                                        true,Qt::darkGray,
                                                        true,QString::number(id) + "." + QString::number(l)));
            }
            if(llst[r].enabled){
                section.addPath(ptsConv::pts2Path(lenr,true));

                //animate
                QPainterPath a = ptsConv::pts2Path(lenr,true);
                lensesitem[QString::number(id) + "." + QString::number(r)] = a;

                sect.appendChild(ptsConv::createElement("path",
                                                        ptsConv::pts2XML(lenr,true),
                                                        true,Qt::black,2,
                                                        true,Qt::darkGray,
                                                        true,QString::number(id) + "." + QString::number(r)));
            }
            //stock
            if(llst[m].enabled && llst[cw].enabled){
                section.addPath(ptsConv::pts2Path(stickpt0,false));
                section.addPath(ptsConv::pts2Path(stickpt1,false));

                //animate
                stoklens.addPath(ptsConv::pts2Path(stickpt0,false));
                stoklens.addPath(ptsConv::pts2Path(stickpt1,false));

                sect.appendChild(ptsConv::createElement("path",ptsConv::pts2XML(stickpt0,false),true,Qt::black,2));
                sect.appendChild(ptsConv::createElement("path",ptsConv::pts2XML(stickpt1,false),true,Qt::black,2));
            }
            if(llst[m].enabled && !llst[cw].enabled){
                section.addPath(ptsConv::pts2Path(stickpt1,false));

                //animate
                stoklens.addPath(ptsConv::pts2Path(stickpt1,false));

                sect.appendChild(ptsConv::createElement("path",ptsConv::pts2XML(stickpt1,false),true,Qt::black,2));
            }
            if(!llst[m].enabled && llst[cw].enabled){
                section.addPath(ptsConv::pts2Path(stickpt2,false));

                //animate
                stoklens.addPath(ptsConv::pts2Path(stickpt2,false));

                sect.appendChild(ptsConv::createElement("path",ptsConv::pts2XML(stickpt2,false),true,Qt::black,2));
            }
            //section nodes
            if(!sect.childNodes().isEmpty()){
                gsect.appendChild(sect);
            }
        }
        if(t == 1){
            if(llst[m].enabled){
                QVector<QPointF> ltram = {p0[0],p0[3],p2[3],p2[2],p1[2],p1[1],p3[2],p3[1],p3[0]};
                QVector<QPointF> stickpt = {QPointF(),(p1[2]+p1[1])/2};
                section.addPath(ptsConv::pts2Path(ltram,true));
                section.addPath(ptsConv::pts2Path(stickpt,false));

                section.addPath(ptsConv::pts2Circle(ll[m]->pos(),size/6));
                section.addPath(ptsConv::pts2Circle(ll[cw]->pos(),size/6));
                section.addPath(ptsConv::pts2Circle(ll[l]->pos(),size/6));
                section.addPath(ptsConv::pts2Circle(ll[r]->pos(),size/6));

                //animate
                QPainterPath a = ptsConv::pts2Circle(ll[m]->pos(),size/6);
                lensesitem[QString::number(id) + "." + QString::number(m)] = a;
                a = ptsConv::pts2Circle(ll[cw]->pos(),size/6);
                lensesitem[QString::number(id) + "." + QString::number(cw)] = a;
                a = ptsConv::pts2Circle(ll[l]->pos(),size/6);
                lensesitem[QString::number(id) + "." + QString::number(l)] = a;
                a = ptsConv::pts2Circle(ll[r]->pos(),size/6);
                lensesitem[QString::number(id) + "." + QString::number(r)] = a;
                stoklens.addPath(ptsConv::pts2Path(ltram,true));

                gsect.appendChild(ptsConv::createElement("path",
                                                         ptsConv::pts2XML(ltram,true),
                                                         true,Qt::black,2,
                                                         true,Qt::darkGray));

                gsect.appendChild(ptsConv::createCircle(QString::number(id) + "." + QString::number(m),
                                                        ll[m]->pos(),Qt::black,2,Qt::gray,size/5.5));
                gsect.appendChild(ptsConv::createCircle(QString::number(id) + "." + QString::number(cw),
                                                        ll[cw]->pos(),Qt::black,2,Qt::gray,size/5.5));
                gsect.appendChild(ptsConv::createCircle(QString::number(id) + "." + QString::number(l),
                                                        ll[l]->pos(),Qt::black,2,Qt::gray,size/5.5));
                gsect.appendChild(ptsConv::createCircle(QString::number(id) + "." + QString::number(r),
                                                        ll[r]->pos(),Qt::black,2,Qt::gray,size/5.5));

                gsect.appendChild(ptsConv::createElement("path",ptsConv::pts2XML(stickpt,false),true,Qt::black,2));

                //animate
                stoklens.addPath(ptsConv::pts2Path(stickpt,false));
            }
        }
    }

    //paint additional lenses
    QPainterPath lenses;
    QPainterPath stick;
    for(int i=0; i<almp.size(); ++i){
        QVector<QPointF> lll = {QPointF()};
        lll.append(almp[i]->blockline());

        QVector<QPointF> stickpt = geom::getBezie(lll);

        stick.addPath(ptsConv::pts2Path(stickpt,false));

        //animate
        stoklens.addPath(ptsConv::pts2Path(stickpt,false));

        gsect.appendChild(ptsConv::createElement("path",ptsConv::pts2XML(stickpt,false),true,Qt::black,2));

        QMap<int,QPointF> l = geom::getRect(almp[i]->pos(),geom::getABC(almp[i]->gl->pos() + almp[i]->pos(),almp[i]->pos()),size/2,true);
        QVector<QPointF> lb = geom::getBezie(l.values());
        lenses.addPath(ptsConv::pts2Path(lb,true));

        //animate
        QPainterPath a = ptsConv::pts2Path(lb,size/6);
        lensesitem[QString::number(id) + "." + QString::number(i+100)] = a;

        gsect.appendChild(ptsConv::createElement("path",
                                                ptsConv::pts2XML(lb,true),
                                                true,Qt::black,2,
                                                true,Qt::darkGray,
                                                true,QString::number(id) + ".a" + QString::number(i)));
    }
    section.addPath(stick);
    section.addPath(lenses);

    //animate
    stoklens.addPath(ptsConv::createCircleP());

    gsect.appendChild(ptsConv::createCircle());
    //manage shower
    if(enabled){
        for(int i=0; i<llst.size(); ++i){
            ll[i]->setVisible(llst[i].visbleState);
        }
    }
    //sections
    dom.appendChild(gsect);
    //full view lens
    skelet->setPath(section);
}

AddLamp *trafficlight::addLens(){
    almp.push_back(new AddLamp(this,almp.size()));
    connect(almp.last(),&AddLamp::updateAdditional,this,&trafficlight::setLLPosition);
    connect(almp.last(),&AddLamp::linkLight,this,&trafficlight::controlLight);
    connect(almp.last(),&AddLamp::deleteSelf,this,&trafficlight::deleteAddLamp);
    almp.last()->setVisibleGrabs(true);
    almp.last()->setDefaultPos(QPointF(80,-80));
    setLLPosition();
    return almp.last();
}

void trafficlight::editItem(){
    setVisibleState(true);
    emit editSelf(this);
}

void trafficlight::removeItem(){
    emit removeSelf(this);
}

void trafficlight::controlLight(int lid){
    emit linkLight(QString::number(id) + "." + QString::number(lid));
}

void trafficlight::deleteAddLamp(AddLamp *lmp){
    almp.removeOne(lmp);
    delete lmp;
    setLLPosition();
}

void trafficlight::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::red,2));
    QGraphicsPathItem::hoverEnterEvent(event);
}

void trafficlight::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    setPen(QPen(Qt::black));
    QGraphicsPathItem::hoverLeaveEvent(event);
}

void trafficlight::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mousePressEvent(event);
}

void trafficlight::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    setLLPosition();
    QGraphicsPathItem::mouseReleaseEvent(event);
}
