#include "application.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"
#include "cube.h"

void BVIRayTracerApplication::CreateScene06()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());
    Scene& scene = *m_Scene;




    scene.AddPointLight(new PointLight(TColor(1), Vector(+300, 300, 300), 750));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300, 300, 300), 450));
    scene.AddSceneObject(new Sphere(m_Material03, Vector(  -0,   0,   -400),  80));
    scene.AddSceneObject(new Sphere(m_Material04, Vector( -200,   0,  -400),  80));
    scene.AddSceneObject(new Sphere(m_Material05, Vector(  200,   0,  -400),  80));
    scene.AddSceneObject(new Sphere(m_Material01, Vector(  65,   -40,  -200),  40));
    scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseGreen, Vector(  -65,   -40,  -200),  40));
    scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseRed, Vector(  0,   -60,  -100),  20));

    scene.AddSceneObject(new ChessBoardPlane(m_Material_Chessboard, Vector(0, 1, 0),  Vector(0, -80, 0), true));


}

