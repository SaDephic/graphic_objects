#include <QApplication>

#include <QTranslator>
#include <QLibraryInfo>

#include "db/dbdcon.h"
#include "common/stashdata.h"
#include "common/factorydata.h"
#include "common/writerdata.h"
#include "common/rac.h"
#include "auth/stateauth.h"
#include "custom/sysenv.h"

sysenv *se = nullptr;
dbdcon *envdb = nullptr;

stashdata *stash = nullptr;
factorydata *factory = nullptr;
writerdata *writer = nullptr;
rac *racoss = nullptr;
stateauth *aut = nullptr;

#include "auth/vauth.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    envdb = new dbdcon;//read in *se
    se = new sysenv;//variables system
    aut = new stateauth;//when server is connected

    QTranslator qtTranslator;
    if(qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::path(QLibraryInfo::TranslationsPath))){
        a.installTranslator(&qtTranslator);
    }

    stash = new stashdata;
    factory = new factorydata;
    writer = new writerdata;
    racoss = new rac;

    vauth va;

    racoss->lastFolder = se->last_folder;
    va.u->setText(se->user_login);

    va.show();
    // test_space ts;
    // ts.show();

    return a.exec();
}
