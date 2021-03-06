#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T10:26:25
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = SWAN2
TEMPLATE = app

#right std call
QMAKE_CXXFLAGS += -std=c++11

#release optimizations
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_LFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE += -O3


SOURCES += main.cpp\
        mainwindow.cpp \
    Entity.cpp \
    World.cpp \
    Solid.cpp \
    Animal.cpp \
    NonSolid.cpp \
    Vision.cpp \
    Coordinate.cpp \
    WorldWidget.cpp \
    WorldColors.cpp \
    Neuron.cpp \
    NeuralNetwork.cpp \
    Neuronlayer.cpp \
    Percepted.cpp \
    Visionsector.cpp \
    Visionsector_Living.cpp \
    Visionsector_NonLiving.cpp \
    SaveManager.cpp \
    EntityViewWidget.cpp \
    NNViewWidget.cpp \
    Vegetal.cpp \
    Water.cpp \
    EntityFrame.cpp \
    EntityAttributeWidget.cpp \
    Resource.cpp \
    Meat.cpp \
    Herbivore.cpp \
    Carnivore.cpp \
    WorldCreator.cpp \
    WorldCreatorResourcesWidget.cpp \
    WorldCreatorAnimalsWidget.cpp \
    lib/qcustomplot.cpp \
    WorldEditor.cpp \
    config/config.cpp \
    ParametersWidget.cpp \
    WorldEditorToolBox.cpp \
    TimeLineWidget.cpp

HEADERS  += mainwindow.h \
    Entity.h \
    World.h \
    Solid.h \
    Animal.h \
    NonSolid.h \
    Vision.h \
    Coordinate.h \
    WorldWidget.h \
    WorldColors.h \
    Neuron.h \
    Neuronlayer.h \
    NeuralNetwork.h \
    Percepted.h \
    Visionsector.h \
    Visionsector_Living.h \
    Visionsector_NonLiving.h \
    SaveManager.h \
    config/errors.h \
    config/config.h \
    config/nnNames.h \
    EntityViewWidget.h \
    Vegetal.h \
    Water.h \
    EntityFrame.h \
    EntityAttributeWidget.h \
    NNViewWidget.h \
    Resource.h \
    Meat.h \
    VisionSector_NonLiving.h \
    VisionSector_Living.h \
    Herbivore.h \
    Carnivore.h \
    WorldCreator.h \
    WorldCreatorResourcesWidget.h \
    WorldCreatorAnimalsWidget.h \
    lib/qcustomplot.h \
    WorldEditor.h \
    ParametersWidget.h \
    WorldEditorToolBox.h \
    TimeLineWidget.h

FORMS    += mainwindow.ui \
    WorldCreator.ui \
    WorldCreatorResourcesWidget.ui \
    WorldCreatorAnimalsWidget.ui \
    Timelinewidget.ui \
    ParametersWidget.ui \
    WorldEditorToolBox.ui

#comment to disable Intel IPP
CONFIG += IPP

#to build using IPP
IPP {
    #add a define to use IPP function in SWANN sources
    DEFINES += USE_INTEL_IPP
    #add build path to IPP (using default IPP Linux path)
    unix:!macx {
        LIBS += -I/opt/intel/ipp/include -L/opt/intel/ipp/lib/intel64 -lippi -lipps -lippvm -lippcore -lm -lpthread

        INCLUDEPATH += /opt/intel/ipp/include
        DEPENDPATH += /opt/intel/ipp/include
    }
    #TODO: add build option for other OSs
}
