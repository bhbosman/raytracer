#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "camera.h"
#include "pixelbuffer.h"
#include "scene.h"
#include "material.h"
#include "colorcalculation.h"
#include "raytracing.h"
#include "qraytracing.h"


class BVIRayTracerApplication: public QApplication
{
private:
    typedef QApplication inherited;
    PixelBuffer::ptr m_Buffer;
    Camera::ptr m_Camera;
    Scene::ptr m_Scene;
    QRayTracing::shared_ptr m_RayTracer;

    Material::ptr m_Material01;
    Material::ptr m_Material_RedMatt_NoBumps;
    Material::ptr m_Material_RedMatt_WithBumps;
    Material::ptr m_Material03;
    Material::ptr m_Material04;
    Material::ptr m_Material05;
    Material::ptr m_Material06;
    Material::ptr m_Material_Chessboard;
    Material::ptr m_Material_Scatter;
    Material::ptr m_Material_PerlinNoiseRed;
    Material::ptr m_Material_PerlinNoiseBlue;
    Material::ptr m_Material_PerlinNoiseGreen;
    Material::ptr m_Material_PerlinNoiseWhite;
    Material::ptr m_Material_Wordmap;
    Material::ptr m_Material_Moon;
    Material::ptr m_Material_Saturn;
    Material::ptr m_Material_Jupitor;
    Material::ptr m_Material_Sun;
    Material::ptr m_Material_Galaxy;

    MappingPointCalculation::ptr m_StandardMappingPointCalculation;

//    Material::ptr m_NonReflectviceGray;
    double m_Ie;
    double m_F;
    void CheckAsserts(int& argc, char **argv);

public:
    BVIRayTracerApplication(int &argc, char **argv, int width, int height);
    PixelBuffer::ptr Buffer();
    void DoRayTracing() const;
    void CreateScene01();
    void CreateScene02();
    void CreateScene03();
    void CreateScene04();
    void CreateScene05();
    void CreateScene06();
    void CreateScene07();
    void CreateScene08();
    void CreateScene09();
    void ClearScene() ;
    void saveImage(const QString& filename) const;
    void RotateX(const double degrees, const Vector& origin) const ;
    void RotateY(const double degrees, const Vector& origin) const;
    void RotateZ(const double degrees, const Vector& origin) const;
    void RotateAxis(const Vector &axis, const double degrees, const Vector& origin) const;
    const Scene::ptr& scene() const;
    void Rotate(const Vector &axis, const double degrees, const Vector& origin) const;
    void scale(const double scale) const;
    const Camera::ptr& camera() const;
    double ie() const;
    double f() const;
    const QRayTracing::shared_ptr& rayTracer() const;
    static int defaultCameraPixelHeight();
    static int defaultCameraPixelWidth();
    static Camera* defaultCamera();

    static Camera* defaultCamera(int pixelWidth, int pixelHeight);
    void resetCamera();

};

extern BVIRayTracerApplication* g_Application;

#endif // APPLICATION_H
