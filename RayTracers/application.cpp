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
#include "normalscene.h"
#include "qraytracing.h"


BVIRayTracerApplication::BVIRayTracerApplication(int &argc, char **argv, int width, int height):
    inherited(argc, argv),
    m_Buffer(new PixelBuffer(width, height)),
    m_Camera(BVIRayTracerApplication::defaultCamera()),
    m_Scene(new NormalScene()),
    m_RayTracer(new QRayTracing()),
    m_Material01(new StandardMaterial(1.0, 0.5, COLOUR_GREEN)),
    m_Material_RedMatt_NoBumps(new StandardMaterial(0.0, 1, COLOUR_RED)),
    m_Material_RedMatt_WithBumps(new StandardMaterial(0.0, 1, COLOUR_RED)),
    m_Material03(new StandardMaterial(1.0, 0.5, COLOUR_BLUE)),
    m_Material04(new StandardMaterial(1.0, 0.5, COLOUR_YELLOW)),
    m_Material05(new StandardMaterial(1.0, 0.5, COLOUR_WHITE)),
    m_Material_Chessboard(new ChessBoardMaterial(1.0, 0.5, COLOUR_WHITE, COLOUR_BLACK)),
    m_Material_Scatter(new ScatterBoardMaterial(1.0, 0.5, COLOUR_RED, COLOUR_GREEN)),
    m_Material_PerlinNoiseRed(new PerlinNoiseMaterial(0.0, 1.0, COLOUR_RED)),
    m_Material_PerlinNoiseBlue(new PerlinNoiseMaterial(0.0, 1.0, COLOUR_BLUE)),
    m_Material_PerlinNoiseGreen(new PerlinNoiseMaterial(0.0, 1.0, COLOUR_GREEN)),
    m_Material_PerlinNoiseWhite(new PerlinNoiseMaterial(0.0, 1.0, COLOUR_WHITE)),

    m_Material_Wordmap(new TextureMaterial(0.0, 0.5, ":/WorldMap/WorldMap")),
    m_Material_Moon(new TextureMaterial(0.0, 0.5, ":/WorldMap/MoonSurface")),
    m_Material_Sun(new TextureMaterial(0.0, 0.5, ":/WorldMap/Sun")),

    m_Material_Galaxy(new TextureMaterial(0.0, 0.5, ":/WorldMap/Galaxy")),
    m_StandardMappingPointCalculation(new StandardMappingPointCalculation()),
//    m_NonReflectviceGray(new Material(1, 0.5, COLOUR_GREY, false)),
    m_Ie(0.02),
    m_F(330)
{
//    new TextureMaterial(0, 0, "ddd");
    CheckAsserts(argc, argv);
    CreateScene01();
    DoRayTracing();
}

void BVIRayTracerApplication::CreateScene01()
{
    ClearScene();
    m_Camera = Camera::ptr(defaultCamera());

    Scene& scene = *m_Scene;

    scene.AddPointLight(new PointLight(TColor(1), Vector(+300, 300, 300), 450));
    scene.AddPointLight(new PointLight(TColor(1), Vector(-300, 300, 300), 450));


    Vector origin(-40, -40, -40);
    Vector axis(0, 1, 0);
    axis.normalise();
    double radius = 15;
    MappingPointCalculation* calc =  new Mapping3DTo2DPointInSphere(axis, origin, radius, true);
    MappingPointCalculation::ptr calc_ptr = MappingPointCalculation::ptr(calc);
    scene.AddSceneObject(new Sphere(m_Material_Wordmap, calc_ptr, origin, radius));



    origin = Vector(40, 40, 40);
    axis = Vector(0, 1, 0);
    axis.normalise();
    radius = 5;
    calc =  new Mapping3DTo2DPointInSphere(axis, origin, radius, true);
    calc_ptr = MappingPointCalculation::ptr(calc);
    scene.AddSceneObject(new Sphere(m_Material_Moon, calc_ptr, origin, radius));



    origin = Vector(0, 0, 0);
    axis = Vector(0, 1, 0);
    axis.normalise();
    radius = 22;
    calc =  new Mapping3DTo2DPointInSphere(axis, origin, radius, false);
    calc_ptr = MappingPointCalculation::ptr(calc);
    scene.AddSceneObject(new Sphere(m_Material_Sun, calc_ptr, origin, radius));



    scene.AddSceneObject(SceneObject::ptr(new Plane(
                                              m_Material_Galaxy,
                                              MappingPointCalculation::ptr(new Mapping3DTo2DPointInPlane(Vector(0, 1, 0))),
                                              Vector(0, 1, 0),  Vector(0, -150, 0), false)));





}
void BVIRayTracerApplication::CreateScene09()
{
    ClearScene();
    Scene& scene = *m_Scene;
    scene.AddPointLight(new PointLight(TColor(1), Vector(+300, 300, 300), 450));

    int increment = 20;

    for(int x = -50; x <= 100; x+= increment)
    {
        for(int y = -50; y <= 100; y += increment)
        {
            for(int z = - 50; z <= 100; z += increment)
            {
                scene.AddSceneObject(SceneObject::ptr(new Sphere(m_Material01, Vector(x,  y,   z),  5)));
            }

        }
    }


    scene.AddSceneObject(SceneObject::ptr(new ChessBoardPlane(m_Material_Chessboard, Vector(0, 1, 0),  Vector(0, -500, 0), true)));

//    scene.AddSceneObject(new Sphere(m_Material01, m_StandardMappingPointCalculation, Vector( 40,  0,   0),  40));

}







