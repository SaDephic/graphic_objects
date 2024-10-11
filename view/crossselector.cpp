#include "crossselector.h"
#include "common/filedir.h"

QTreeWidgetItem *region::item(int index){
    if(areas.keys().contains(index)){
        return areas[index];
    }
    QTreeWidgetItem *inx = new QTreeWidgetItem;
    areas.insert(index,inx);
    return inx;
}

QTreeWidgetItem *region::mapItem(){
    foreach (int k, areas.keys()) {
        it->addChild(areas[k]);
    }
    return it;
}

crossselector::crossselector(){
    cd = new crossdata;
    cd->createNP();
    connect(racoss,&rac::loaded,this,&crossselector::toView);

    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("Список объектов");
    setMinimumSize(QSize(750,500));

    statusStage = new QLabel;

    tree = new QTreeWidget;
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    tree->setVisible(false);
    tree->setColumnCount(4);
    tree->setHeaderLabels({"Имя объекта","Номер","Отрисован","Объект изменен"});

    QVBoxLayout *vl = new QVBoxLayout(this);

    QVBoxLayout *cs = new QVBoxLayout;
    slab = new QLabel("Найти:");
    slab->setVisible(false);
    btnss = new QPushButton("Поиск");
    btnss->setVisible(false);
    search = new QLineEdit;
    search->setVisible(false);

    QHBoxLayout *ss = new QHBoxLayout;
    ss->addWidget(slab);
    ss->addWidget(search);
    ss->addWidget(btnss);
    cs->addLayout(ss);
    cs->addWidget(tree);

    QHBoxLayout *bhl = new QHBoxLayout;
    selectObject = new QPushButton("Выбрать");
    connect(selectObject,&QPushButton::clicked,this,&crossselector::confirm);
    selectObject->setVisible(false);
    selectObject->setEnabled(false);
    decilineObject = new QPushButton("Отмена");
    connect(decilineObject,&QPushButton::clicked,this,&crossselector::cancel);
    decilineObject->setVisible(false);
    lselect = new QLabel;
    lselect->setVisible(false);
    bhl->addWidget(lselect);
    bhl->addStretch();
    bhl->addWidget(selectObject);
    bhl->addWidget(decilineObject);

    vl->addWidget(statusStage);
    vl->addLayout(cs);
    vl->addLayout(bhl);

    refresh = new QMenuBar;
    refresh->setEnabled(false);
    QAction *act = new QAction("Обновить");
    act->setShortcut(tr("F5"));
    connect(act,&QAction::triggered,this,&crossselector::refreshData);
    refresh->addAction(act);
    vl->setMenuBar(refresh);

    QShortcut *closeselect = new QShortcut(this);
    closeselect->setKey(QKeySequence(tr("CTRL+W")));
    connect(closeselect,&QShortcut::activated,this,&QWidget::close);
}

crossselector::~crossselector(){}

void crossselector::show(){
    if(!running)
        refreshData();
    QWidget::show();
}

int crossselector::parentCount(QTreeWidgetItem *it){
    int count = 0;
    if(it){
        while(it->parent()){
            count++;
            it = it->parent();
        }
    }
    return count;
}

void crossselector::openFolder(){
    QString folder = file().cross
                     + QDir::separator() + QString::number(_region)
                     + QDir::separator() + QString::number(_area)
                     + QDir::separator() + QString::number(_cross);
    if(QDir().exists(folder)){
        QDesktopServices::openUrl(QUrl(QUrl::fromLocalFile(folder)));
    }else{
        QMessageBox msg;
        msg.setWindowModality(Qt::ApplicationModal);
        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("Ошибка!");
        msg.setText("Каталог перекрестка не существует!");
        msg.exec();
    }
}

