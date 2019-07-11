TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    String.cpp \
    FlightData.cpp \
    FlightPlan.cpp \
    test.cpp \
    FlightPlanner.cpp

HEADERS += \
    AdjacencyList.h \
    AdjacencyListElement.h \
    ArrayWrapper.h \
    ConcurrentModificationException.h \
    FlightPlanner.h \
    IndexOutOfBoundsException.h \
    LinkedList.h \
    LinkedListIterator.h \
    ListNode.h \
    SortedList.h \
    Stack.h \
    String.h \
    FlightData.h \
    FlightPlan.h \
    catch.hpp
