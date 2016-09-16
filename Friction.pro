TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

SOURCES += main.cpp \
    node.cpp \
    spring.cpp \
    forcemodifier.cpp \
    externalforce.cpp \
    nodecomponent.cpp \
    frictionlaw.cpp \
    amontonscoulomb.cpp \
    componentsorter.cpp \
    integrator.cpp \
    inifile.cpp \
    constantvelocity.cpp \
    powerlawfriction.cpp \
    absoluteviscosity.cpp \
    rateandstatefriction.cpp

HEADERS += \
    node.h \
    spring.h \
    forcemodifier.h \
    externalforce.h \
    nodecomponent.h \
    frictionlaw.h \
    amontonscoulomb.h \
    componentsorter.h \
    integrator.h \
    inifile.h \
    constantvelocity.h \
    powerlawfriction.h \
    absoluteviscosity.h \
    rateandstatefriction.h
