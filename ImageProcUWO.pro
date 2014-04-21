#-------------------------------------------------
#
# Project created by QtCreator 2012-01-11T10:22:27
#
#-------------------------------------------------

QT       -= gui

TARGET = ImageProcCV
TEMPLATE = lib

DEFINES += IMAGEPROCCV_LIBRARY

SOURCES += \
    src/DisjointSets.cpp \
    src/CheckMatrix.cpp \
    src/GetLut.cpp \
    src/testskel.cpp \
    src/IPCV_ApplyLUT.cpp \
    src/IPCV_BwBoundaries.cpp \
    src/IPCV_BwBoundaries_2.cpp \
    src/IPCV_BwBranchPoints.cpp \
    src/IPCV_BwBridge.cpp \
    src/IPCV_BwClean.cpp \
    src/IPCV_BwCorner.cpp \
    src/IPCV_BwEndPoints.cpp \
    src/IPCV_BwHitMiss.cpp \
    src/IPCV_BwLabel.cpp \
    src/IPCV_BwMajority.cpp \
    src/IPCV_BwPerim.cpp \
    src/IPCV_BwRemove.cpp \
    src/IPCV_BwSelect.cpp \
    src/IPCV_BWSkel.cpp \
    src/IPCV_BwSkel2.cpp \
    src/IPCV_BwSkel3.cpp \
    src/IPCV_BWSpur.cpp \
    src/IPCV_BwSpur2.cpp \
    src/IPCV_BWThin.cpp \
    src/IPCV_BwThin2.cpp \
    src/IPCV_CannyEdgeDetector.cpp \
    src/IPCV_getOtusThreshValue.cpp \
    src/IPCV_ImageAdjust.cpp \
    src/IPCV_ImageInvert.cpp \
    src/IPCV_ImageNormalize.cpp \
    src/IPCV_SkelEndPoints.cpp \
    src/IPCV_SsedTransform.cpp


HEADERS +=\
    include/DisjointSets.h \
    include/ImageProcCV.h \
    include/ErrorNumbers.h \
    include/LookupTables.h \
    include/ImageProcCV_global.h

#Configurations for Windows
win32{
INCLUDEPATH += D:/OpenCV_MinGW/install/include
INCLUDEPATH += ./include

LIBS += -LD:/OpenCV_MinGW/install/x64/mingw/bin \
-llibopencv_core248 \
-llibopencv_highgui248 \
-llibopencv_imgproc248 \
-llibopencv_features2d248 \
-llibopencv_calib3d248

}

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE520443B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ImageProcCV.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}


unix:!symbian {

INCLUDEPATH += ./include/
INCLUDEPATH += /opt/TBB40U4/include/

LIBS += -L/opt/Opencv-2.3.1/lib \
-lopencv_core \
-lopencv_highgui \
-lopencv_imgproc \
-lopencv_features2d \
-lopencv_calib3d


LIBS += -L/opt/TBB40U4/lib \
-ltbb





}


























