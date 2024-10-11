#ifndef CAM_H
#define CAM_H

#include <QPen>
#include <QBrush>
#include <QObject>
#include <QGraphicsPathItem>
#include <QFont>
#include <QDomDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMenu>
#include <QAction>

class grabCam: public QObject, public QGraphicsPathItem{
    Q_OBJECT

public: signals:
    void posChanged();//changed for repaint

public:
    grabCam(QGraphicsItem *parent, int t = 0);

private slots:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

class cam: public QObject, public QGraphicsPathItem{
    Q_OBJECT
    bool enabled = false;//for edit

    //text view
    QColor color = Qt::black;
    int camsize = 14;
    QString text = "Камера";
    QString style = "Times New Roman";
    int textsize = 14;
    QString url = QString();
    QString stop = QString();
    QString up = QString();
    QString down = QString();
    QString left = QString();
    QString right = QString();

    QGraphicsPathItem *gtext = nullptr;
    QGraphicsPathItem *garea = nullptr;
    grabCam *direct = nullptr;
    QVector<grabCam*> area;

public:
    int id = -1;
    QMenu *menu = nullptr;//menu for manage
    QDomDocument dom;

signals:
    void removeSelf(cam *mrk);
    void editSelf(cam *mrk);
public:
    cam();
    ~cam();

    void setPos(QPointF pos);
    void setVisibleState(bool state);

    QJsonObject json();
    void setjson(QJsonObject data);
    void setchanges(QJsonObject data);

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

#endif // CAM_H
