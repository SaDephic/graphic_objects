#ifndef CROSSSETS_H
#define CROSSSETS_H

#include <QWidget>

#include "common/rac.h"
extern rac *racoss;

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>

class crosssets : public QWidget{
    Q_OBJECT

    QLineEdit *r = nullptr;
    QLineEdit *a = nullptr;
    QLineEdit *c = nullptr;

public:
    crosssets(){
        setWindowTitle("Параметры объекта");
        setFixedSize(285,130);

        r = new QLineEdit;
        a = new QLineEdit;
        c = new QLineEdit;

        QFormLayout *fl = new QFormLayout(this);
        fl->addRow("Регион:",r);
        fl->addRow("Область:",a);
        fl->addRow("Перекресток:",c);

        QHBoxLayout *hl = new QHBoxLayout;

        QPushButton *conf = new QPushButton("Задать");
        connect(conf,&QPushButton::clicked,this,&crosssets::confirm);
        hl->addWidget(conf);

        QPushButton *cancel = new QPushButton("Отмена");
        connect(cancel,&QPushButton::clicked,this,&QWidget::close);
        hl->addWidget(cancel);

        fl->addRow(hl);

        QShortcut *closeselect = new QShortcut(this);
        closeselect->setKey(QKeySequence(tr("CTRL+W")));
        connect(closeselect,&QShortcut::activated,this,&QWidget::close);

    }
    ~crosssets(){}

private slots:
    void confirm(){
        racoss->setCurrentIDsCross(r->text().toInt(),
                                   a->text().toInt(),
                                   c->text().toInt());
        this->close();
    }
};

#endif // CROSSSETS_H
