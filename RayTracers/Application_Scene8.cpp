#include "application.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"
#include "mesh.h"
#include "meshtriangle.h"
#include "cube.h"

void BVIRayTracerApplication::CreateScene08()
{
    ClearScene();
    m_Camera = Camera::ptr(
                new Camera(
                    Vector(-1, 1, 1),
                    Vector(-1,-1, 1),
                    Vector(0, 0, -1), 100,
                    (double)(defaultCameraPixelWidth() / (double)defaultCameraPixelHeight())));

    Scene& scene = *m_Scene;
    scene.AddPointLight(new PointLight(TColor(1), Vector(0, 0, 300), 450));
    scene.AddSceneObject(new ChessBoardPlane(m_Material_Chessboard, Vector::VECTOR_UNIT_Y,  Vector(0, -100, 0), true));
    Mesh* mesh = new Mesh(m_Material_RedMatt_NoBumps, m_StandardMappingPointCalculation);
    mesh->readPLYFile();
    scene.AddSceneObject(mesh);
}

