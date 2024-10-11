#ifndef IOLINESETS_H
#define IOLINESETS_H

#include <QWidget>
#include <QSpinBox>
#include <QCheckBox>

#include <QPushButton>

#include <QFormLayout>
#include <QVBoxLayout>

#include <QJsonObject>

class IOLineSets : public QWidget{
    Q_OBJECT

    bool conf = false;

    QCheckBox *trw = nullptr;//tramway or roadway
    QSpinBox *in = nullptr;//input
    QSpinBox *out = nullptr;//output
    QSpinBox *sizeline = nullptr;//output
    QSpinBox *sizemidline = nullptr;//output
    QCheckBox *chin = nullptr;//stopline inline
    QCheckBox *chout = nullptr;//stopline outline

public:
    QJsonObject current;

signals:
    void updateView();
    void closed();
    void restore();

public:
    IOLineSets();
    void setData(QJsonObject data);
    void setToView();

private slots:
    void changedIn(int i);
    void changedOut(int i);
    void changedSizeLine(int i);
    void changedSizeMidLine(int i);
    void changedCHIN(int);
    void changedCHOUT(int);
    void changedTRW(int);

    void confirm();

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // IOLINESETS_H
