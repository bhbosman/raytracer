#include "application.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"
#include "cube.h"



void BVIRayTracerApplication::CreateScene04()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());
    Scene& scene = *m_Scene;

    scene.AddPointLight(new PointLight(TColor(1), Vector(+300, 300, 300), 450));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300, 300, 300), 450));

    scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseGreen, m_StandardMappingPointCalculation, Vector( 40,  40,   40),  10));
    scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseGreen, m_StandardMappingPointCalculation, Vector(40,   20,   40),  10));
    scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseRed, m_StandardMappingPointCalculation, Vector(  0,  40,   0),  10));
    scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseRed, m_StandardMappingPointCalculation, Vector(  0, -40,   0),  10));

    scene.AddSceneObject(new Plane(m_Material_Scatter, m_StandardMappingPointCalculation, Vector::VECTOR_UNIT_Y,  Vector(0, -100, 0), true));
}

