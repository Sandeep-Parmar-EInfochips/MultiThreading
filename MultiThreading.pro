TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


TARGET = Multithreading

DESTDIR     = bin                   #Target file directory
OBJECTS_DIR = build/Object_files    #Intermediate object files directory
MOC_DIR     = build/Moc_files       #Intermediate moc files directory

INCLUDEPATH += inc

INCLUDEPATH +=/usr/local/include/UnitTest++


SOURCES +=  src/main.cpp \
            src/primary.cpp \
            src/worker.cpp

HEADERS += \
            inc/primary.h \
            inc/worker.h \
    inc/common.h \
    inc/workercallbackinterface.h


LIBS += -pthread
LIBS += -lUnitTest++


