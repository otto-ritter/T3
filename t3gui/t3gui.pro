#-------------------------------------------------
#
# Project created by QtCreator 2011-05-09T19:43:18
#
#-------------------------------------------------

QT       += core widgets xml

TARGET = t3gui
TEMPLATE = app
INCLUDEPATH += src/ \

SOURCES +=  src/main.cpp\
            src/controller/app.cpp \
            src/gui/mainwindow.cpp \
            src/gui/managingfrienddialog.cpp \
            src/gui/settings.cpp \

HEADERS  += src/controller/app.h \
            src/gui/mainwindow.h \
            src/gui/managingfrienddialog.h \
            src/gui/settings.h

FORMS    += src/gui/mainwindow.ui \
            src/gui/managingfrienddialog.ui \
            src/gui/settings.ui \

LIBS += -lcrypto \
        -lssl \

RESOURCES += etc/Icons.qrc \
