#ifndef TEST_SPACE_H
#define TEST_SPACE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>

#include "custom/dialog.h"

#include "view/workplace/wpview.h"
#include "common/crossdata.h"

#include "common/writerdata.h"
#include "auth/stateauth.h"
#include "custom/sysenv.h"

extern writerdata *writer;
extern stateauth *aut;
extern sysenv *se;

class test_space : public QMainWindow{
    Q_OBJECT

    crossdata cd;
    wpview *v = nullptr;
    QWidget *w= nullptr;

public: signals:
    void logout();

public:
    test_space();
    ~test_space();

private:
    void createMenu();

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    //bottom - png
    //picture - svg
    //extend - расширенные
    //state - шаблон
    void saveCurrentData();
    void saveHowObject();
    void loadCrossData();
    void setCurrentCross();
    void changeCrossBackMap();
    void openObject();

    void showPermissions();
    void swapuser();
};

#endif // TEST_SPACE_H
