#ifndef VMRK_H
#define VMRK_H


#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QColorDialog>
#include <QFontDatabase>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QJsonObject>

class vmrk : public QWidget{
    Q_OBJECT

    bool conf = false;

    QLabel *id = nullptr;
    QPushButton *color = nullptr;
    QSpinBox *size = nullptr;
    QComboBox *style = nullptr;
    QLineEdit *txt = nullptr;
    QColorDialog *bcolor = nullptr;
    QColor tmpcolor;

public:
    QJsonObject current;

signals:
    void updateView();
    void closed();
    void restore();

public:
    vmrk();

    void setData(QJsonObject data);
    void setToView();

private slots:
    void changedStyle(const QString &t);
    void changedSize(int size);
    void changedText(const QString &t);
    void showColor();
    void updateColor(QColor col);
    void colorAccept();
    void colorReject();

    void confirm();

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // VMRK_H
