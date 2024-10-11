#ifndef LINKPTS_H
#define LINKPTS_H

#include "../gpoint.h"
#include "gline.h"

#include <QObject>
#include <QGraphicsPathItem>

class linkpts : public QObject, public QGraphicsPathItem{
    Q_OBJECT

    gpoint *b = nullptr;
    gpoint *e = nullptr;

public:
    linkpts();
    bool busy();
    void null();
    void startLink(gpoint *p);
    bool doneLink(gpoint *p);
    gline *getLink();
    void updateLink(QPointF pos);
};

#endif // LINKPTS_H
