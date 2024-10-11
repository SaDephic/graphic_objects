#include "geom.h"

int geom::Fuctorial(int n){
    int res = 1;
    for (int i=1; i<=n; i++)
        res *= i;
    return res;
}

double geom::polinom(int i, int n, float t){
    return (Fuctorial(n)/(Fuctorial(i)*Fuctorial(n-i)))*pow(t,i)*pow(1-t,n-i);
}

QVector<QPointF> geom::getBezie(QVector<QPointF> nodes, float step){
    if(nodes.isEmpty())
        return QVector<QPointF>();
    QVector<QPointF> result;
    for(float t=0; t<1; t+=step){
        double ytmp = 0;
        double xtmp = 0;
        for (int i = 0; i < nodes.size(); i++){
            double b = polinom(i, nodes.size() - 1, t);
            xtmp += nodes[i].x()*b;
            ytmp += nodes[i].y()*b;
        }
        result.append(QPointF(xtmp, ytmp));
    }
    result.append(nodes.last());
    return result;
}

geom::abc geom::getABC(QPointF b, QPointF e){
    return{b.y()-e.y(),e.x()-b.x(),(b.x()*e.y())-(e.x()*b.y())};
}

double geom::getLenght(QPointF b, QPointF e){
    return abs(sqrt(((e.y()-b.y())*(e.y()-b.y()))+((e.x()-b.x())*(e.x()-b.x()))));
}

double geom::getLenghtMass(QVector<QPointF> l){
    double len = 0.0;
    QPointF b = l.takeFirst();
    for(int i=0; i<l.size(); ++i){
        len += getLenght(b,l[i]);
        b = l[i];
    }
    return len;
}

QPointF geom::getPointByLenght(QPointF b, QPointF e, double len){
    return e+(b-e)*(len/getLenght(b,e));
}

int geom::getAngle(QPointF cent, QPointF to){
    int angle = 0;
    QPointF r = to - cent;
    double pi = 3.1415926535;
    angle = atan2(r.y(), r.x()) * 180/pi;
    angle = angle + ((angle < 0) ? 360 : 0);
    return angle;
}

double geom::getAngleRad(QPointF cent, QPointF to){
    QPointF r = to - cent;
    return atan2(r.y(), r.x());
}

QPointF geom::getIntLL(abc l1, abc l2){
    double DivXY = l1.a*l2.b-l2.a*l1.b;
    if(DivXY == 0.0) {
        return QPointF(double(),double());
    }else{
        double x=(l1.b*l2.c-l2.b*l1.c)/DivXY;
        double y=(l1.c*l2.a-l2.c*l1.a)/DivXY;
        return QPointF(x,y);
    }
}

QPointF geom::getIntLLcat(QPointF p00, QPointF p01, QPointF p10, QPointF p11){
    abc ol0 = getABC(p00,p01);
    abc tl1 = getABC(p10,p11);

    double DivXY = ol0.a*tl1.b-tl1.a*ol0.b;
    if(DivXY == 0.0) {
        return QPointF(double(),double());
    }else{
        double x=(ol0.b*tl1.c-tl1.b*ol0.c)/DivXY;
        double y=(ol0.c*tl1.a-tl1.c*ol0.a)/DivXY;

        double rx0 = (x-p00.x())/(p01.x()-p00.x());
        double ry0 = (y-p00.y())/(p01.y()-p00.y());
        double rx1 = (x-p10.x())/(p11.x()-p10.x());
        double ry1 = (y-p10.y())/(p11.y()-p10.y());

        if(((rx0>=0&&rx0<=1)||(ry0>=0&&ry0<=1))&&((rx1>=0&&rx1<=1)||(ry1>=0&&ry1<=1))){
            return QPointF(x,y);
        }else return QPointF(double(),double());
    }
}

QVector<QVector<QPointF> > geom::getIntLLs(QVector<QPointF> cur, QVector<QPointF> drob){
    QVector<QPointF> before;
    QVector<QPointF> after;

    bool state = false;
    for(int i=1; i<cur.size(); i++){
        if(!state){
            before.append(cur[i-1]);
            for(int c=1;c<drob.size();c++){
                QPointF recheck = getIntLLcat(cur[i-1],cur[i],drob[c-1],drob[c]);
                if(recheck != QPointF(double(),double())){
                    state = true;
                    before.append(recheck);
                    after.append(recheck);
                    break;
                }
            }
        }else{
            after.append(cur[i]);
        }
    }
    return {before,after};
}

QPointF geom::getIntLLPoint(QVector<QPointF> cur, QVector<QPointF> drob){
    QPointF pt;
    bool state = false;
    for(int i=1; i<cur.size(); i++){
        if(!state){
            for(int c=1;c<drob.size();c++){
                QPointF recheck = getIntLLcat(cur[i-1],cur[i],drob[c-1],drob[c]);
                if(recheck != QPointF(double(),double())){
                    state = true;
                    pt = recheck;
                    break;
                }
            }
        }
    }
    return pt;
}

