#include "application.h"
#include "raytracing.h"
#include "sphere.h"
#include "gtest/gtest.h"
#include "plane.h"
#include "Plane_Scatter.h"
#include "plane_chessboard.h"
#include "Triangle.h"
#include "PerlinNoise.h"
#include "cube.h"

void BVIRayTracerApplication::CreateScene07()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());
    Scene& scene = *m_Scene;

    scene.AddPointLight(new PointLight(TColor(1), Vector( 300,  300, 300), 800));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300, -300, 300), 450));
    scene.AddPointLight(new PointLight(TColor(1), Vector( 300, -300, 300), 450));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300,  300, 300), 450));

    int c = 0;
    for (int x = -100; x <= 100; x += 20)
    {
        if (x != 0)
        {
            for (int y = -100; y <= 100; y += 20)
            {
                for (int z =-1000; z <= 100; z += 20)
                {
                    c++;
                    switch(c % 4)
                    {

                    case 0:
                        scene.AddSceneObject(new Sphere(m_Material01, Vector( x,   y,   z),  5));
                        break;
                    case 1:
                        scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseBlue, Vector( x,   y,   z),  5));
                        break;

                    case 2:
                        scene.AddSceneObject(new Sphere(m_Material_PerlinNoiseRed, Vector( x,   y,   z),  5));
                        break;
                    case 3:
                        scene.AddSceneObject(new Sphere(m_Material_Scatter, Vector( x,   y,   z),  5));
                        break;
                    }
                }
            }
        }
    }
}