void crossselector::toView(){
    tree->clear();
    QVector<racobject> rec = racoss->cross;
    if(!rec.isEmpty()){
        QMap<int,region> regions;
        while(!rec.isEmpty()){
            racobject rmp = rec.first();
            QTreeWidgetItem *it = nullptr;
            //exist
            if(regions.keys().contains(rmp.region)){
                //area
                it = regions[rmp.region].item(rmp.area);
                it->setText(0,rmp.descArea);
                it->setText(1,QString::number(rmp.area));
            }else{//new
                region r;
                //region
                r.it = new QTreeWidgetItem();
                r.it->setText(0,rmp.descRegion);
                r.it->setText(1,QString::number(rmp.region));
                //area
                r.areas.insert(rmp.area, new QTreeWidgetItem);
                it = r.areas[rmp.area];
                regions.insert(rmp.region,r);
            }
            //area
            it->setText(0,rmp.descArea);
            it->setText(1,QString::number(rmp.area));
            //object
            QTreeWidgetItem *o = new QTreeWidgetItem;
            o->setText(0,rmp.descObject);
            o->setText(1,QString::number(rmp.number));
            //check existing
            QString dir = file().cross
                          + QDir::separator() + QString::number(rmp.region)
                          + QDir::separator() + QString::number(rmp.area)
                          + QDir::separator() + QString::number(rmp.number);
            //file exists
            QFile f(dir + QDir::separator() + file().s);
            if(f.exists()){
                QFileInfo ff(f);
                if(ff.size() > 10000){
                    o->setText(2,"Готов");
                    o->setForeground(2,Qt::darkGreen);
                }else{
                    o->setText(2,"Не готов");
                    o->setForeground(2,Qt::darkRed);
                }
                o->setText(3,QFileInfo(f).lastModified().toString("hh:mm:ss dd.MM.yyyy"));//каталог
            }else{
                o->setText(2,"Отсутствует");
                o->setForeground(2,Qt::darkBlue);
                o->setText(3,"Отсутствует");//каталог
            }
            //append to listing
            it->addChild(o);
            rec.removeFirst();
        }
        //set data to tree
        foreach (int k, regions.keys()) {
            tree->addTopLevelItem(regions[k].mapItem());
        }

        regions.clear();

        tree->expandAll();
        tree->resizeColumnToContents(0);
        tree->resizeColumnToContents(1);

        slab->setVisible(true);
        btnss->setVisible(true);
        search->setVisible(true);
        tree->setVisible(true);
        selectObject->setVisible(true);
        decilineObject->setVisible(true);
        lselect->setVisible(true);
        statusStage->setVisible(false);
        refresh->setEnabled(true);

        connect(search,&QLineEdit::returnPressed,this,&crossselector::searchLine);
        connect(btnss,&QPushButton::clicked,this,&crossselector::searchLine);
        connect(tree,&QTreeWidget::doubleClicked,this,&crossselector::doubleClick);
        connect(tree,&QTreeWidget::currentItemChanged,this,&crossselector::selectPads);
        connect(tree,&QTreeWidget::customContextMenuRequested,this,&crossselector::showMenu);
    }else{
        statusStage->setText("Ошибка чтения данных или данные отсутствуют!");
    }
    setCursor(Qt::ArrowCursor);

    running = false;
}

void crossselector::setStage(QString stage){
    setCursor(Qt::BusyCursor);

    disconnect(search,&QLineEdit::returnPressed,this,&crossselector::searchLine);
    disconnect(btnss,&QPushButton::clicked,this,&crossselector::searchLine);
    disconnect(tree,&QTreeWidget::doubleClicked,this,&crossselector::doubleClick);
    disconnect(tree,&QTreeWidget::currentItemChanged,this,&crossselector::selectPads);
    disconnect(tree,&QTreeWidget::customContextMenuRequested,this,&crossselector::showMenu);

    slab->setVisible(false);
    btnss->setVisible(false);
    search->setVisible(false);
    tree->setVisible(false);
    selectObject->setVisible(false);
    decilineObject->setVisible(false);
    lselect->setVisible(false);
    statusStage->setVisible(true);
    refresh->setEnabled(false);

    statusStage->setText("Читаю: " + stage);
}

void crossselector::errorMessage(QString error){
    QMessageBox msg;
    msg.setIcon(QMessageBox::Critical);
    msg.setWindowTitle("Ошибка");
    msg.setText(error);
    msg.exec();

    statusStage->setText(error);
    setCursor(Qt::ArrowCursor);
}

