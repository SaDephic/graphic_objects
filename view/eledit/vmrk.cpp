#include "vmrk.h"

void vmrk::setData(QJsonObject data){
    current = data;
    setToView();
}

void vmrk::setToView(){
    id->setText(QString::number(current["id"].toInt()));
    size->setValue(current["size"].toInt());
    style->setCurrentText(current["style"].toString());
    color->setStyleSheet("background-color:" + current["color"].toString());
    txt->setText(current["text"].toString());
}

void vmrk::changedStyle(const QString &t){
    current["style"] = (QString)t;
    emit updateView();
}

void vmrk::changedSize(int size){
    current["size"] = (int)size;
    emit updateView();
}

void vmrk::changedText(const QString &t){
    current["text"] = (QString)t;
    emit updateView();
}

void vmrk::showColor(){
    tmpcolor = QColor(current["color"].toString());
    bcolor->setCurrentColor(tmpcolor);
    //bcolor->setVisible(true);
    bcolor->show();
}

void vmrk::updateColor(QColor col){
    current["color"] = (QString)col.name();
    emit updateView();
}

void vmrk::colorAccept(){
    color->setStyleSheet("background-color:" + QVariant(bcolor->currentColor()).toString());
    current["color"] = (QString)bcolor->currentColor().name();
    emit updateView();
}

void vmrk::colorReject(){
    color->setStyleSheet("background-color:" + tmpcolor.name());
    current["color"] = (QString)tmpcolor.name();
    emit updateView();
}

void vmrk::confirm(){
    conf = true;
    close();
}

void vmrk::closeEvent(QCloseEvent *e){
    if(!conf){
        emit restore();
    }
    emit closed();
    conf = false;
    QWidget::closeEvent(e);
}

vmrk::vmrk(){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Метка");

    id = new QLabel;
    color = new QPushButton;
    connect(color,&QPushButton::clicked,this,&vmrk::showColor);
    size = new QSpinBox;
    connect(size,&QSpinBox::valueChanged,this,&vmrk::changedSize);
    style = new QComboBox;
    connect(style,&QComboBox::currentTextChanged,this,&vmrk::changedStyle);
    style->addItems(QFontDatabase::families());
    txt = new QLineEdit;
    connect(txt,&QLineEdit::textChanged,this,&vmrk::changedText);
    bcolor = new QColorDialog;
    bcolor->setWindowModality(Qt::WindowModality::ApplicationModal);
    bcolor->setVisible(false);
    connect(bcolor,&QColorDialog::currentColorChanged,this,&vmrk::updateColor);
    connect(bcolor,&QColorDialog::accepted,this,&vmrk::colorAccept);
    connect(bcolor,&QColorDialog::rejected,this,&vmrk::colorReject);

    QVBoxLayout *vl = new QVBoxLayout(this);
    QGroupBox *b = new QGroupBox("Параметры объекта");
    QFormLayout *flay = new QFormLayout(b);
    flay->addRow("Размер шрифта:",size);
    flay->addRow("Стиль:",style);
    flay->addRow("Цвет:",color);
    flay->addRow("Текст:",txt);
    vl->addWidget(b);
    vl->addStretch();


    QPushButton *confirm = new QPushButton("Принять");
    connect(confirm,&QPushButton::clicked,this,&vmrk::confirm);
    vl->addWidget(confirm);
}
