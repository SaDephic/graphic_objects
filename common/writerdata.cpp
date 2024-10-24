#include "writerdata.h"
#include "custom/dep.h"
#include "common/filedir.h"

void writerdata::writeData(QString file, QByteArray ba){
    QFile f(file);
    if(f.open(QFile::WriteOnly)){
        f.write(ba);
        f.close();
    }
}

QByteArray writerdata::readData(QString file){
    QByteArray a;
    QFile f(file);
    if(f.open(QFile::ReadOnly)){
        a = f.readAll();
        f.close();
    }
    return a;
}

void writerdata::saveData(QString path){
    QFile f(path + QDir::separator() + file().t);
    if(f.open(QFile::WriteOnly)){
        QJsonDocument doc;
        doc.setObject(getData());
        f.write(doc.toJson());
        f.close();
    }
}

void writerdata::loadData(QString path){
    stash->clearData();//clear current stash data
    QFile f(path + QDir::separator() + file().t);
    if(f.open(QFile::ReadOnly)){
        setData(QJsonDocument::fromJson(f.readAll()).object());
        f.close();
    }
}

void writerdata::removeData(QString path){
    stash->clearData();
    QFile f(path + QDir::separator() + file().t);
    f.remove();
}

void writerdata::saveToLocal(QVector<int> rac, QString path, QByteArray m, QByteArray p, QByteArray e, QByteArray s){
    QString fp = path;
    for(int i=0; i<rac.size(); ++i){
        fp += QDir::separator() + QString::number(rac[i]);
        if(!QDir().exists(fp)){
            QDir().mkdir(fp);
        }
    }
    writeData(fp + QDir::separator() + file().m,m);
    writeData(fp + QDir::separator() + file().s,p);
    writeData(fp + QDir::separator() + file().e,e);
    writeData(fp + QDir::separator() + file().t,s);
}

QByteArray writerdata::svg(QByteArray map){
    QDomDocument dom;

    //map converting
    QPixmap pix;
    pix.loadFromData(map,"PNG");
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer, "PNG");
    auto const encoded = buffer.data().toBase64();

    //default pref
    QDomElement svg = dom.createElement("svg");
    svg.setAttribute("xlinkn","http://www.w3.org/1999/xlink");
    svg.setAttribute("xmlns","http://www.w3.org/2000/svg");
    svg.setAttribute("xmlns:xsl","http://www.w3.org/1999/XSL/Transform");
    svg.setAttribute("preserveAspectRatio","none");
    svg.setAttribute("shape-rendering","auto");
    svg.setAttribute("xmlns:xlink","http://www.w3.org/1999/xlink");
    svg.setAttribute("width",QString::number(pix.size().width()));
    svg.setAttribute("xmlns:svg","http://www.w3.org/2000/svg");
    svg.setAttribute("height",QString::number(pix.size().height()));
    svg.setAttribute("viewBox","0 0 " + QString::number(pix.size().width()) + " " + QString::number(pix.size().height()));

    //image
    QDomElement image = dom.createElement("image");
    image.setAttribute("x","0"); image.setAttribute("y","0");
    image.setAttribute("width",QString::number(pix.width()));
    image.setAttribute("height",QString::number(pix.height()));
    image.setAttribute("xlink:href","data:image/png;base64," + QString(encoded));
    svg.appendChild(image);


    QVector<QDomDocument> els = getDomElements();
    foreach (QDomDocument e, els) {
        svg.appendChild(e);
    }

    dom.appendChild(svg);
    return dom.toByteArray();
}

QByteArray writerdata::extend(){
    QJsonObject o;
    QJsonDocument jdoc(o);
    return jdoc.toJson();
}

bool writerdata::isEmptyTMP(QString path){
    QFile f(path + QDir::separator() + file().t);
    QFileInfo fi(f);
    if(fi.size()>(qint64)4)
        return false;
    return true;
}

bool writerdata::isEmptyCurrent(){
    QJsonDocument doc;
    doc.setObject(getData());
    QByteArray ba = doc.toJson();
    if(ba.size() > (qint64)4)
        return false;
    return true;
}