QVector<QPointF> geom::getParralelLine(QVector<QPointF> _data, double cut, bool UpDwn){
    QVector<dataPoints> data;

    QVector<QPointF> _datatmp = _data;
    foreach(QPointF _cur, _datatmp){
        dataPoints currentData;
        currentData.current = _cur;
        data.append(currentData);
    }

    QPointF mem;
    for(int i=0; i<_datatmp.size(); i++){
        if(_datatmp[i] == _datatmp.first()){
            mem = _datatmp[i];
        }else{
            data[i].before = mem;
            mem = _datatmp[i];
        }
    }

    for(int k=0, s=data.size(), max=(s/2); k<max; k++) data.swapItemsAt(k,s-(1+k));
    for(int k=0, s=_datatmp.size(), max=(s/2); k<max; k++) _datatmp.swapItemsAt(k,s-(1+k));

    for(int i=0; i<_datatmp.size(); i++){
        if(_datatmp[i] == _datatmp.first()){
            mem = _datatmp[i];
        }else{
            data[i].next = mem;
            mem = _datatmp[i];
        }
    }

    for(int k=0, s=data.size(), max=(s/2); k<max; k++) data.swapItemsAt(k,s-(1+k));

    QVector<QPointF> _retred;
    foreach(dataPoints _cur, data){
        _cur.setResult(cut,UpDwn);
        if(_cur.result != QPointF())
            _retred.append(_cur.result);
    }
    return _retred;
}

QMap<int, QPointF> geom::getRect(QPointF pts, abc base, int size, bool cw){
    abc pbase = base.getPerpendicular(pts);
    abc top;
    abc bot;
    if(cw){
        top = pbase.getUp(size*0.6);
        bot = pbase.getDown(size*0.6);
    }else{
        top = pbase.getUp(size*0.8);
        bot = pbase.getDown(size*0.8);
    }
    abc left = base.getUp(size);
    abc right = base.getDown(size);
    return {
        {0,getIntLL(top,right)},//R
        {1,getIntLL(bot,right)},//BR
        {2,getIntLL(bot,left)},//BL
        {3,getIntLL(top,left)}//L
    };
}

QMap<int, QPointF> geom::getRectLen(QPointF pts, abc base, int size){
    abc pbase = base.getPerpendicular(pts);
    abc top = pbase.getUp(size*0.7);
    abc bot = pbase.getDown(size*0.7);
    abc left = base.getUp(size*0.6);
    abc right = base.getDown(size*0.6);
    return {
        {0,getIntLL(top,right)},//R
        {1,getIntLL(bot,right)},//BR
        {2,getIntLL(bot,left)},//BL
        {3,getIntLL(top,left)}//L
    };
}

QPointF geom::getPointOfAngle(QPointF bp, int l, double angle){
    return QPointF(bp.x() + l*cos(angle),bp.y() + l*sin(angle));
}

QVector<QPointF> geom::getArrowPTS(QPointF begin, QPointF end, int arrlen){
    QVector<QPointF> pts;
    QPointF mid = getPointByLenght(begin,end,arrlen);
    abc _this = getABC(begin,end);
    abc pp_this = _this.getPerpendicular(mid);
    QPointF p0 = getIntLL(pp_this,_this.getUp(arrlen/2));
    QPointF p1 = getIntLL(pp_this,_this.getDown(arrlen/2));
    pts = {mid,p0,end,p1,mid};
    return pts;
}

QDomDocument ptsConv::createElement(QString typeel, QString line, bool pen, QColor pencolor, int pensize, bool fill, QColor fillcolor, bool ident, QString id){
    QDomDocument dom;

    QDomElement rootElement = dom.createElement(typeel);
    rootElement.setAttribute("d",line);

    if(ident){
        rootElement.setAttribute("id",id);
    }
    if(fill){
        rootElement.setAttribute("fill",fillcolor.name());
    }else{
        rootElement.setAttribute("fill","none");
    }
    if(pen){
        rootElement.setAttribute("stroke-width",QString::number(pensize));
        rootElement.setAttribute("stroke",pencolor.name());
    }

    dom.appendChild(rootElement);

    return dom;
}

QDomDocument ptsConv::createCircle(QString id, QPointF pos, QColor pen, int size, QColor brush, int radius){
    QDomDocument dom;
    QDomElement el = dom.createElement("circle");
    el.setAttribute("id",id);
    el.setAttribute("cx",pos.x());
    el.setAttribute("cy",pos.y());
    el.setAttribute("r",radius);
    el.setAttribute("stroke",pen.name());
    el.setAttribute("stroke-width",size);
    el.setAttribute("fill",brush.name());
    dom.appendChild(el);
    return dom;
}

QPainterPath ptsConv::createCircleP(double r){
    QPainterPath p;
    p.addEllipse(QRectF(-r/2,-r/2,r,r));
    return p;
}

