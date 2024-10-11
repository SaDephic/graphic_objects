#include "veledit.h"

veledit::veledit(){
    io = new IOLineSets;
    cm = new vcam;
    mk = new vmrk;
    tl = new vtl;

    connect(io,&IOLineSets::updateView,this,&veledit::updateIO);
    connect(cm,&vcam::updateView,this,&veledit::updateCM);
    connect(mk,&vmrk::updateView,this,&veledit::updateMK);
    connect(tl,&vtl::updateView,this,&veledit::updateTL);

    connect(io,&IOLineSets::closed,this,&veledit::hideAll);
    connect(cm,&vcam::closed,this,&veledit::hideAll);
    connect(mk,&vmrk::closed,this,&veledit::hideAll);
    connect(tl,&vtl::closed,this,&veledit::hideAll);

    connect(io,&IOLineSets::restore,this,&veledit::restore);
    connect(cm,&vcam::restore,this,&veledit::restore);
    connect(mk,&vmrk::restore,this,&veledit::restore);
    connect(tl,&vtl::restore,this,&veledit::restore);
}

void veledit::setIO(gline *item){
    if(ill != item)
        hideAll();
    ill = item;
    io->setVisible(true);
    //sets data
    tmp = item->json();
    io->setData(tmp);

    io->show();
}

void veledit::setCM(cam *item){
    if(icm != item)
        hideAll();
    icm = item;
    cm->setVisible(true);
    //sets data
    tmp = item->json();
    cm->setData(tmp);

    cm->show();
}

void veledit::setMK(mark *item){
    if(imk != item)
        hideAll();
    imk = item;
    mk->setVisible(true);
    //sets data
    tmp = item->json();
    mk->setData(tmp);

    mk->show();
}

void veledit::setTL(trafficlight *item){
    if(itl != item)
        hideAll();
    itl = item;
    tl->setVisible(true);
    //sets data
    tmp = item->json();
    tl->setData(tmp);

    tl->show();
}

void veledit::restore(){
    if(itl){
        itl->setchanges(tmp);
    }
    if(imk){
        imk->setchanges(tmp);
    }
    if(icm){
        icm->setchanges(tmp);
    }
    if(ill){
        ill->setchanges(tmp);
    }
}

void veledit::updateIO(){
    ill->setchanges(io->current);
}

void veledit::updateCM(){
    icm->setchanges(cm->current);
}

void veledit::updateMK(){
    imk->setchanges(mk->current);
}

void veledit::updateTL(){
    itl->setchanges(tl->current);
}

void veledit::hideAll(){
    tl->hide();
    if(itl){
        itl->setVisibleState(false);
        itl = nullptr;
    }
    mk->hide();
    if(imk){
        imk->setVisibleState(false);
        imk = nullptr;
    }
    cm->hide();
    if(icm){
        icm->setVisibleState(false);
        icm = nullptr;
    }
    io->hide();
    if(ill){
        ill = nullptr;
    }
}
