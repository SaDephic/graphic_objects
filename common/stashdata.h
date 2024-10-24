#ifndef STASHDATA_H
#define STASHDATA_H

#include "elements/ielements.h"
#include "elements/elements.h"

class stashdata : public QObject{
    Q_OBJECT

public: signals:
    void nullCenter();

public:
    stashdata(){}
    ~stashdata(){}

    QMap<int,QMap<int,int>> sttable;

    ielements id;
    QPointF mid;

    QVector<gpoint*> vecpoint;//100
    QVector<gline*> vecline;//99
    QVector<amid*> vecmid;

    //move els
    QVector<trafficlight*> vectraffic;//110
    QVector<cam*> veccam;//109
    QVector<mark*> vecmark;//108
    QVector<crosswalk*> vecwalk;//107

    //for svg generation
    QDomDocument getCRTL();
    QDomDocument getTTL();
    QDomDocument getCam();
    QDomDocument getMK();
    QDomDocument getCW();

    void hideManElements(bool state);

    void clearData();
    bool containsMid(gpoint *p);
};

#endif // STASHDATA_H
