#ifndef AMID_H
#define AMID_H

#include <QObject>

#include "elements/simple/gpoint.h"
#include "elements/simple/line/gline.h"

class pt : public QObject, public QGraphicsEllipseItem{

    Q_OBJECT

public: signals:
    void posChanged();
    void hovered(bool state);

public:
    pt(QPointF pos = QPointF(), QGraphicsItem *parent = nullptr){
        setZValue(999);
        setParentItem(parent);

        setFlag(QGraphicsItem::ItemIsMovable);
        setAcceptHoverEvents(true);
        setPen(QPen(Qt::black));
        setRect(QRectF(-3,-3,6,6));

        setPos(pos);
    }

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
        emit posChanged();
        QGraphicsEllipseItem::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
        emit posChanged();
        QGraphicsEllipseItem::mouseReleaseEvent(event);
    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event){
        emit hovered(true);
        setPen(QPen(Qt::red,2));
        QGraphicsEllipseItem::hoverEnterEvent(event);
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
        emit hovered(false);
        setPen(QPen(Qt::black));
        QGraphicsEllipseItem::hoverLeaveEvent(event);
    }

};

class lr : public QObject, public QGraphicsPathItem{
    Q_OBJECT

public:
    pt *p0 = nullptr;
    pt *p1 = nullptr;

    gpoint *m = nullptr;
    gline *l = nullptr;
    gline *r = nullptr;

    QVector<QPointF> pts;
    QVector<QPointF> bpts;

public:
    lr(gpoint *_m,gline *_l,gline *_r,QGraphicsItem *parent = nullptr){
        setZValue(999);
        setParentItem(parent);
        setAcceptHoverEvents(true);

        m=_m;

        l=_l;
        r=_r;

        QPointF lp = lra().last();
        QPointF rp = lra().first();

        QPointF b = geom::getPointByLenght(rp,lp,geom::getLenght(lp,rp)*0.2);
        p0 = new pt(b,this);
        connect(p0,&pt::posChanged,this,&lr::repaintBords);

        QPointF e = geom::getPointByLenght(lp,rp,geom::getLenght(lp,rp)*0.2);
        p1 = new pt(e,this);
        connect(p1,&pt::posChanged,this,&lr::repaintBords);
    }
    ~lr(){
        delete p0;
        delete p1;
    }

    QVector<QPointF> lra(){
        if(l->getLRPT(m).isEmpty() || r->getLRPT(m).isEmpty()){
            return {l->getSUPT(m),r->getSUPT(m)};
        }
        return {l->getLRPT(m).last(),r->getLRPT(m).first()};
    }
    QVector<QPointF> lrb(){
        if(l->getBLRPT(m).isEmpty() || r->getBLRPT(m).isEmpty()){
            return {l->getSUPT(m),r->getSUPT(m)};
        }
        return {l->getBLRPT(m).last(),r->getBLRPT(m).first()};
    }

    QJsonObject json();
    void setjson(QJsonObject data);

public slots:
    void repaintBords(){
        if(!lra().isEmpty()){
            QPointF lp = lra()[0];
            QPointF rp = lra()[1];

            QVector<QPointF> line = {
                lp,
                p1->scenePos(),
                p0->scenePos(),
                rp
            };

            //setPath(ptsConv::pts2Path(geom::getBezie(line),false));
            pts = geom::getBezie(line);

            //***************************************
            QPointF blp = lrb()[0];
            QPointF brp = lrb()[1];

            QVector<QPointF> bline = {
                blp,
                p1->scenePos(),
                p0->scenePos(),
                brp
            };

            bpts = geom::getBezie(bline);
            //std::reverse(bpts.begin(),bpts.end());

            return;
        }
        setPath(QPainterPath());
    }
};

class amid : public QObject, public QGraphicsPathItem{
    Q_OBJECT

public:
    gpoint *m;
    QVector<gline*> sync;

    QGraphicsPathItem *bord = nullptr;

    //area
    QGraphicsPathItem *varea = nullptr;
    QGraphicsPathItem *vbord = nullptr;

    QColor p;

    QJsonObject v;

public: signals:
    void addItemToScene(QGraphicsItem *item);

private:
    QVector<lr*> blr;

public:
    amid(gpoint *gm){
        setFlag(QGraphicsItem::ItemIsFocusable,false);
        setFlag(QGraphicsItem::ItemIsSelectable,false);

        bord = new QGraphicsPathItem;
        bord->setPen(QPen(Qt::white,2));
        bord->setBrush(Qt::NoBrush);
        bord->setFlag(QGraphicsItem::ItemIsFocusable,false);
        bord->setFlag(QGraphicsItem::ItemIsSelectable,false);
        bord->setZValue(104);//road

        m = gm;

        varea = new QGraphicsPathItem;
        vbord = new QGraphicsPathItem;
    }
    amid(gpoint *gm, QVector<gline*> gsync);
    ~amid();

    void update_mid(QVector<gline*> gsync);
    bool containsLine(gline *l);
    void paintCurrentConfig();

    bool existSumid(gline *l, gline *r);

    QJsonObject json(){
        QJsonObject data;
        data["mid"] = (int)m->id;
        QJsonArray a;
        for(int i=0; i<blr.size(); ++i){
            a.push_back(blr[i]->json());
        }
        data["blr"] = a;
        return data;
    }
    void setjson(QJsonObject data) {
        QJsonArray a = data["blr"].toArray();
        for(int i=0; i<a.size(); ++i){
            QJsonObject o = a[i].toObject();
            for(int c=0; c<blr.size(); ++c){
                if(blr[c]->r->id == o["r"].toInt() && blr[c]->l->id == o["l"].toInt()){
                    blr[c]->setjson(o);
                }
            }
        }
    }

public slots:
    void colorHover(bool state);
};

#endif // AMID_H