void crossselector::showMenu(const QPoint &pos){
    sitem = tree->itemAt(pos);
    if(parentCount(sitem) == 2){
        QMenu *menu = new QMenu();
        QAction *act = nullptr;
        QAction *arc = new QAction(sitem->text(0));
        arc->setEnabled(false);
        menu->addAction(arc);
        menu->addSeparator();
        act = new QAction("Открыть расположение");
        connect(act,&QAction::triggered,this,&crossselector::openFolder);
        menu->addAction(act);
        menu->exec(tree->mapToGlobal(pos));
    }
}

void crossselector::refreshData(){
    running = true;

    tree->setVisible(false);
    slab->setVisible(false);
    btnss->setVisible(false);
    search->setVisible(false);
    selectObject->setVisible(false);
    selectObject->setEnabled(false);
    decilineObject->setVisible(false);
    lselect->setVisible(false);
    refresh->setEnabled(false);
    statusStage->setVisible(true);

    //reader cross
    cd->createNP();//create data without params
    racoss->clearDataCross();//clear data before refresh
    //link messages
    connect(cd->db,&dbconnection::currentStage,this,&crossselector::setStage);
    connect(cd->db,&dbconnection::errorConnection,this,&crossselector::errorMessage);
    //do action
    cd->updateRegion();
}

void crossselector::searchLine(){
    if(search->text().isEmpty()){
        QList<QTreeWidgetItem*> all = tree->findItems("",Qt::MatchContains | Qt::MatchRecursive, 0);
        foreach(QTreeWidgetItem* item, all)
            item->setHidden(false);
    }else{
        QList<QTreeWidgetItem*> all = tree->findItems("",Qt::MatchContains | Qt::MatchRecursive, 0);
        foreach(QTreeWidgetItem* item, all)
            item->setHidden(true);

        QList<QTreeWidgetItem*> items;
        QString search_text = search->text();

        QString area;
        QString cross;

        if(area.isEmpty()||cross.isEmpty()){
            items = tree->findItems(search_text,Qt::MatchContains | Qt::MatchRecursive, 0);
            items.append(tree->findItems(search_text,Qt::MatchContains | Qt::MatchRecursive, 1));
        }
        foreach(QTreeWidgetItem* item, items) {
            if(parentCount(item) != 2){
                continue;
            }
            item->setHidden(false);

            QTreeWidgetItem* parent = item->parent();
            while (parent){
                parent->setHidden(false);
                parent = parent->parent();
            }
        }
        tree->expandAll();
        if(!items.isEmpty()){
            foreach(QTreeWidgetItem* item, items) {
                if(parentCount(item) == 2){
                    tree->setCurrentItem(item);
                    selectCross(item,0);
                    break;
                }
            }
        }
    }
}

void crossselector::selectCross(QTreeWidgetItem *item, int){
    if(parentCount(item) == 2){
        _cross = item->text(1).toInt();
        _area = item->parent()->text(1).toInt();
        _region = item->parent()->parent()->text(1).toInt();
        for(int i=0; i<racoss->cross.size(); ++i){
            if(_region == racoss->cross[i].region &&
                _area == racoss->cross[i].area &&
                _cross == racoss->cross[i].number){
                _subarea = racoss->cross[i].subarea;
                break;
            }
        }

        QString lna = QString::number(_region) + "/" +
                      QString::number(_area) + "/" +
                      QString::number(_cross) + "[" + QString::number(_subarea) + "]" + " : " + item->text(0);

        //cat 100 symbols in string text
        while(lna.size() > 100)
            lna.chop(1);

        lselect->setText(lna);
        selectObject->setEnabled(true);
    }else{
        _cross = -1;
        _subarea = -1;
        _area = -1;
        _region = -1;
        lselect->setText(QString());
        selectObject->setEnabled(false);
    }
}

void crossselector::selectPads(QTreeWidgetItem *current, QTreeWidgetItem *){
    selectCross(current,0);
}

void crossselector::doubleClick(const QModelIndex &){
    if(_region == -1 || _area == -1 || _subarea == -1 || _cross == -1)
        return;

    confirm();
}

void crossselector::confirm(){
    racoss->setCurrentIDsCross(_region,_area,_cross);
    emit racoss->loadDataSelectedCross();
    this->close();
}

void crossselector::cancel(){
    this->close();
}
