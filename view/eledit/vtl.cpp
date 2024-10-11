#include "vtl.h"

vtl::vtl(){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Светофор");

    id = new QLabel;
    size = new QSpinBox;
    connect(size,&QSpinBox::valueChanged,this,&vtl::changedSize);

    setMinimumSize(QSize(250,100));

    QVBoxLayout *v = new QVBoxLayout(this);

    QGroupBox *g = new QGroupBox("Параметры объекта");
    QFormLayout *flay = new QFormLayout(g);
    flay->addRow("Размер объекта:",size);
    v->addWidget(g);
    v->addStretch();


    QPushButton *confirm = new QPushButton("Принять");
    connect(confirm,&QPushButton::clicked,this,&vtl::confirm);
    v->addWidget(confirm);
}

vtl::~vtl(){}

void vtl::setData(QJsonObject data){
    current = data;
    setToView();
}

void vtl::setToView(){
    id->setText(QString::number(current["id"].toInt()));
    size->setValue(current["size"].toInt());
}

void vtl::changedSize(int size){
    current["size"] = (int)size;
    emit updateView();
}

void vtl::confirm(){
    conf = true;
    close();
}

void vtl::closeEvent(QCloseEvent *e){
    if(!conf){
        emit restore();
    }
    emit closed();
    conf = false;
    QWidget::closeEvent(e);
}
