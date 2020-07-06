#include "application.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"
#include "cube.h"


void BVIRayTracerApplication::CreateScene02()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());
    Scene& scene = *m_Scene;

    scene.AddPointLight(new PointLight(TColor(1), Vector(+300, 300, 300), 750));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300, 300, 300), 450));
    scene.AddSceneObject(new Sphere(m_Material01, Vector( -80,   0,   -50),  50));
    scene.AddSceneObject(new Sphere(m_Material01, Vector( 80,   0,   -150),  10));
    scene.AddSceneObject(new Sphere(m_Material01, Vector(-0,   0,   -150),  10));
    scene.AddSceneObject(new Sphere(m_Material_RedMatt_NoBumps, Vector(  40,  40,   -150),  10));
    scene.AddSceneObject(new Sphere(m_Material_RedMatt_NoBumps, Vector(  40, -40,   -150),  10));
    scene.AddSceneObject(new Sphere(m_Material03, Vector(40, 0, -150),  10));
    scene.AddSceneObject(new Sphere(m_Material01, Vector(300,   300,   -600),  10));
    scene.AddSceneObject(new Sphere(m_Material01, Vector(300,   300,   -400),  10));
    scene.AddSceneObject(new Sphere(m_Material_RedMatt_NoBumps, Vector(400, 300,   -500),  10));
    scene.AddSceneObject(new Sphere(m_Material_RedMatt_NoBumps, Vector(200, 300,   -500),  10));
    scene.AddSceneObject(new Sphere(m_Material03, Vector(300, 300, -500),  30));
    scene.AddSceneObject(new ChessBoardPlane(m_Material_Chessboard, Vector(0, 1, 0),  Vector(0, -50, 0), true));

}

