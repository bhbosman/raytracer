#include "application.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"

#include "Triangle.h"


void BVIRayTracerApplication::CreateScene05()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());
    Scene& scene = *m_Scene;

    scene.AddPointLight(new PointLight(TColor(1), Vector(0, 0, 300), 450));
    scene.AddSceneObject(new Plane(m_Material_Scatter,m_StandardMappingPointCalculation, Vector::VECTOR_UNIT_X,  Vector(-200, 0, 0), true));
    scene.AddSceneObject(new Plane(m_Material_Scatter, m_StandardMappingPointCalculation, -Vector::VECTOR_UNIT_X,  Vector(200, 0, 0), true));
    scene.AddSceneObject(new ChessBoardPlane(m_Material_Chessboard, Vector::VECTOR_UNIT_Y,  Vector(0, -100, 0), true));
    scene.AddSceneObject(new Triangle(m_Material_RedMatt_NoBumps, m_StandardMappingPointCalculation, Vector(0, 10, 20),  Vector(-10, 0, 20), Vector(10, 0, 20)));
}