QString ptsConv::pts2XML(QVector<QPointF> lpts, bool cycle){
    QString res = QString();
    if(!lpts.isEmpty()){
        res = QString("M %1,%2").arg(QString::number(lpts.first().toPoint().x()),
                                     QString::number(lpts.first().y()));
        for(int i=1; i<lpts.size(); ++i){
            res += QString(" L %1,%2").arg(QString::number(lpts[i].x()),
                                           QString::number(lpts[i].y()));
        }
        if(cycle){
            res += QString(" L %1,%2").arg(QString::number(lpts.first().x()),
                                           QString::number(lpts.first().y()));
        }
    }
    return res;
}

QPainterPath ptsConv::pts2Path(QVector<QPointF> lpts, bool cycle){
    QPainterPath path;
    if(!lpts.isEmpty()){
        path.moveTo(lpts.first().toPoint());
        for(int i=1; i<lpts.size(); ++i){
            path.lineTo(lpts[i].toPoint());
        }
        if(cycle){
            path.lineTo(lpts.first().toPoint());
        }
    }
    return path;
}

QPainterPath ptsConv::pts2Circle(QPointF pos, int size){
    QPainterPath path;
    path.addEllipse(pos,size,size);
    return path;
}

QDomDocument ptsConv::getCenterState(QPointF pos){
    QDomDocument dom;
    QDomElement g = dom.createElement("g");
    g.setAttribute("id","self-phase");
    g.setAttribute("visibility","hidden");
    g.setAttribute("transform","translate(" + QVariant(pos.x()).toString() + "," + QVariant(pos.y()).toString() + ")");
    QDomElement circle = dom.createElement("circle");
    circle.setAttribute("id","self-phase-back");
    circle.setAttribute("stroke-width","3");
    circle.setAttribute("stroke","black");
    circle.setAttribute("r","16");
    g.appendChild(circle);
    QDomElement text = dom.createElement("text");
    text.setAttribute("id","self-phase-text");
    text.setAttribute("text-anchor","middle");
    text.setAttribute("x","0");
    text.setAttribute("y","4");
    text.setAttribute("font-size","13");
    g.appendChild(text);
    dom.appendChild(g);
    return dom;
}

QPainterPath ptsConv::getArrow(QPointF begin, QPointF end, int arrlen){
    QPainterPath path = QPainterPath();

    QPointF mid = geom::getPointByLenght(begin,end,arrlen);
    geom::abc _this = geom::getABC(begin,end);
    geom::abc pp_this = _this.getPerpendicular(mid);
    QPointF p0 = geom::getIntLL(pp_this,_this.getUp(arrlen/2));
    QPointF p1 = geom::getIntLL(pp_this,_this.getDown(arrlen/2));

    path.moveTo(mid);
    path.lineTo(p0);
    path.lineTo(end);
    path.lineTo(p1);
    path.lineTo(mid);
    return path;
}

geom::abc geom::abc::getPerpendicular(QPointF pt){
    return{-b,a,-a*pt.y()+b*pt.x()};
}

geom::abc geom::abc::getDown(int len){
    return{a,b,c+len*sqrt(a*a+b*b)};
}

geom::abc geom::abc::getUp(int len){
    return{a,b,c-len*sqrt(a*a+b*b)};
}

bool roadLen::evenLines(int in, int out){
    if((in+out)&1){//not event
        return false;
    }else{//even
        return true;
    }
    return false;
}

QVector<QVector<QPointF> > roadLen::getMidLine(int size, QVector<QPointF> bline){
    QVector<QPointF> l = geom::getParralelLine(bline,size/2,false);
    QVector<QPointF> r = geom::getParralelLine(bline,size/2,true);
    return {l,r};
}

QVector<QPointF> roadLen::getLine(int counter, QVector<QPointF> bline, int midsp, int len, bool inout, int add){
    //split size mid line
    int midlen = midsp/2;
    //result line
    QVector<QPointF> line;
    //input and output directions
    line = geom::getParralelLine(bline,midlen + counter*len + add,inout);
    return line;
}

void geom::dataPoints::setResult(double len, bool updwn){
    if(before == QPointF()){
        abc _vec = getABC(next,current);
        if(updwn)
            result = getIntLL(_vec.getUp(len),_vec.getPerpendicular(current));
        else{
            result = getIntLL(_vec.getDown(len),_vec.getPerpendicular(current));
        }
    }
    if(next == QPointF()){
        abc _vec = getABC(before,current);
        if(!updwn)
            result = getIntLL(_vec.getUp(len),_vec.getPerpendicular(current));
        else{
            result = getIntLL(_vec.getDown(len),_vec.getPerpendicular(current));
        }
    }
    if((next != QPointF())&&(before != QPointF())){
        abc _vecB = getABC(before,current);
        if(!updwn){
            result = getIntLL(_vecB.getUp(len),_vecB.getPerpendicular(current));
        }else{
            result = getIntLL(_vecB.getDown(len),_vecB.getPerpendicular(current));
        }
    }
}
