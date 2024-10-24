#ifndef PASVIEW_H
#define PASVIEW_H

#include "passcene.h"

#include <QGraphicsView>
#include <QMenu>
#include <QScrollBar>
#include <QWheelEvent>

class pasview : public QGraphicsView{
    Q_OBJECT

    bool mousePressed;
    int _panStartX;
    int _panStartY;

public:
    passcene *s = nullptr;

public:
    pasview();
    ~pasview();

protected:
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // PASVIEW_H
