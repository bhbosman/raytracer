#include "application.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"
#include "cube.h"



void BVIRayTracerApplication::CreateScene03()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());
    Scene& scene = *m_Scene;

    scene.AddPointLight(new PointLight(TColor(1), Vector(+300, 300, 300), 450));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300, 300, 300), 450));

    scene.AddSceneObject(new Sphere(m_Material01, Vector( 40,   0,   0),  10));
    scene.AddSceneObject(new Sphere(m_Material01, Vector(-40,   0,   0),  10));
    scene.AddSceneObject(new Sphere(m_Material_RedMatt_NoBumps, Vector(  0,  40,   0),  10));
    scene.AddSceneObject(new Sphere(m_Material_RedMatt_NoBumps, Vector(  0, -40,   0),  10));
    scene.AddSceneObject(new Sphere(m_Material03, Vector(  0,   0,  0),  10));

    scene.AddSceneObject(new Plane(m_Material_Scatter,m_StandardMappingPointCalculation, Vector::VECTOR_UNIT_X,  Vector(-300, 0, 0), true));
    scene.AddSceneObject(new Plane(m_Material_Scatter, m_StandardMappingPointCalculation, -Vector::VECTOR_UNIT_X,  Vector(300, 0, 0), true));
    scene.AddSceneObject(new ChessBoardPlane(m_Material_Chessboard, Vector::VECTOR_UNIT_Y,  Vector(0, -300, 0), true));
    scene.AddSceneObject(new ChessBoardPlane(m_Material_Chessboard, Vector::VECTOR_UNIT_Y,  Vector(0, 200, 0), true));

}

