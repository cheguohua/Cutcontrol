#-------------------------------------------------
#
# Project created by QtCreator 2022-06-15T21:30:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CutControl
TEMPLATE = app


SOURCES += main.cpp\
        maincontrol.cpp \
    dxf/dl_dxf.cpp \
    dxf/dl_writer_ascii.cpp \
    dxf/dl_creationclass.cpp \
    testcontrol.cpp \
    camera/CamThread.cpp \
    gts/GtsThread.cpp

HEADERS  += maincontrol.h \
    dxf/include/dl_attributes.h \
    dxf/include/dl_codes.h \
    dxf/include/dl_creationadapter.h \
    dxf/include/dl_creationinterface.h \
    dxf/include/dl_dxf.h \
    dxf/include/dl_entities.h \
    dxf/include/dl_exception.h \
    dxf/include/dl_extrusion.h \
    dxf/include/dl_global.h \
    dxf/include/dl_writer.h \
    dxf/include/dl_writer.h \
    dxf/include/dl_writer_ascii.h \
    dxf/include/dl_creationclass.h \
    camera/include/CameraParams.h \
    camera/include/MvCameraControl.h \
    camera/include/MvErrorDefine.h \
    camera/include/ObsoleteCamParams.h \
    camera/include/MvISPErrorDefine.h \
    camera/include/MvObsoleteInterfaces.h \
    camera/include/MvSdkExport.h \
    camera/include/PixelType.h \
    camera/CamThread.h \
    gts/include/gts.h   \
    gts/GtsThread.h \
    testcontrol.h

win32: LIBS += -L$$PWD/lib -lMvCameraControl -liMVS-6000PlatformSDK -lgts

FORMS    += maincontrol.ui \
            testcontrol.ui

OTHER_FILES +=
