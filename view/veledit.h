#ifndef VELEDIT_H
#define VELEDIT_H

#include "eledit/iolinesets.h"
#include "eledit/vcam.h"
#include "eledit/vmrk.h"
#include "eledit/vtl.h"

#include <QObject>

#include "elements/simple/line/gline.h"
#include "elements/cam.h"
#include "elements/mark.h"
#include "elements/trafficlight/trafficlight.h"

class veledit : public QObject{
    Q_OBJECT

public:
    IOLineSets *io = nullptr;
    vcam *cm = nullptr;
    vmrk *mk = nullptr;
    vtl *tl = nullptr;

    QJsonObject tmp;

    trafficlight *itl = nullptr;
    mark *imk = nullptr;
    cam *icm = nullptr;
    gline *ill = nullptr;

public:
    veledit();

public slots:
    void setIO(gline *item);
    void setCM(cam *item);
    void setMK(mark *item);
    void setTL(trafficlight *item);
    void hideAll();

private slots:
    void restore();

    void updateIO();
    void updateCM();
    void updateMK();
    void updateTL();
};

#endif // VELEDIT_H
