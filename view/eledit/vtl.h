#ifndef VTL_H
#define VTL_H

#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QJsonObject>
#include <QPushButton>

class vtl : public QWidget{
    Q_OBJECT

    bool conf = false;

    QLabel *id = nullptr;
    QSpinBox *size = nullptr;

public:
    QJsonObject current;

signals:
    void updateView();
    void closed();
    void restore();

public:
    vtl();
    ~vtl();

    void setData(QJsonObject data);
    void setToView();

private slots:
    void changedSize(int size);
    void confirm();

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // VTL_H
