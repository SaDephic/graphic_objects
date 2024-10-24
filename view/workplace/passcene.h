#ifndef PASSCENE_H
#define PASSCENE_H

#include "common/factorydata.h"
extern factorydata *factory;

#include <QGraphicsScene>
#include <QBuffer>
#include <QGraphicsSceneMouseEvent>

class passcene : public QGraphicsScene{
    Q_OBJECT

    QGraphicsPathItem *sow = nullptr;
    QVector<QString> lsw = {"С","СЗ","З","ЮЗ","Ю","ЮВ","В","СВ"};

    QGraphicsPixmapItem *map = nullptr;

public:
    passcene(){
        sow = new QGraphicsPathItem;
        sow->setPen(QPen(Qt::red,2));
        sow->setFlag(QGraphicsItem::ItemIsSelectable,false);
        sow->setFlag(QGraphicsItem::ItemIsFocusable,false);
        addItem(sow);

        map = new QGraphicsPixmapItem;
        setMap(passcene::emptyMap());
        addItem(map);
    }
    ~passcene(){}

private:
    static QByteArray emptyMap(QSize size = QSize(450,450));

public slots:
    void setMap(QByteArray arr){
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
};

#endif // PASSCENE_H
