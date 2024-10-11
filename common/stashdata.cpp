#include "stashdata.h"

QDomDocument stashdata::getCRTL(){
    QDomDocument doc;
    QDomElement el = doc.createElement("g");
    el.setAttribute("id","RT");
    for(int i=0; i<vectraffic.size(); ++i)
        if(vectraffic[i]->t == 0)
            el.appendChild(vectraffic[i]->dom);
    doc.appendChild(el);
    return doc;
}

QDomDocument stashdata::getTTL(){
    QDomDocument doc;
    QDomElement el = doc.createElement("g");
    el.setAttribute("id","TT");
    for(int i=0; i<vectraffic.size(); ++i)
        if(vectraffic[i]->t == 1)
            el.appendChild(vectraffic[i]->dom);
    doc.appendChild(el);
    return doc;
}

QDomDocument stashdata::getCam(){
    QDomDocument doc;
    QDomElement el = doc.createElement("g");
    el.setAttribute("id","CM");
    for(int i=0; i<veccam.size(); ++i)
        el.appendChild(veccam[i]->dom);
    doc.appendChild(el);
    return doc;
}

QDomDocument stashdata::getMK(){
    QDomDocument doc;
    QDomElement el = doc.createElement("g");
    el.setAttribute("id","MK");
    for(int i=0; i<vecmark.size(); ++i)
        el.appendChild(vecmark[i]->dom);
    doc.appendChild(el);
    return doc;
}

QDomDocument stashdata::getCW(){
    QDomDocument doc;
    QDomElement el = doc.createElement("g");
    el.setAttribute("id","CW");
    for(int i=0; i<vecwalk.size(); ++i)
        el.appendChild(vecwalk[i]->dom);
    doc.appendChild(el);
    return doc;
}

void stashdata::clearData(){
    emit nullCenter();
    //point
    while(!vecpoint.isEmpty()){
        emit vecpoint.first()->removeSelf(vecpoint.first());
    }
    //link line
    while(!vecline.isEmpty()){
        emit vecline.first()->removeSelf(vecline.first());
    }
    //traffic/tramway light
    while(!vectraffic.isEmpty()){
        emit vectraffic.first()->removeSelf(vectraffic.first());
    }
    //camera
    while(!veccam.isEmpty()){
        emit veccam.first()->removeSelf(veccam.first());
    }
    //on road text
    while(!vecmark.isEmpty()){
        emit vecmark.first()->removeSelf(vecmark.first());
    }
    //crosswalk
    while(!vecwalk.isEmpty()){
        emit vecwalk.first()->removeSelf(vecwalk.first());
    }
}