QJsonObject writerdata::getData(){
    QJsonObject data;
    stash->mid != QPointF()?data["m"] = dep::posToString(stash->mid) : QJsonValue();
    //head point
    if(!stash->vecpoint.isEmpty()){
        QJsonArray points;
        for(int i=0; i<stash->vecpoint.size(); i++){
            points.push_back(stash->vecpoint[i]->json());
        }
        data["pt"] = points;
    }
    //linkers
    if(!stash->vecline.isEmpty()){
        QJsonArray lines;
        for(int i=0; i<stash->vecline.size(); ++i){
            lines.push_back(stash->vecline[i]->json());
        }
        data["ab"] = lines;
    }
    //trafficlights
    if(!stash->vectraffic.isEmpty()){
        QJsonArray lights;
        for(int i=0; i<stash->vectraffic.size(); ++i){
            lights.push_back(stash->vectraffic[i]->json());
        }
        data["light"] = lights;
    }
    //cam
    if(!stash->veccam.isEmpty()){
        QJsonArray cams;
        for(int i=0; i<stash->veccam.size(); ++i){
            cams.push_back(stash->veccam[i]->json());
        }
        data["cam"] = cams;
    }
    //mark
    if(!stash->vecmark.isEmpty()){
        QJsonArray marks;
        for(int i=0; i<stash->vecmark.size(); ++i){
            marks.push_back(stash->vecmark[i]->json());
        }
        data["mark"] = marks;
    }
    //crosswalk
    if(!stash->vecwalk.isEmpty()){
        QJsonArray walks;
        for(int i=0; i<stash->vecwalk.size(); ++i){
            walks.push_back(stash->vecwalk[i]->json());
        }
        data["walk"] = walks;
    }
    if(!stash->vecmid.isEmpty()){
        QJsonArray mids;
        for(int i=0; i<stash->vecmid.size(); ++i){
            mids.push_back(stash->vecmid[i]->json());
        }
        data["mids"] = mids;
    }

    // link data
    if(!stash->sttable.isEmpty()){
        QJsonArray arr;
        for(int c=0; c<stash->sttable.size(); ++c){
            QJsonArray ra;
            for(int r=0; r<stash->sttable[c].size(); ++r){
                ra.push_back(stash->sttable[c][r]);
            }
            arr.push_back(ra);
        }
        data["mtx"] = arr;
    }

    return data;
}

void writerdata::setData(QJsonObject data){
    stash->mid = dep::posFromString(data["m"].toString());
    QJsonArray apts = data["pt"].toArray();
    for(int i=0; i<apts.size(); ++i){
        factory->getPoint()->setjson(apts[i].toObject());
    }
    QJsonArray alns = data["ab"].toArray();
    for(int i=0; i<alns.size(); ++i){
        QJsonObject o = alns[i].toObject();
        factory->getLine(factory->getPointById(o["b"].toInt()),
                         factory->getPointById(o["e"].toInt()))->setjson(o);
    }
    QJsonArray lts = data["light"].toArray();
    for (int i = 0; i < lts.size(); ++i) {
        QJsonObject o = lts[i].toObject();
        factory->getTrafficLight(QPointF(),o["type"].toInt())->setjson(o);
    }
    QJsonArray mks = data["mark"].toArray();
    for (int i = 0; i < mks.size(); ++i) {
        QJsonObject o = mks[i].toObject();
        factory->getMark()->setjson(o);
    }
    QJsonArray cms = data["cam"].toArray();
    for (int i = 0; i < cms.size(); ++i) {
        QJsonObject o = cms[i].toObject();
        factory->getCam()->setjson(o);
    }
    QJsonArray cws = data["walk"].toArray();
    for (int i = 0; i < cws.size(); ++i) {
        QJsonObject o = cws[i].toObject();
        factory->getCrossWalk()->setjson(o);
    }
    QJsonArray mds = data["mids"].toArray();
    for (int i = 0; i < mds.size(); ++i) {
        QJsonObject o = mds[i].toObject();
        factory->getMidRes(o["mid"].toInt())->v = o;
    }

    //link
    QJsonArray mtx = data["mtx"].toArray();
    for(int c=0; c<mtx.size(); ++c){
        QJsonArray ra = mtx[c].toArray();
        for(int r=0; r<ra.size(); ++r){
            stash->sttable[c][r] = ra[r].toInt();
        }
    }
}

QVector<QDomDocument> writerdata::getDomElements(){
    QVector<QDomDocument> data;
    data.push_back(stash->getCRTL());
    data.push_back(stash->getTTL());
    data.push_back(stash->getCW());
    data.push_back(stash->getCam());
    data.push_back(stash->getMK());
    return data;
}
