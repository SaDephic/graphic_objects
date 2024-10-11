#ifndef WPVIEW_H
#define WPVIEW_H

#include "wpscene.h"

#include <QGraphicsView>
#include <QMenu>
#include <QScrollBar>
#include <QWheelEvent>

class wpview : public QGraphicsView{
    Q_OBJECT

    bool mousePressed;
    int _panStartX;
    int _panStartY;

    QMenu *menu = nullptr;

public:
    wpscene *s = nullptr;

public:
    wpview(){
        setRenderHint(QPainter::Antialiasing);
        setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

        s = new wpscene;
        setScene(s);

        fitInView(sceneRect(), Qt::KeepAspectRatio);

        createMenu();
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this,&wpview::customContextMenuRequested,this,&wpview::showContextMenu);
    }

#ifdef QT_DEBUG
    void createTestElements(){
        gpoint *p = new gpoint(QPointF(20,20));
        s->addItem(p);

        gline *l = new gline(QPointF(40,20),QPointF(40,100));
        s->addItem(l);

        trafficlight *tl1 = new trafficlight(0);
        tl1->setPos(QPointF(180,180));
        s->addItem(tl1);

        trafficlight *tl2 = new trafficlight(1);
        tl2->setPos(QPointF(400,400));
        s->addItem(tl2);

        mark *m = new mark();
        m->setPos(QPointF(150,220));
        s->addItem(m);
    }
#endif

private:
    void createMenu(){
        QAction *act;
        menu = new QMenu;

        act = new QAction("Добавить узел");
        connect(act,&QAction::triggered,s,&wpscene::addNode);
        menu->addAction(act);

        menu->addSeparator();

        act = new QAction("Добавить транспортный светофор");
        connect(act,&QAction::triggered,s,&wpscene::addRTL);
        menu->addAction(act);

        act = new QAction("Добавить трамвайный светофор");
        connect(act,&QAction::triggered,s,&wpscene::addTTL);
        menu->addAction(act);

        act = new QAction("Добавить пешеходный переход");
        connect(act,&QAction::triggered,s,&wpscene::addCW);
        menu->addAction(act);

        menu->addSeparator();

        act = new QAction("Добавить камеру");
        connect(act,&QAction::triggered,s,&wpscene::addCM);
        menu->addAction(act);

        act = new QAction("Добавить метку");
        connect(act,&QAction::triggered,s,&wpscene::addMK);
        menu->addAction(act);

        menu->addSeparator();

        act = new QAction("Установить точку ПР/ЖМ/ОС/КК");
        connect(act,&QAction::triggered,s,&wpscene::setCenter);
        menu->addAction(act);
    }

private slots:
    void showContextMenu(const QPoint &pos){
        QGraphicsItem *it = itemAt(pos);
        if(it){
            gpoint *itpoint = dynamic_cast<gpoint*>(it);
            if(itpoint && !itpoint->middle){
                itpoint->menu->popup(mapToGlobal(pos));
                return;
            }
            gline *itline = dynamic_cast<gline*>(it);
            if(itline){
                itline->menu->popup(mapToGlobal(pos));
                return;
            }
            trafficlight *itraffic = dynamic_cast<trafficlight*>(it);
            if(itraffic){
                itraffic->menu->popup(mapToGlobal(pos));
                return;
            }
            cam *icam = dynamic_cast<cam*>(it);
            if(icam){
                icam->menu->popup(mapToGlobal(pos));
                return;
            }
            mark *imark = dynamic_cast<mark*>(it);
            if(imark){
                imark->menu->popup(mapToGlobal(pos));
                return;
            }
            crosswalk *icrosswalk = dynamic_cast<crosswalk*>(it);
            if(icrosswalk){
                icrosswalk->menu->popup(mapToGlobal(pos));
                return;
            }
        }
        if(s->centerPos() == QPointF())
            for(int i=0; i<menu->actions().size()-1; i++)
                menu->actions().at(i)->setEnabled(false);
        else
            for(int i=0; i<menu->actions().size()-1; i++)
                menu->actions().at(i)->setEnabled(true);

        menu->popup(mapToGlobal(pos));
    }

protected:
    void wheelEvent(QWheelEvent *event){
        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0){
            factor = 1.1;
        } else {
            factor = 0.9;
        }
        scale(factor, factor);
        setTransformationAnchor(anchor);
    }
    void mouseMoveEvent(QMouseEvent *event){
        if (mousePressed){
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->pos().x() - _panStartX));
            verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - _panStartY));

            _panStartX = event->pos().x();
            _panStartY = event->pos().y();
        }
        if(s->linkBusy()){
            s->updateLinker();
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseDoubleClickEvent(QMouseEvent *event){
        if(event->button() == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier){
            fitInView(s->sceneRect(), Qt::KeepAspectRatio);
        }
        QGraphicsView::mouseDoubleClickEvent(event);
    }

    void mousePressEvent(QMouseEvent *event){
        if(event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier){
            mousePressed = true;

            _panStartX = event->pos().x();
            _panStartY = event->pos().y();

            setCursor(Qt::ClosedHandCursor);
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event){
        mousePressed = false;
        setCursor(Qt::ArrowCursor);
        QGraphicsView::mouseReleaseEvent(event);
    }
};

#endif // WPVIEW_H
