#ifndef CROSSSELECTOR_H
#define CROSSSELECTOR_H

#include "common/crossdata.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDesktopServices>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTreeWidget>
#include <QShortcut>
#include <QMessageBox>

struct region{
    QTreeWidgetItem *it;
    struct area{
        int index;
        QTreeWidgetItem *it;
    };
    QMap<int, QTreeWidgetItem*> areas;
    QTreeWidgetItem *item(int index);
    QTreeWidgetItem *mapItem();
};

class crossselector : public QWidget{
    Q_OBJECT

    bool running = false;

    int _region;
    int _area;
    int _subarea;
    int _cross;
    QTreeWidgetItem *sitem = nullptr;

    crossdata *cd = nullptr;

    QLabel *slab = nullptr;
    QPushButton *btnss = nullptr;
    QLineEdit *search = nullptr;

    QTreeWidget *tree = nullptr;
    QLabel *statusStage = nullptr;

    QLabel *lselect = nullptr;
    QPushButton *selectObject = nullptr;
    QPushButton *decilineObject = nullptr;

    QMenuBar *refresh = nullptr;

public:
    crossselector();
    ~crossselector();

    void show();

private:
    int parentCount(QTreeWidgetItem *it);
    void openFolder();

public slots:
    void toView();

private slots:
    void setStage(QString stage);
    void errorMessage(QString error);

    void showMenu(const QPoint &pos);
    void refreshData();

    void searchLine();
    void selectCross(QTreeWidgetItem *item, int);
    void selectPads(QTreeWidgetItem *current, QTreeWidgetItem *);
    void doubleClick(const QModelIndex &);

    void confirm();
    void cancel();
};

#endif // CROSSSELECTOR_H
