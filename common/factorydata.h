#ifndef FACTORYDATA_H
#define FACTORYDATA_H

#include "common/stashdata.h"
extern stashdata *stash;

#include "view/veledit.h"

class factorydata : public QObject{
    Q_OBJECT

public:
    veledit *vel = nullptr;;

public:
    factorydata();

    void addPoint(gpoint *p);
    void addLine(gline *l);
    void addTrafficLight(trafficlight *t);
    void addMark(mark* m);
    void addCam(cam* c);
    void addCrosswalk(crosswalk* c);
    void addMid(amid *m);

    gpoint *getPoint(QPointF pos = QPointF());
    gpoint *getPointById(int id);
    gline *getLine(gpoint *b, gpoint *e);
    trafficlight *getTrafficLight(QPointF pos, int t = 0);
    cam *getCam(QPointF pos = QPointF());
    mark *getMark(QPointF pos = QPointF());
    crosswalk *getCrossWalk(QPointF pos = QPointF());
    amid *getMidRes(int idmid);
    amid *getMid(gpoint *p);

public slots:
    void removeLine(gline *l);
    void removePoint(gpoint *p);
    void removeTrafficlight(trafficlight *t);
    void removeMark(mark *m);
    void removeCam(cam *c);
    void removeCrosswalk(crosswalk *c);

private:
    void removeLinkedLines(gpoint *p);
};

#endif // FACTORYDATA_H
