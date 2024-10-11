#ifndef VCAM_H
#define VCAM_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QColorDialog>
#include <QLineEdit>

#include <QVBoxLayout>
#include <QFormLayout>
#include <QGroupBox>

#include <QJsonObject>

class vcam : public QWidget{
    Q_OBJECT

    bool conf = false;

    //main
    QLabel *id = nullptr;//id cam
    QSpinBox *camsize = nullptr;//cam size
    QLineEdit *name = nullptr;//label name
    QPushButton *color = nullptr;//color area cam
    QSpinBox *size = nullptr;//size text

    //linker
    QLineEdit *urll = nullptr;//url to cam
    QLineEdit *stop = nullptr;//action up
    QLineEdit *up = nullptr;//action up
    QLineEdit *down = nullptr;//action down
    QLineEdit *left = nullptr;//action left
    QLineEdit *right = nullptr;//action right
    QColorDialog *bcolor = nullptr;//selector color
    QColor tmpcolor;

public:
    QJsonObject current;

signals:
    void updateView();
    void closed();
    void restore();

public:
    vcam();
    void setData(QJsonObject data);
    void setToView();

private slots:
    void changedCamSize(int size);
    void changedName(const QString &t);
    void changedTextSize(int size);
    void changedUrl(const QString &t);
    void changedStop(const QString &t);
    void changedUp(const QString &t);
    void changedDown(const QString &t);
    void changedLeft(const QString &t);
    void changedRight(const QString &t);
    void showColor();
    void updateColor(QColor col);
    void colorAccept();
    void colorReject();

    void confirm();

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // VCAM_H