void BVIRayTracerApplication::ClearScene()
{
    m_Buffer->clear();
    m_Scene->ClearScene();
}
void BVIRayTracerApplication::saveImage(const QString& filename) const
{
    m_Buffer->save(filename);

}

void BVIRayTracerApplication::RotateX(const double degrees, const Vector& origin) const
{
    m_Scene->Rotate(Vector::VECTOR_UNIT_X, degrees, origin);
}

void BVIRayTracerApplication::RotateY(const double degrees, const Vector& origin) const
{
    m_Scene->Rotate(Vector::VECTOR_UNIT_Y, degrees, origin);
}

void BVIRayTracerApplication::RotateZ(const double degrees, const Vector& origin) const
{
    m_Scene->Rotate(Vector::VECTOR_UNIT_Z, degrees, origin);
}

void BVIRayTracerApplication::RotateAxis(const Vector &axis, const double degrees, const Vector& origin) const
{
    m_Scene->Rotate(axis, degrees, origin);
}

const Scene::ptr &BVIRayTracerApplication::scene() const
{
    return m_Scene;
}

void BVIRayTracerApplication::Rotate(const Vector &axis, const double degrees, const Vector& origin) const
{
    m_Buffer->clear();
    m_Scene->Rotate(axis, degrees, origin);
    DoRayTracing();
}

void BVIRayTracerApplication::scale(const double scale) const
{
    m_Buffer->clear();
    m_Scene->scale(scale);
    DoRayTracing();

}

const Camera::ptr &BVIRayTracerApplication::camera() const
{
    return m_Camera;
}

double BVIRayTracerApplication::ie() const
{
    return m_Ie;
}

double BVIRayTracerApplication::f() const
{
    return m_F;
}

const QRayTracing::shared_ptr &BVIRayTracerApplication::rayTracer() const
{
    return m_RayTracer;
}

int BVIRayTracerApplication::defaultCameraPixelHeight()
{
    return 900;
}

int BVIRayTracerApplication::defaultCameraPixelWidth()
{
    return 1200;
}

Camera *BVIRayTracerApplication::defaultCamera()
{
    return defaultCamera(BVIRayTracerApplication::defaultCameraPixelWidth(), BVIRayTracerApplication::defaultCameraPixelHeight());
}

Camera *BVIRayTracerApplication::defaultCamera(int pixelWidth, int pixelHeight)
{

    return new Camera(
                Vector(-4, 3, 120),
                Vector(-4,-3, 120),
                Vector(0, 0, -1), 5,
                (double)(pixelWidth) / (double)pixelHeight);
}

void BVIRayTracerApplication::resetCamera()
{
    m_Camera = Camera::ptr(defaultCamera());
}

void BVIRayTracerApplication::DoRayTracing() const
{
    m_RayTracer->DoRayTracing(m_Buffer, m_Camera, m_Scene, m_Ie, m_F);
}

void BVIRayTracerApplication::CheckAsserts(int &argc, char **argv)
{

    testing::InitGoogleTest(&argc, argv);
    int abc = RUN_ALL_TESTS();
    if (abc == 0)
    {
    }

    assert(sizeof(PixelData) == m_Buffer->bytesPerPixel());
}


PixelBuffer::ptr BVIRayTracerApplication::Buffer()
{
    return m_Buffer;
}
// globals
BVIRayTracerApplication* g_Application;
Material::ptr g_Space(new StandardMaterial(0, 0, TColor(0)));
