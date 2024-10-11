#include "test_space.h"

#include "common/filedir.h"
#include "custom/dialog.h"
#include "view/vdbconnection.h"
#include "view/crossselector.h"
#include "view/crosssets.h"

#include "common/factorydata.h"
#include "db/dbdcon.h"
extern factorydata *factory;
extern dbdcon *envdb;

test_space::test_space(){
    setWindowTitle("Редактор");

    v = new wpview;
    setCentralWidget(v);
    connect(racoss, &rac::currentSelected,this,&test_space::setWindowTitle);
    connect(racoss, &rac::loadDataSelectedCross,this,&test_space::loadCrossData);
    connect(&cd,&crossdata::loadData,this,&test_space::setCurrentCross);
    createMenu();

    if(!writer->isEmptyTMP(file().tempsys)){
        Dialog d("Восстановление", "Есть незавершенный объект, открыть?",{"Да","Нет"});
        if(d.exec()){
            writer->loadData(file().tempsys);
            v->s->setMap(writer->readData(file().tempsys + QDir::separator() + file().m));
            v->s->addAllItems();;
        }
    }

    QShortcut *closeselect = new QShortcut(this);
    closeselect->setKey(QKeySequence(tr("CTRL+W")));
    connect(closeselect,&QShortcut::activated,this,&QWidget::close);
}

test_space::~test_space(){
    delete envdb;
    delete se;
}

void test_space::createMenu(){
    QMenuBar *mbar = new QMenuBar();
    QMenu *file = new QMenu("Объект");

    QAction *setups = new QAction("Параметры");
    setups->setShortcut(QKeySequence(tr("CTRL+P")));
    connect(setups,&QAction::triggered,new crosssets,&crosssets::show);
    file->addAction(setups);

    QAction *place = new QAction("Заменить подложку");
    place->setShortcut(QKeySequence(tr("CTRL+L")));
    connect(place,&QAction::triggered,this,&test_space::changeCrossBackMap);
    file->addAction(place);

    file->addSeparator();

    QAction *select_t = new QAction("Открыть объект");
    select_t->setShortcut(QKeySequence(tr("CTRL+T")));
    connect(select_t,&QAction::triggered,this,&test_space::openObject);
    file->addAction(select_t);

    QAction *save_t = new QAction("Сохранить");
    save_t->setShortcut(QKeySequence(tr("CTRL+F")));
    connect(save_t,&QAction::triggered,this,&test_space::saveCurrentData);
    file->addAction(save_t);

    QAction *saveh_t = new QAction("Сохранить как...");
    saveh_t->setShortcut(QKeySequence(tr("CTRL+H")));
    connect(saveh_t,&QAction::triggered,this,&test_space::saveHowObject);
    file->addAction(saveh_t);

    file->addSeparator();

    QAction *select_c = new QAction("Получить с сервера");
    select_c->setShortcut(QKeySequence(tr("CTRL+S")));
    connect(select_c,&QAction::triggered,new crossselector,&crossselector::show);
    file->addAction(select_c);

    mbar->addMenu(file);

    QAction *settings = new QAction("Настройки");
    settings->setShortcut(QKeySequence(tr("F10")));
    connect(settings,&QAction::triggered,new vdbconnection,&vdbconnection::show);
    mbar->addAction(settings);

    QMenuBar *rbar = new QMenuBar;
    QAction *user = new QAction(aut->user);
    user->setToolTip(aut->uperm());
    connect(user,&QAction::triggered,this,&test_space::showPermissions);
    rbar->addAction(user);

    mbar->setCornerWidget(rbar,Qt::TopRightCorner);

    setMenuBar(mbar);
}

void test_space::closeEvent(QCloseEvent *e){
    if(writer->isEmptyCurrent())
        writer->saveData(file().tempsys);

    Dialog *d = new Dialog("Выход", "Завершить работу с программой?",{"Да","Нет"});
    if(d->exec()){
        factory->vel->hideAll();
        e->accept();
    }else{
        e->ignore();
        return;
    }

    QWidget::closeEvent(e);
}

