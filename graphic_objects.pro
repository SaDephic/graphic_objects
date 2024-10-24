QT += core gui sql xml svg network networkauth

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = crosseditor

MOC_DIR = common\build\moc
RCC_DIR = common\build\rcc
OBJECTS_DIR = coomon\build\obj

CONFIG(debug, debug|release){
    DESTDIR = $$OUT_PWD\CRE_Debug
    QMAKE_POST_LINK = $$(QTDIR)\bin\windeployqt --no-system-d3d-compiler $$OUT_PWD\CRE_Debug#maker
    # QMAKE_POST_LINK = $$(QTDIR)\bin\windeployqt --no-translations --no-opengl-sw --no-system-d3d-compiler $$OUT_PWD\CRE_Debug#maker
    # QMAKE_POST_LINK += && xcopy /S $$system_path(C:\Users\Public\Unpound\SQLDLL) $$system_path($$OUT_PWD\CRE_Debug)#pglib
}else{
    DESTDIR = $$OUT_PWD\CRE_Release
    QMAKE_POST_LINK = $$(QTDIR)\bin\windeployqt --no-system-d3d-compiler $$OUT_PWD\CRE_Release#maker
    # QMAKE_POST_LINK = $$(QTDIR)\bin\windeployqt --no-translations --no-opengl-sw --no-system-d3d-compiler $$OUT_PWD\CRE_Release#maker
    # QMAKE_POST_LINK += && xcopy /S $$system_path(C:\Users\Public\Unpound\SQLDLL) $$system_path($$OUT_PWD\CRE_Release)#pglib
}


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auth/stateauth.cpp \
    common/crossdata.cpp \
    common/factorydata.cpp \
    common/filedir.cpp \
    common/querys.cpp \
    common/rac.cpp \
    common/writerdata.cpp \
    custom/dep.cpp \
    custom/gin_index.cpp \
    custom/dialog.cpp \
    custom/geom.cpp \
    custom/sysenv.cpp \
    db/dbconnection.cpp \
    db/dbdcon.cpp \
    db/dbvalue.cpp \
    elements/cam.cpp \
    elements/crosswalk.cpp \
    elements/ielements.cpp \
    elements/elements.cpp \
    common/stashdata.cpp \
    elements/mark.cpp \
    elements/simple/amid.cpp \
    elements/simple/gpoint.cpp \
    elements/simple/line/gline.cpp \
    elements/simple/line/linkpts.cpp \
    elements/trafficlight/lenslamp.cpp \
    elements/trafficlight/trafficlight.cpp \
    test_space.cpp \
    view/crossselector.cpp \
    view/crosssets.cpp \
    view/eledit/iolinesets.cpp \
    view/eledit/vcam.cpp \
    view/link/direction.cpp \
    view/link/manview.cpp \
    view/vdbconnection.cpp \
    view/veledit.cpp \
    view/eledit/vmrk.cpp \
    view/eledit/vtl.cpp \
    view/workplace/passcene.cpp \
    view/workplace/pasview.cpp \
    view/workplace/wpscene.cpp \
    view/workplace/wpview.cpp \
    main.cpp \
    auth/vauth.cpp

HEADERS += \
    auth/stateauth.h \
    common/crossdata.h \
    common/factorydata.h \
    common/filedir.h \
    common/querys.h \
    common/rac.h \
    common/writerdata.h \
    custom/dep.h \
    custom/gin_index.h \
    custom/dialog.h \
    custom/geom.h \
    custom/sysenv.h \
    db/dbconnection.h \
    db/dbdcon.h \
    db/dbvalue.h \
    elements/cam.h \
    elements/crosswalk.h \
    elements/ielements.h \
    elements/elements.h \
    common/stashdata.h \
    elements/mark.h \
    elements/simple/amid.h \
    elements/simple/gpoint.h \
    elements/simple/line/gline.h \
    elements/simple/line/linkpts.h \
    elements/trafficlight/lenslamp.h \
    elements/trafficlight/trafficlight.h \
    test_space.h \
    view/crossselector.h \
    view/crosssets.h \
    view/eledit/iolinesets.h \
    view/eledit/vcam.h \
    view/link/direction.h \
    view/link/manview.h \
    view/vdbconnection.h \
    view/veledit.h \
    view/eledit/vmrk.h \
    view/eledit/vtl.h \
    view/workplace/passcene.h \
    view/workplace/pasview.h \
    view/workplace/wpscene.h \
    view/workplace/wpview.h \
    auth/vauth.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
