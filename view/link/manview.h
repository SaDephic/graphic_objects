#ifndef MANVIEW_H
#define MANVIEW_H

#include <QWidget>
#include "direction.h"
#include "view/workplace/pasview.h"

class manview : public QWidget{
    Q_OBJECT

public:
    direction *direct = nullptr;
    pasview *l = nullptr;

public:
    manview(){
        direct = new direction;
        l = new pasview;
        QHBoxLayout *hl = new QHBoxLayout(this);
        hl->addWidget(direct);
        hl->addWidget(l);
    }
    ~manview(){}
};

#endif // MANVIEW_H
