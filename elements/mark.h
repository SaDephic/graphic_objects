#ifndef MARK_H
#define MARK_H

#include <QPen>
#include <QBrush>
#include <QObject>
#include <QGraphicsPathItem>
#include <QFont>
#include <QDomDocument>
#include <QJsonObject>
#include <QMenu>
#include <QAction>

class grabMark: public QObject, public QGraphicsPathItem{
    Q_OBJECT

public: signals:
    void posChanged();//changed for repaint

public:
    grabMark(QGraphicsItem *parent);

private slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class mark : public QObject, public QGraphicsPathItem{
    Q_OBJECT

    bool enabled = false;//for edit

    //text view
    QColor color = Qt::black;
    QString text = "Метка";
    int size = 14;
    QString style = "Times Tew Roman";
    QGraphicsPathItem *gtext = nullptr;

    //for rotation text
    grabMark *gl = nullptr;

public:
    int id = -1;
    QMenu *menu = nullptr;//menu for manage
    QDomDocument dom;

signals:
    void removeSelf(mark *mrk);
    void editSelf(mark *mrk);

public:
    mark();
    void setPos(QPointF pos);
    void setVisibleState(bool state);
    QJsonObject json();
    void setjson(QJsonObject data);
    void setchanges(QJsonObject data);

    void setVisiblePot(bool state){
        if(state){
            QPainterPath path;
            path.addEllipse(QRectF(-4,-4,8,8));
            setPath(path);
            paintView();
        }else{
            gtext->setPath(QPainterPath());
            setPath(QPainterPath());
        }
    }

private slots:
    void paintView();
    void editItem();
    void removeItem();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MARK_H
