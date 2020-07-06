#-------------------------------------------------
#
# Project created by QtCreator 2014-09-01T21:59:07
#
#-------------------------------------------------

QT       += core gui
QT       += concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RayTracer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pixelbuffer.cpp \
    camera.cpp \
    application.cpp \
    sceneobject.cpp \
    intersection.cpp \
    ray.cpp \
    vector.cpp \
    plane.cpp \
    material.cpp \
    scene.cpp \
    pointlight.cpp \
    raytracing.cpp \
    raytracingblock.cpp \
    sphere.cpp \
    rotation.cpp \
    matrix.cpp \
    ../../../../../../Library/Google/gtest_1_7_0/src/gtest-all.cc \
    Tests/Matrix_Test001.cpp \
    Tests/Matrix_Test002.cpp \
    Tests/Matrix_Test003.cpp \
    Tests/Matrix_Test004.cpp \
    Tests/Matrix_Test005.cpp \
    Tests/Matrix_Test006.cpp \
    Tests/Matrix_Test007.cpp \
    Tests/rotation_Test.cpp \
    phonglightingmodel.cpp \
    phonelightingmodelcalculation.cpp \
    Tests/PhongLightingModel_Test001.cpp \
    phonglightingmodelhelper.cpp \
    Tests/PhongLightingModel_Test002.cpp \
    Tests/RayTracer_Test0001.cpp \
    Tests/RayTracer_Test002.cpp \
    Plane_Scatter.cpp \
    plane_chessboard.cpp \
    plyreader.cpp \
    Triangle.cpp \
    mesh.cpp \
    PerlinNoise.cpp \
    intersectionwithsceneobject.cpp \
    colorcalculation.cpp \
    bumpmapping.cpp \
    affinetransformdialog.cpp \
    matrixmodel.cpp \
    raytracingcontext.cpp \
    cube.cpp \
    Application_Scene2.cpp \
    Application_Scene3.cpp \
    Application_Scene4.cpp \
    Application_Scene5.cpp \
    Application_Scene6.cpp \
    Application_Scene7.cpp \
    Application_Scene8.cpp \
    meshtriangle.cpp \
    boxedscene.cpp \
    normalscene.cpp \
    qraytracing.cpp \
    raytracingcontext_nomultithread.cpp \
    futurewatcherresult.cpp \
    futurewatchercontainer.cpp \
    raytracingcontext_multithread.cpp \
    Tests/SphereTo2DMapping.cpp \
    rply.c

HEADERS  += mainwindow.h \
    pixelbuffer.h \
    camera.h \
    plane.h \
    vector.h \
    application.h \
    sceneobject.h \
    intersection.h \
    ray.h \
    NearPlane.h \
    material.h \
    scene.h \
    pointlight.h \
    raytracing.h \
    raytracingblock.h \
    PixelData.h \
    sphere.h \
    rotation.h \
    matrix.h \
    color.h \
    phonglightingmodel.h \
    phonelightingmodelcalculation.h \
    phonglightingmodelhelper.h \
    raytracer_test003.h \
    Plane_Scatter.h \
    plane_chessboard.h \
    plyreader.h \
    Triangle.h \
    mesh.h \
    PerlinNoise.h \
    intersectionwithsceneobject.h \
    SurfaceDimension.h \
    colorcalculation.h \
    bumpmapping.h \
    affinetransformdialog.h \
    matrixmodel.h \
    raytracingcontext.h \
    cube.h \
    meshtriangle.h \
    boxedscene.h \
    BoxKey.h \
    normalscene.h \
    qraytracing.h \
    raytracingcontext_nomultithread.h \
    futurewatcherresult.h \
    futurewatchercontainer.h \
    raytracingcontext_multithread.h \
    rply.h

#FORMS    += mainwindow.ui \
#    affinetransformdialog.ui


# adding boost
INCLUDEPATH += /opt/local/include
LIBS += -L /opt/local/lib
LIBS += -lboost_system-mt -lboost_filesystem-mt

# adding gtesting
INCLUDEPATH += /Users/brendanbosman/Library/Google/gtest_1_7_0/include

#LIBS += -framework TheFramework

#LIBS += -l
LIBS += -L/usr/local/lib -lprotobuf
INCLUDEPATH += /usr/local/include





QMAKE_CXXFLAGS += -std=c++11


QMAKE_CFLAGS += -Wignored-qualifiers



OTHER_FILES += \
    MarkSheet.txt \
    README.TXT

RESOURCES += \
    res.qrc

FORMS += \
    affinetransformdialog.ui \
    mainwindow.ui
