#include "pasview.h"


pasview::pasview(){
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

    s = new passcene;
    setScene(s);

    fitInView(sceneRect(), Qt::KeepAspectRatio);
}

pasview::~pasview(){}

void pasview::wheelEvent(QWheelEvent *event){
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

void pasview::mouseMoveEvent(QMouseEvent *event){
    if (mousePressed){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->pos().x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - _panStartY));

        _panStartX = event->pos().x();
        _panStartY = event->pos().y();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void pasview::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && event->modifiers() == Qt::ShiftModifier){
        fitInView(s->sceneRect(), Qt::KeepAspectRatio);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void pasview::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier){
        mousePressed = true;

        _panStartX = event->pos().x();
        _panStartY = event->pos().y();

        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void pasview::mouseReleaseEvent(QMouseEvent *event){
    mousePressed = false;
    setCursor(Qt::ArrowCursor);
    QGraphicsView::mouseReleaseEvent(event);
}
