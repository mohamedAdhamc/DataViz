QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport # Choosing modules (group of classes) needed for the app

CONFIG += c++11 # Setting the standard of C++

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    dataset.cpp \
    datasetsviewer.cpp \
    datasetwindow.cpp \
    functiondialog.cpp \
    graphwindow.cpp \
    helpdialog.cpp \
    histogramwindow.cpp \
    main.cpp \
    parentwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    aboutdialog.h \
    atmsp.h \
    dataset.h \
    datasetsviewer.h \
    datasetwindow.h \
    functiondialog.h \
    graphwindow.h \
    helpdialog.h \
    histogramwindow.h \
    parentwindow.h \
    qcustomplot.h

FORMS += \
    aboutdialog.ui \
    datasetwindow.ui \
    functiondialog.ui \
    graphwindow.ui \
    helpdialog.ui \
    histogramwindow.ui \
    parentwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/GSLlib/ -lgsl

INCLUDEPATH += $$PWD/GSLinclude
DEPENDPATH += $$PWD/GSLlib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/GSLlib/gsl.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/GSLlib/libgsl.a



win32: LIBS += -L$$PWD/GSLlib/ -lgslcblas
unix: LIBS += -lgsl -lgslcblas

INCLUDEPATH += $$PWD/GSLinclude
DEPENDPATH += $$PWD/GSLlib

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/GSLlib/gslcblas.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/GSLlib/libgslcblas.a

RESOURCES += \
    resources.qrc
