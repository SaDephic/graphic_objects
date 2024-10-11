#ifndef GEOM_H
#define GEOM_H

#include <QPointF>
#include <QObject>
#include <QVariant>
#include <QPainterPath>
#include "math.h"

#define EPS 1e-9

class geom{
public:
    //bezie
    static int Fuctorial(int n);
    static double polinom(int i, int n, float t);
    static QVector<QPointF> getBezie(QVector<QPointF> nodes, float step = 0.05f);
    //a,b,c line
    struct abc{
        double a;
        double b;
        double c;
        abc getPerpendicular(QPointF pt);
        abc getDown(int len);
        abc getUp(int len);
    };
    //a,b,c coef line
    static abc getABC(QPointF b, QPointF e);
    //lenght line of points
    static double getLenght(QPointF b, QPointF e);
    //masslenght
    static double getLenghtMass(QVector<QPointF> l);
    //point of b->e with lenght
    static QPointF getPointByLenght(QPointF b, QPointF e, double len);
    //angle line
    static int getAngle(QPointF cent, QPointF to);
    //angle line radian
    static double getAngleRad(QPointF cent, QPointF to);
    //intersect line+line
    static QPointF getIntLL(abc l1, abc l2);
    //intersect line+line cat point
    static QPointF getIntLLcat(QPointF p00, QPointF p01, QPointF p10, QPointF p11);
    //intersect line+line point [line for cut and cut line]
    static QVector<QVector<QPointF>> getIntLLs(QVector<QPointF> cur, QVector<QPointF> drob);
    //intersect line+line point [line for cut and cut line]
    static QPointF getIntLLPoint(QVector<QPointF> cur, QVector<QPointF> drob);
    //get parallel line
    struct dataPoints{
        QPointF before;
        QPointF current;
        QPointF next;
        QPointF result;
        void setResult(double len, bool updwn = false);
    };
    static QVector<QPointF> getParralelLine(QVector<QPointF> _data, double cut, bool UpDwn);
    //rect point
    static QMap<int, QPointF> getRect(QPointF pts, abc base, int size, bool cw = false);
    //rect point
    static QMap<int, QPointF> getRectLen(QPointF pts, abc base, int size);
    //point of angle and lenght
    static QPointF getPointOfAngle(QPointF bp, int l, double angle);
    //get arrow points by begin and end pts + len
    static QVector<QPointF> getArrowPTS(QPointF begin, QPointF end, int arrlen);
};

#include <QDomDocument>
#include <QDomElement>
#include <QColor>
class ptsConv{
public:
    //object xml
    static QDomDocument createElement(QString typeel = QString(),
                                      QString line = QString(),
                                      bool pen = false,QColor pencolor = Qt::black,int pensize = 1,
                                      bool fill = false,QColor fillcolor = Qt::black,
                                      bool ident = false,QString id = QString());
    //circle
    static QDomDocument createCircle(QString id = QString("-1"),QPointF pos = QPointF(), QColor pen = Qt::black, int size = 2, QColor brush = Qt::white, int radius = 3);
    static QPainterPath createCircleP(double r = 3);
    //line to text for SVG element
    static QString pts2XML(QVector<QPointF> lpts, bool cycle);
    //paht line
    static QPainterPath pts2Path(QVector<QPointF> lpts, bool cycle);
    static QPainterPath pts2Circle(QPointF pos, int size);
    static QDomDocument getCenterState(QPointF pos);
    static QPainterPath getArrow(QPointF begin, QPointF end, int arrlen);
};

class roadLen{
public:
    static bool evenLines(int in, int out);
    //size middle and base line
    static QVector<QVector<QPointF>> getMidLine(int size, QVector<QPointF> bline);
    //int counter - line counter
    //QVector<QPointF> bline - basic line
    //int midsp - mid space
    //int len - size line
    //bool even - even/not even countlines
    //bool type - duo/signle directions
    //bool inout - input/output directions
    static QVector<QPointF> getLine(int counter, QVector<QPointF> bline, int midsp, int len, bool inout, int add = 0);
};

#endif // GEOM_H
