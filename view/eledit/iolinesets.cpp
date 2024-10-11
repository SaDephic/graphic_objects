#include "iolinesets.h"

IOLineSets::IOLineSets(){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Линия");
    setMinimumWidth(300);

    trw = new QCheckBox;
    connect(trw,&QCheckBox::stateChanged,this,&IOLineSets::changedTRW);
    in = new QSpinBox;
    connect(in,&QSpinBox::valueChanged,this,&IOLineSets::changedIn);
    out = new QSpinBox;
    connect(out,&QSpinBox::valueChanged,this,&IOLineSets::changedOut);
    sizeline = new QSpinBox;
    connect(sizeline,&QSpinBox::valueChanged,this,&IOLineSets::changedSizeLine);
    sizemidline = new QSpinBox;
    connect(sizemidline,&QSpinBox::valueChanged,this,&IOLineSets::changedSizeMidLine);
    chin = new QCheckBox;
    connect(chin,&QCheckBox::stateChanged,this,&IOLineSets::changedCHIN);
    chout = new QCheckBox;
    connect(chout,&QCheckBox::stateChanged,this,&IOLineSets::changedCHOUT);

    QFormLayout *fl = new QFormLayout(this);
    fl->addRow("Трамвайная:",trw);
    fl->addRow("Входящих:",in);
    fl->addRow("Исходящих:",out);
    fl->addRow("Ширина полосы:",sizeline);
    fl->addRow("Ширина островка:",sizemidline);
    fl->addRow("Входящая стоп-линия:",chin);
    fl->addRow("Исходящая стоп-линия:",chout);

    QPushButton *confirm = new QPushButton("Принять");
    connect(confirm,&QPushButton::clicked,this,&IOLineSets::confirm);
    fl->addRow(confirm);
}

void IOLineSets::setData(QJsonObject data){
    current = data;
    setToView();
}

void IOLineSets::setToView(){
    //setWindowTitle("Линия" + QString::number(current["id"].toInt()));
    current["try"].toBool() ? trw->setCheckState(Qt::Checked) : trw->setCheckState(Qt::Unchecked);
    in->setValue(current["in"].toInt());
    out->setValue(current["out"].toInt());
    sizeline->setValue(current["sizeline"].toInt());
    sizemidline->setValue(current["sizemidline"].toInt());
    current["chin"].toBool() ? chin->setCheckState(Qt::Checked) : chin->setCheckState(Qt::Unchecked);
    current["chout"].toBool() ? chout->setCheckState(Qt::Checked) : chout->setCheckState(Qt::Unchecked);
}

void IOLineSets::changedIn(int i){
    current["in"] = (int)i;
    emit updateView();
}

void IOLineSets::changedOut(int i){
    current["out"] = (int)i;
    emit updateView();
}

void IOLineSets::changedSizeLine(int i){
    current["sizeline"] = (int)i;
    emit updateView();
}

void IOLineSets::changedSizeMidLine(int i){
    current["sizemidline"] = (int)i;
    emit updateView();
}

void IOLineSets::changedCHIN(int){
    chin->checkState() == Qt::Checked ? current["chin"] = true : current["chin"] = false;
    emit updateView();
}

void IOLineSets::changedCHOUT(int){
    chout->checkState() == Qt::Checked ? current["chout"] = true : current["chout"] = false;
    emit updateView();
}

void IOLineSets::changedTRW(int){
    trw->checkState() == Qt::Checked ? current["try"] = true : current["try"] = false;
    emit updateView();
}

void IOLineSets::confirm(){
    conf = true;
    close();
}

void IOLineSets::closeEvent(QCloseEvent *e){
    if(!conf){
        emit restore();
    }
    emit closed();
    conf = false;
    QWidget::closeEvent(e);
}
