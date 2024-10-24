#ifndef TEST_SPACE_H
#define TEST_SPACE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QTabWidget>

#include "custom/dialog.h"

#include "view/workplace/wpview.h"
#include "view/link/manview.h"
#include "common/crossdata.h"

#include "common/writerdata.h"
#include "auth/stateauth.h"
#include "custom/sysenv.h"

extern writerdata *writer;
extern stateauth *aut;
extern sysenv *se;

class test_space : public QMainWindow{
    Q_OBJECT

    crossdata cd;
    QTabWidget *tab = nullptr;
    wpview *v = nullptr;
    manview *l = nullptr;
    QWidget *w= nullptr;

public: signals:
    void logout();

public:
    test_space();
    ~test_space();

private:
    void createMenu();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    //bottom - png
    //picture - svg
    //extend - расширенные
    //state - шаблон
    void saveCurrentData();
    void saveHowObject();
    void loadCrossData();
    void setCurrentCross();
    void changeCrossBackMap();
    void openObject();

    void showPermissions();
    void swapuser();

    void changedTab(int indx){
        if(indx == 0){
            for(int i=0; i<stash->vectraffic.size(); ++i){
                if(!v->s->items().contains(stash->vectraffic[i])){
                    stash->vectraffic[i]->setVisibleSpot(true);
                    v->s->addItem(stash->vectraffic[i]);
                }
            }
        }
        if(indx == 1){
            l->l->s->setMap(v->s->getMapStruct());
            for(int i=0; i<stash->vectraffic.size(); ++i){
                if(!l->l->s->items().contains(stash->vectraffic[i])){
                    stash->vectraffic[i]->setVisibleSpot(false);
                    l->l->s->addItem(stash->vectraffic[i]);
                }
            }
        }
    }
};

#endif // TEST_SPACE_H
