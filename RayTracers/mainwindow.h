#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "pixelbuffer.h"
#include "camera.h"
#include <QWidget>
#include <Qmap>
#include <qevent.h>
#include <qcoreevent.h>
#include "futurewatcherresult.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
private:
    typedef QMainWindow inherited;

    Q_OBJECT



protected:
    void paintEvent(QPaintEvent *);
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *e);

    void keyReleaseEvent(QKeyEvent *e);

    void mousePressEvent(QMouseEvent *e);


    
private slots:

    void on_actionScene_1_triggered();

    void on_actionScene_2_triggered();

    void on_actionScene_3_triggered();

    void on_actionScene_4_triggered();

    void on_actionScene_5_triggered();

    void on_actionScene_6_triggered();

    void on_actionBump_Mapping_triggered();

    void on_actionShadowing_triggered();

    void on_actionScene_7_triggered();

    void on_actionScene_8_triggered();

    void on_actionReset_Camera_triggered();

    void on_actionZoom_OUT_triggered();

    void on_actionZoom_IN_triggered();

    void on_actionCameraMoveLeft_triggered();

    void on_actionCameraMoveRight_triggered();

    void on_actionCameraMoveUp_triggered();

    void on_actionCameraMoveDown_triggered();

    void on_actionCameraMoveForward_triggered();

    void on_actionCameraMoveBackward_triggered();

    void on_actionCameraTransform_triggered();

    void on_actionMulti_Threading_triggered();

    void on_actionSave_large_triggered();

    void on_actionBlock_triggered();

    void on_actionReflection_triggered();


    void on_actionStop_triggered();


    void on_actionXPlaneLeft_triggered();

    void on_actionXPlaneRight_triggered();

    void on_actionYPlane_Plus_10_degrees_triggered();

    void on_actionYPlane_Minus_10_degrees_triggered();

    void on_actionZPlane_Plus_10_degrees_triggered();



    void on_actionZPlane_Minus_10_degrees_triggered();

    void on_actionSuperSampling_triggered();

    void on_actionScale_triggered();

    void on_actionScene_844_triggered();

    void on_actionInterception_triggered();

private:
    Ui::MainWindow *ui;


public slots:
    void futureFinished();
    void futureProgressRangeChanged(int,int);

    void progressValueChanged(int);



};

#endif // MAINWINDOW_H
