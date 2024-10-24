#include "stashdata.h"

QDomDocument stashdata::getCRTL(){
    QDomDocument doc;
    QDomElement el = doc.createElement("g");
    el.setAttribute("visibility","visible");
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
    el.setAttribute("visibility","visible");
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
    el.setAttribute("visibility","hidden");
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

void stashdata::hideManElements(bool state){
    for(int i=0; i<vecpoint.size(); ++i){
        vecpoint[i]->setVisible(state);
    }
    for(int i=0; i<vecwalk.size(); ++i){
        vecwalk[i]->setVisibleGarbs(state);
    }
    for(int i=0; i<vecmid.size(); ++i){
        vecmid[i]->setVisibleBords(state);
    }
    for(int i=0; i<vecline.size(); ++i){
        vecline[i]->setVisivbleSubs(state);
    }
    for(int i=0; i<veccam.size(); ++i){
        veccam[i]->setVisiblePot(state);
    }
    for(int i=0; i<vecmark.size(); ++i){
        vecmark[i]->setVisiblePot(state);
    }
    for(int i=0; i<vecwalk.size(); ++i){
        vecwalk[i]->setVisiblePot(state);
    }
    for(int i=0; i<vectraffic.size(); ++i){
        vectraffic[i]->setVisiblePot(state);
    }
    //close all visible elements by editors
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
    //mid areas
    while(!vecmid.isEmpty()){
        delete vecmid.takeFirst();
    }
    //clear matrix swap
    sttable.clear();
}

bool stashdata::containsMid(gpoint *p){
    for(int i=0; i<vecmid.size(); ++i){
        if(vecmid[i]->m == p){
            return true;
        }
    }
    return false;
}
