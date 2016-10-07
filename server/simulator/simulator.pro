TEMPLATE = app
CONFIG += console
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x -g -fpermissive


SOURCES += \
    ../src/test.cpp \
    ../src/processGenerator.cpp \
    ../src/distributions.cpp \
    ../src/CompleteProcess.cpp \
    ../src/BaseProcess.cpp \
    ../src/simulator.cpp \
    ../src/finaltimes.cpp \
    ../src/basealgorithm.cpp

HEADERS += \
    ../include/serverSock.h \
    ../include/basealgorithm.h \
    ../include/iqueue.h \
    ../include/psjf.h \
    ../include/processGenerator.h \
    ../include/priorityQueue.h \
    ../include/node.h \
    ../include/fifoQueue.h \
    ../include/eventData.h \
    ../include/distributions.h \
    ../include/CompleteProcess.h \
    ../include/BaseProcess.h \
    ../include/sjf.h \
    ../include/rr.h \
    ../include/fcfs.h \
    ../include/simulator.h \
    ../include/DataSocket1.h \
    ../include/finaltimes.h \
    ../include/finalsocket.h \
    ../include/multSimData.h

INCLUDEPATH+=../include

LIBS+=-pthread
OTHER_FILES +=

