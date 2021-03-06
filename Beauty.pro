######################################################################
# Automatically generated by qmake (3.1) Sat Feb 2 19:12:51 2019
######################################################################

TEMPLATE = app
TARGET = Beauty
INCLUDEPATH += .
QT += widgets
QMAKE_CXXFLAGS += -std=c++11

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += Model/container.h \
           Model/deepptr.h \
           Model/model.h \
           Model/qfilterproxymodel.h \
           Model/qtablemodeladapter.h \
           Model/xmlio.h \
           View/insertwidget.h \
           View/itemview.h \
           View/mainwindow.h \
           View/tableview.h \
           Model/hierarchy/beautyitem.h \
           Model/hierarchy/consumableitem.h \
           Model/hierarchy/makeup.h \
           Model/hierarchy/nonconsumableitem.h \
           Model/hierarchy/profumo.h \
           Model/hierarchy/pulizia.h \
           Model/hierarchy/strumento.h
SOURCES += Model/model.cpp \
           Model/qfilterproxymodel.cpp \
           Model/qtablemodeladapter.cpp \
           Model/xmlio.cpp \
           View/insertwidget.cpp \
           View/itemview.cpp \
           View/main.cpp \
           View/mainwindow.cpp \
           View/tableview.cpp \
           Model/hierarchy/beautyitem.cpp \
           Model/hierarchy/consumableitem.cpp \
           Model/hierarchy/makeup.cpp \
           Model/hierarchy/nonconsumableitem.cpp \
           Model/hierarchy/profumo.cpp \
           Model/hierarchy/pulizia.cpp \
           Model/hierarchy/strumento.cpp


RESOURCES += \
    resources.qrc
