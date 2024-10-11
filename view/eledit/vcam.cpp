#include "vcam.h"

vcam::vcam(){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Камера");

    camsize = new QSpinBox;
    connect(camsize,&QSpinBox::valueChanged,this,&vcam::changedCamSize);
    id = new QLabel;
    name = new QLineEdit;
    connect(name,&QLineEdit::textChanged,this,&vcam::changedName);
    color = new QPushButton;
    connect(color,&QPushButton::clicked,this,&vcam::showColor);
    size = new QSpinBox;
    connect(size,&QSpinBox::valueChanged,this,&vcam::changedTextSize);
    urll = new QLineEdit;
    connect(urll,&QLineEdit::textChanged,this,&vcam::changedUrl);
    stop = new QLineEdit;
    connect(stop,&QLineEdit::textChanged,this,&vcam::changedStop);
    up = new QLineEdit;
    connect(up,&QLineEdit::textChanged,this,&vcam::changedUp);
    down = new QLineEdit;
    connect(down,&QLineEdit::textChanged,this,&vcam::changedDown);
    left = new QLineEdit;
    connect(left,&QLineEdit::textChanged,this,&vcam::changedLeft);
    right = new QLineEdit;
    connect(right,&QLineEdit::textChanged,this,&vcam::changedRight);
    bcolor = new QColorDialog;
    bcolor->setWindowModality(Qt::WindowModality::ApplicationModal);
    bcolor->setVisible(false);
    connect(bcolor,&QColorDialog::currentColorChanged,this,&vcam::updateColor);
    connect(bcolor,&QColorDialog::accepted,this,&vcam::colorAccept);
    connect(bcolor,&QColorDialog::rejected,this,&vcam::colorReject);

    QGroupBox *mm = new QGroupBox("Параметры объекта");
    QFormLayout *ff = new QFormLayout(mm);
    ff->addRow("Размер камеры:",camsize);
    ff->addRow("Текст",name);
    ff->addRow("Цвет области:",color);
    ff->addRow("Размер шрифта",size);

    QGroupBox *bb = new QGroupBox("Привязка");
    QFormLayout *flay = new QFormLayout(bb);
    flay->addRow("URL:",urll);
    flay->addRow("Остановить:",stop);
    flay->addRow("Вверх",up);
    flay->addRow("Вниз",down);
    flay->addRow("Налево",left);
    flay->addRow("Направо",right);

    QVBoxLayout *vlay = new QVBoxLayout(this);
    vlay->addWidget(mm);
    vlay->addWidget(bb);
    vlay->addStretch();

    QPushButton *confirm = new QPushButton("Принять");
    connect(confirm,&QPushButton::clicked,this,&vcam::confirm);
    vlay->addWidget(confirm);
}

void vcam::setData(QJsonObject data){
    current = data;
    setToView();
}

void vcam::setToView(){
    id->setText(QString::number(current["id"].toInt()));
    camsize->setValue(current["camsize"].toInt());
    name->setText(current["name"].toString());
    color->setStyleSheet("background-color:" + current["color"].toString());
    size->setValue(current["textsize"].toInt());
    urll->setText(current["url"].toString());
    stop->setText(current["stop"].toString());
    up->setText(current["up"].toString());
    down->setText(current["down"].toString());
    left->setText(current["left"].toString());
    right->setText(current["right"].toString());
}

void vcam::changedCamSize(int size){
    current["camsize"] = (int)size;
    emit updateView();
}

void vcam::changedName(const QString &t){
    current["name"] = (QString)t;
    emit updateView();
}

void vcam::changedTextSize(int size){
    current["textsize"] = (int)size;
    emit updateView();
}

void vcam::changedUrl(const QString &t){
    current["url"] = (QString)t;
    emit updateView();
}

void vcam::changedStop(const QString &t){
    current["stop"] = (QString)t;
    emit updateView();
}

void vcam::changedUp(const QString &t){
    current["up"] = (QString)t;
    emit updateView();
}

void vcam::changedDown(const QString &t){
    current["down"] = (QString)t;
    emit updateView();
}

void vcam::changedLeft(const QString &t){
    current["left"] = (QString)t;
    emit updateView();
}

void vcam::changedRight(const QString &t){
    current["right"] = (QString)t;
    emit updateView();
}

void vcam::showColor(){
    tmpcolor = QColor(current["color"].toString());
    bcolor->setCurrentColor(tmpcolor);
    //bcolor->setVisible(true);
    bcolor->show();
}

void vcam::updateColor(QColor col){
    current["color"] = (QString)col.name();
    emit updateView();
}

void vcam::colorAccept(){
    color->setStyleSheet("background-color:" + QVariant(bcolor->currentColor()).toString());
    current["color"] = (QString)bcolor->currentColor().name();
    emit updateView();
}

void vcam::colorReject(){
    color->setStyleSheet("background-color:" + tmpcolor.name());
    current["color"] = (QString)tmpcolor.name();
    emit updateView();
}

void vcam::confirm(){
    conf = true;
    close();
}

void vcam::closeEvent(QCloseEvent *e){
    if(!conf){
        emit restore();
    }
    emit closed();
    conf = false;
    QWidget::closeEvent(e);
}
