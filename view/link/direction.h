#ifndef DIRECTION_H
#define DIRECTION_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>

#include "common/factorydata.h"
extern factorydata *factory;

class direction : public QWidget{
    Q_OBJECT

    int maxPhase = 8;
    int maxDirect = 20;

public:
    QTableWidget *tsw = nullptr;

public:
    direction(){
        QVBoxLayout *vl = new QVBoxLayout(this);

        QGroupBox *gb = new QGroupBox("Таблица состояний");
        gb->setMaximumWidth(400);

        QVBoxLayout *vlpb = new QVBoxLayout(gb);

        QPushButton *pb = nullptr;
        QHBoxLayout *h = nullptr;

        h = new QHBoxLayout;

        pb = new QPushButton("-Ф");
        connect(pb,&QPushButton::clicked,this,&direction::removeColPhase);
        pb->setMaximumWidth(50);
        h->addWidget(pb);

        pb = new QPushButton("+Ф");
        connect(pb,&QPushButton::clicked,this,&direction::addColPhase);
        pb->setMaximumWidth(50);
        h->addWidget(pb);

        vlpb->addLayout(h);

        h = new QHBoxLayout;

        pb = new QPushButton("-Н");
        connect(pb,&QPushButton::clicked,this,&direction::removeRowDirection);
        pb->setMaximumWidth(50);
        h->addWidget(pb);

        pb = new QPushButton("+Н");
        connect(pb,&QPushButton::clicked,this,&direction::addRowDirection);
        pb->setMaximumWidth(50);
        h->addWidget(pb);

        vlpb->addLayout(h);

        h = new QHBoxLayout;

        pb = new QPushButton("Очистить");
        connect(pb,&QPushButton::clicked,this,&direction::clearall);
        pb->setMaximumWidth(150);
        h->addWidget(pb);

        vlpb->addLayout(h);

        tsw = new QTableWidget;
        tsw->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tsw->setFocusPolicy(Qt::NoFocus);
        tsw->setSelectionMode(QAbstractItemView::NoSelection);
        vlpb->addWidget(tsw);

        vl->addWidget(gb);

        setMaximumWidth(300);
    }

    void loadMatrix(){
        //clear data
        while(tsw->rowCount()>0){
            tsw->removeRow(tsw->rowCount()-1);
        }
        while(tsw->columnCount()>0){
            tsw->removeColumn(tsw->columnCount()-1);
        }

        //clear data in stash
        if(!stash->sttable.isEmpty()){
            for(int c=0; c<stash->sttable.size(); ++c){
                tsw->insertColumn(tsw->columnCount());
            }

            for(int r=0; r<stash->sttable[0].size(); ++r){
                tsw->insertRow(tsw->rowCount());

                for(int c=0; c<tsw->columnCount(); ++c){
                    QPushButton *pb = new QPushButton();
                    pb->setMinimumSize(QSize(25,25));
                    pb->setProperty("r",r);
                    pb->setProperty("c",c);
                    tsw->setCellWidget(r,c,pb);
                }
            }

            for(int c=0; c<stash->sttable.size(); ++c){
                for(int r=0; r<stash->sttable[c].size(); ++r){
                    QPushButton *pb = dynamic_cast<QPushButton*>(tsw->cellWidget(r,c));
                    if(stash->sttable[c][r] == 0)
                        pb->setStyleSheet("background-color:gray");
                    if(stash->sttable[c][r] == 1)
                        pb->setStyleSheet("background-color:green");
                    if(stash->sttable[c][r] == 2)
                        pb->setStyleSheet("background-color:red");
                    connect(pb,&QPushButton::clicked,this,&direction::changeState);
                }
            }

            tsw->resizeColumnsToContents();
            tsw->resizeRowsToContents();
        }
    }

private slots:
    void addRowDirection(){
        if(tsw->rowCount() < maxDirect){
            tsw->insertRow(tsw->rowCount());

            for(int r=0; r<tsw->rowCount(); ++r){
                for(int c=0; c<tsw->columnCount(); ++c){
                    if(stash->sttable[c][r] != 0)
                        continue;

                    stash->sttable[c][r]=0;
                    QPushButton *pb = new QPushButton();
                    pb->setStyleSheet("background-color:gray");
                    pb->setMinimumSize(QSize(25,25));
                    connect(pb,&QPushButton::clicked,this,&direction::changeState);
                    pb->setProperty("r",r);
                    pb->setProperty("c",c);
                    tsw->setCellWidget(r,c,pb);
                }
            }

            tsw->resizeColumnsToContents();
            tsw->resizeRowsToContents();
        }
    }

    void removeRowDirection(){
        for(int i=0; i<tsw->columnCount(); ++i){
            stash->sttable[i].remove(tsw->rowCount()-1);
        }

        tsw->removeRow(tsw->rowCount()-1);
        tsw->resizeColumnsToContents();
        tsw->resizeRowsToContents();
    }

    void addColPhase(){
        if(tsw->columnCount() < maxPhase){
            tsw->insertColumn(tsw->columnCount());

            for(int c=0; c<tsw->columnCount(); ++c){
                for(int r=0; r<tsw->rowCount(); ++r){
                    if(stash->sttable[c][r] != 0)
                        continue;

                    stash->sttable[c][r] = 0;
                    QPushButton *pb = new QPushButton();
                    pb->setStyleSheet("background-color:gray");
                    pb->setMinimumSize(QSize(25,25));
                    connect(pb,&QPushButton::clicked,this,&direction::changeState);
                    pb->setProperty("r",r);
                    pb->setProperty("c",c);
                    tsw->setCellWidget(r,c,pb);
                }
            }

            tsw->resizeColumnsToContents();
            tsw->resizeRowsToContents();
        }
    }

    void removeColPhase(){
        stash->sttable.remove(tsw->columnCount()-1);

        tsw->removeColumn(tsw->columnCount()-1);
        tsw->resizeColumnsToContents();
        tsw->resizeRowsToContents();
    }

    void clearall(){
        while(tsw->rowCount()>0){
            tsw->removeRow(tsw->rowCount()-1);
        }
        while(tsw->columnCount()>0){
             tsw->removeColumn(tsw->columnCount()-1);
        }
        tsw->resizeColumnsToContents();
        tsw->resizeRowsToContents();

        stash->sttable.clear();
    }

    void changeState(){
        QPushButton *pb = dynamic_cast<QPushButton*>(sender());
        int r = pb->property("r").toInt();
        int c = pb->property("c").toInt();

        int current = stash->sttable[c][r];
        current++;

        if(current > 2){
            stash->sttable[c][r] = 0;
        }else{
            stash->sttable[c][r] = current;
        }

        if(stash->sttable[c][r] == 0){
            dynamic_cast<QPushButton*>(tsw->cellWidget(r,c))->setStyleSheet("background-color:gray");
        }
        if(stash->sttable[c][r] == 1){
            dynamic_cast<QPushButton*>(tsw->cellWidget(r,c))->setStyleSheet("background-color:green");
        }
        if(stash->sttable[c][r] == 2){
            dynamic_cast<QPushButton*>(tsw->cellWidget(r,c))->setStyleSheet("background-color:red");
        }
    }
};

#endif // DIRECTION_H
