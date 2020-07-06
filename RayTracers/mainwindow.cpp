#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include "application.h"
#include "rotation.h"
#include "raytracing.h"
#include "affinetransformdialog.h"
#include <QFileDialog>
#include <QStandardPaths>
#include "raytracingcontext.h"

MainWindow::MainWindow(QWidget *parent) :
    inherited(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionBump_Mapping->setChecked(g_Application->rayTracer()->doBumpMapping());
    ui->actionShadowing->setChecked(g_Application->rayTracer()->shadowing());
    ui->actionMulti_Threading->setChecked(g_Application->rayTracer()->multiThreaded());
    ui->actionBlock->setChecked(g_Application->rayTracer()->blocks());
    ui->actionReflection->setChecked(g_Application->rayTracer()->reflection());
    ui->actionSuperSampling->setChecked(g_Application->rayTracer()->superSampling());
    ui->actionInterception->setChecked(g_Application->rayTracer()->interception());

    setGeometry(0, 0, 1600, 1000);
                    ;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    inherited::keyPressEvent(e);
    //
//    switch (e->key())
//    {
//    case Qt::Key_Left:
//        if(e->modifiers()& Qt::ShiftModifier)
//        {
//            g_Application->Rotate(Vector::VECTOR_UNIT_X, 10, Vector(0));
//        }
//        else if (e->modifiers()& Qt::ControlModifier)
//        {
//            g_Application->Rotate(Vector::VECTOR_UNIT_Y, 10, Vector(0));
//        }
//        else
//        {
//            g_Application->Rotate(Vector::VECTOR_UNIT_Z, 10, Vector(0));
//        }
//        this->repaint();
//        break;
//    case Qt::Key_Right:
//        if(e->modifiers()& Qt::ShiftModifier)
//        {
//            g_Application->Rotate(Vector::VECTOR_UNIT_X, -10, Vector(0));
//        }
//        else if (e->modifiers()& Qt::ControlModifier)
//        {
//            g_Application->Rotate(Vector::VECTOR_UNIT_Y, -10, Vector(0));
//        }
//        else
//        {
//            g_Application->Rotate(Vector::VECTOR_UNIT_Z, -10, Vector(0));
//        }
//        this->repaint();
//        break;
//    default:
//        break;
//    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    inherited::keyReleaseEvent(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int x = e->localPos().x();
    int y = e->localPos().y();
    if ((x < g_Application->Buffer().get()->width())
        && (y < g_Application->Buffer().get()->height()))
    {
        Vector origin = (g_Application->rayTracer())->CalculatePixelVector(
                    g_Application->Buffer(),
                    g_Application->camera(),
                    x, y);
        Vector direction = origin - g_Application->camera().get()->cameraPoint();
        direction.normalise();


        RayTracingContext ctx(
                    g_Application->Buffer(),
                    g_Application->camera(),
                    g_Application->scene(),
                    g_Application->ie(),
                    g_Application->f(),
                    false,
                    false,
                    false,
                    false,
                    false);
        IntersectionCtx intersection_ctx(direction, origin);
        ctx.DoRayTracingInternal2(
                    intersection_ctx,
                    origin,
                    direction);
        if (intersection_ctx.interSectionType()  == InterSectionType_Outside)
        {
            if (intersection_ctx.sceneObject() != nullptr)
            {
                int ddd=5;
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, (g_Application->Buffer())->image());
}

void MainWindow::on_actionScene_1_triggered()
{
    g_Application->CreateScene01();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_2_triggered()
{
    g_Application->CreateScene02();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_3_triggered()
{
    g_Application->CreateScene03();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_4_triggered()
{
    g_Application->CreateScene04();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_5_triggered()
{
    g_Application->CreateScene05();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_6_triggered()
{
    g_Application->CreateScene06();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_7_triggered()
{
    g_Application->CreateScene07();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionScene_8_triggered()
{
    g_Application->CreateScene08();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionReset_Camera_triggered()
{
    g_Application->resetCamera();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionZoom_OUT_triggered()
{
    (g_Application->camera())->ZoomOut();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionZoom_IN_triggered()
{
    (g_Application->camera())->ZoomIn();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraMoveLeft_triggered()
{
    (g_Application->camera())->moveLeft(5);
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraMoveRight_triggered()
{
    (g_Application->camera())->moveRight(5);
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraMoveUp_triggered()
{
    (g_Application->camera())->moveUp(5);
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraMoveDown_triggered()
{
    (g_Application->camera())->moveDown(5);
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraMoveForward_triggered()
{
    (g_Application->camera())->moveForward(5);
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraMoveBackward_triggered()
{
    (g_Application->camera())->moveBackward(5);
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionCameraTransform_triggered()
{

        AffineTransformDialog dialog(this, (g_Application->camera())->cameraDirection());
        if (dialog.exec() == QDialog::Accepted)
        {
            (g_Application->camera())->AffineTransform(dialog.matrix(), true);
            g_Application->DoRayTracing();
            if(!g_Application->rayTracer()->multiThreaded())
            {
                repaint();
            }
        }
}

void MainWindow::on_actionMulti_Threading_triggered()
{
    (g_Application->rayTracer())->setmultiThreaded(ui->actionMulti_Threading->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionBump_Mapping_triggered()
{
    (g_Application->rayTracer())->setDoBumpMapping(ui->actionBump_Mapping->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionShadowing_triggered()
{
    (g_Application->rayTracer())->setShawowing(ui->actionShadowing->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionSuperSampling_triggered()
{
    g_Application->rayTracer()->setSuperSampling(ui->actionSuperSampling->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

void MainWindow::on_actionInterception_triggered()
{
    g_Application->rayTracer()->setInterception(ui->actionInterception->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }

}



void MainWindow::on_actionSave_large_triggered()
{
    QString filename = QFileDialog::getSaveFileName(
                this,
                "Save file..",
                "/Users/brendanbosman/Pictures/untitled.jpg",
                "Images (*.jpg)");
    if (filename != nullptr && filename != "")
    {
        g_Application->saveImage(filename);
    }
}

void MainWindow::on_actionBlock_triggered()
{
    (g_Application->rayTracer())->setBlocks(ui->actionBlock->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }

}

void MainWindow::on_actionReflection_triggered()
{
    (g_Application->rayTracer())->setReflection(ui->actionReflection->isChecked());
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }

}


void MainWindow::on_actionStop_triggered()
{
    g_Application->rayTracer()->cancel();
}

void MainWindow::futureFinished()
{
    this->repaint();
}

void MainWindow::futureProgressRangeChanged(int a, int b)
{
    ui->progressBar->setMinimum(a);
    ui->progressBar->setMaximum(b);
    ui->progressBar->setValue(a);
}

void MainWindow::progressValueChanged(int a)
{
    ui->progressBar->setValue(a);

}
void MainWindow::on_actionXPlaneLeft_triggered()
{
    g_Application->Rotate(Vector::VECTOR_UNIT_X, 10, Vector(0));
}




void MainWindow::on_actionXPlaneRight_triggered()
{
    g_Application->Rotate(Vector::VECTOR_UNIT_X, -10, Vector(0));
}

void MainWindow::on_actionYPlane_Plus_10_degrees_triggered()
{
    g_Application->Rotate(Vector::VECTOR_UNIT_Y, 10, Vector(0));

}

void MainWindow::on_actionYPlane_Minus_10_degrees_triggered()
{
    g_Application->Rotate(Vector::VECTOR_UNIT_Y, -10, Vector(0));
}

void MainWindow::on_actionZPlane_Plus_10_degrees_triggered()
{
    g_Application->Rotate(Vector::VECTOR_UNIT_Z, 10, Vector(0));
}

void MainWindow::on_actionZPlane_Minus_10_degrees_triggered()
{
    g_Application->Rotate(Vector::VECTOR_UNIT_Z, -10, Vector(0));

}


void MainWindow::on_actionScale_triggered()
{
    g_Application->scale(2);

}

void MainWindow::on_actionScene_844_triggered()
{
    g_Application->CreateScene08();
    g_Application->DoRayTracing();
    if(!g_Application->rayTracer()->multiThreaded())
    {
        repaint();
    }
}