void test_space::saveCurrentData(){
    //opened current cross
    QVector<int> rac = racoss->getCurrentCross();
    if(rac.contains(0))
        return;

    //ask save cross ??
    Dialog *d = new Dialog("Отправка", "Сохранить текущее состояние перекрестка?",{"Да","Нет"});
    if(d->exec()){

        QByteArray cmap = v->s->getMap();
        QByteArray cext = writer->extend();
        QByteArray csvg = writer->svg(cmap);
        QByteArray cst = QJsonDocument(writer->getData()).toJson();

        //save temp cross data
        if(!writer->isEmptyCurrent()){
            writer->saveData(file().tempsys);
            writer->writeData(file().tempsys + QDir::separator() + file().m, cmap);
            writer->writeData(file().tempsys + QDir::separator() + file().e, cext);
            writer->writeData(file().tempsys + QDir::separator() + file().s, csvg);
        }

        //variables to DB
        QMap<QString,dbvalue> data;
        data[":bottom"] = dbvalue{cmap};
        data[":picture"] = dbvalue{csvg};
        data[":extend"] = dbvalue{cext};
        data[":state"] = dbvalue{cst};

        //execute
        cd.createNP();
        cd.sendCurrentCross(rac,data);

        //save local data
        writer->saveToLocal(racoss->getCurrentCross(),file().cross,cmap,csvg,cext,cst);
    }
}

void test_space::saveHowObject(){
    QString catalog = QFileDialog::getExistingDirectory(this, tr("Выберите каталог для сохранения объекта"),
                                                        racoss->lastFolder,
                                                        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!catalog.isEmpty()){
        racoss->lastFolder = catalog;

        QByteArray cmap = v->s->getMap();
        QByteArray cext = writer->extend();
        QByteArray csvg = writer->svg(cmap);

        //save temp cross data
        if(!writer->isEmptyCurrent()){
            writer->saveData(catalog);
            writer->writeData(catalog + QDir::separator() + file().m, cmap);
            writer->writeData(catalog + QDir::separator() + file().e, cext);
            writer->writeData(catalog + QDir::separator() + file().s, csvg);
        }
    }
}

void test_space::loadCrossData(){
    cd.createNP();
    cd.askCurrentCross(racoss->getCurrentCross());
}

void test_space::setCurrentCross(){
    stash->clearData();
    v->s->setMap(cd.single_rac["bottom"].value_byte());
    writer->setData(QJsonDocument::fromJson(cd.single_rac["state"].value_byte()).object());
    v->fitInView(v->sceneRect(), Qt::KeepAspectRatio);
    v->s->addAllItems();
}

void test_space::changeCrossBackMap(){
    QString map = QFileDialog::getOpenFileName(nullptr,
                                               "Выберите файл подложки:",
                                               file().cross,tr("Подложка (*.png)"));
    if(!map.isEmpty()){
        QFile f(map);
        if(f.open(QFile::ReadOnly)){
            v->s->setMap(f.readAll());
            f.close();
        }
    }
}

void test_space::openObject(){
    QString catalog = QFileDialog::getExistingDirectory(this, tr("Выберите каталог с файлами объекта"),
                                                        racoss->lastFolder,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!catalog.isEmpty()){
        racoss->lastFolder = catalog;
        stash->clearData();
        v->s->setMap(writer->readData(catalog + QDir::separator() + file().m));
        writer->setData(QJsonDocument::fromJson(writer->readData(catalog + QDir::separator() + file().t)).object());
        v->fitInView(v->sceneRect(), Qt::KeepAspectRatio);
        v->s->addAllItems();
    }
}

void test_space::showPermissions(){
    w  = new QWidget;
    w->setWindowModality(Qt::ApplicationModal);
    w->setWindowTitle("О пользователе");
    w->setMinimumWidth(300);

    QFormLayout *fl = new QFormLayout(w);
    fl->addRow("Пользователь:",new QLabel(aut->user));
    fl->addRow("Регион:",new QLabel(aut->region == -1 ? "*" : QString::number(aut->region)));
    fl->addRow("Район(ы):",new QLabel(aut->areas_text()));

    QPushButton *ok = new QPushButton("Ок");
    connect(ok,&QPushButton::clicked,w,&QWidget::close);
    fl->addRow(ok);

    QPushButton *swu = new QPushButton("Сменить пользователя");
    connect(swu,&QPushButton::clicked,this,&test_space::swapuser);
    fl->addRow(swu);
    w->show();
}

void test_space::swapuser(){
    w->close();
    emit logout();
}
