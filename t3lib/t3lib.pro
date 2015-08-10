#-------------------------------------------------
#
# Project created by QtCreator 2015-07-26T10:04:14
#
#-------------------------------------------------

QT       += core xml
QT       -= gui

INCLUDEPATH += src/ \

TARGET = t3lib
TEMPLATE = lib

DEFINES += T3_LIBRARY

SOURCES += src/controller/controllserver.cpp \
            src/crypter/cryptblowfish.cpp \
            src/crypter/cryptaes.cpp \
            src/crypter/cryptrsa.cpp \
            src/crypter/crypt3des.cpp \
            src/crypter/crypt.cpp \
            src/utils/errorlogger.cpp \
            src/utils/sha_api.cpp \
            src/utils/userexception.cpp \
            src/utils/errorposition.cpp \
            src/utils/filehandler.cpp \
            src/utils/mainexception.cpp \
            src/model/rsakeypair.cpp \
            src/model/personenlist.cpp

HEADERS +=  src/controller/controllserver.h \
            src/crypter/crypt3des.h \
            src/crypter/cryptblowfish.h \
            src/crypter/crypt.h \
            src/crypter/cryptrsa.h \
            src/crypter/cryptaes.h \
            src/utils/filehandler.h \
            src/utils/globalDefines.h \
            src/utils/errorlogger.h \
            src/utils/sha_api.h \
            src/utils/mainexception.h \
            src/utils/errorposition.h \
            src/utils/userexception.h \
            src/model/personenlist.h \
            src/model/rsakeypair.h \
            src/t3_global.h \

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
