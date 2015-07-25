#-------------------------------------------------
#
# Project created by QtCreator 2011-05-09T19:43:18
#
#-------------------------------------------------

QT       += core widgets xml

TARGET = T3
TEMPLATE = app
INCLUDEPATH += Source/ \

SOURCES += Source/main.cpp\
        Source/Gui/mainwindow.cpp \
        Source/Functions/crypt.cpp \
        Source/Functions/cryptblowfish.cpp \
        Source/Functions/crypt3des.cpp \
        Source/Functions/sha_api.cpp \
        Source/Helper/errorposition.cpp \
        Source/Functions/cryptaes.cpp \
        Source/Functions/cryptrsa.cpp \
        Source/Controller/controllserver.cpp \
        Source/Model/personenlist.cpp \
        Source/Gui/managingfrienddialog.cpp \
        Source/Model/rsakeypair.cpp \
        Source/Helper/errorlogger.cpp \
        Source/Gui/settings.cpp \
        Source/Helper/filehandler.cpp \
        Source/Helper/userexception.cpp \
        Source/Helper/mainexception.cpp

HEADERS  += Source/Gui/mainwindow.h \
        Source/Functions/crypt.h \
        Source/Functions/cryptblowfish.h \
        Source/Functions/crypt3des.h \
        Source/Functions/sha_api.h \
	Source/Helper/errorposition.h \
	Source/Functions/cryptaes.h \
	Source/Functions/cryptrsa.h \
        Source/Controller/controllserver.h \
	Source/Model/personenlist.h \
	Source/Gui/managingfrienddialog.h \
	Source/Model/rsakeypair.h \
	Source/Helper/errorlogger.h \
	Source/Helper/globalDefines.h \
        Source/Gui/settings.h \
        Source/Helper/filehandler.h \
        Source/Helper/mainexception.h \
        Source/Helper/userexception.h

FORMS    += Source/Gui/mainwindow.ui \
        Source/Gui/managingfrienddialog.ui \
        Source/Gui/settings.ui

LIBS += -lcrypto \
        -lssl

RESOURCES += Source/Icons.qrc \
