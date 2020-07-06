#include "mainwindow.h"
#include <QApplication>
#include "application.h"
#include <qobject.h>

int main(int argc, char *argv[])
{
    BVIRayTracerApplication a(argc, argv,BVIRayTracerApplication::defaultCameraPixelWidth(), BVIRayTracerApplication::defaultCameraPixelHeight());
    g_Application = &a;

    MainWindow w;
    QRayTracing* rayTracing = g_Application->rayTracer().get();

    QObject::connect(rayTracing, SIGNAL(OnFinish()) ,&w, SLOT(futureFinished()));
    QObject::connect(rayTracing, SIGNAL(OnProgressRangeChanged(int,int)), &w, SLOT(futureProgressRangeChanged(int,int)));
    QObject::connect(rayTracing, SIGNAL(OnProgressValueChanged(int)), &w, SLOT(progressValueChanged(int)));


    w.show();
    
    return a.exec();
}
