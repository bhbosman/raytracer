#ifndef RAYTRACINGCONTEXT_H
#define RAYTRACINGCONTEXT_H

#include "scene.h"
#include "pixelbuffer.h"
#include "camera.h"
#include "raytracingblock.h"
#include <boost/shared_ptr.hpp>
#include "intersectionwithsceneobject.h"
#include "bumpmapping.h"

class RayTracingContext
{
    PixelBuffer::ptr m_PixelBuffer;
    Camera::ptr m_Camera;
    Scene::ptr m_Scene;
    double m_Ie;
    double m_F;
    bool m_DoBumpMapping;
    bool m_Reflection;
    BumpMapping m_BumpMapping;
    bool m_Shadowing;
    RayTracingBlock::ptr m_RayTracingBlock;
    bool m_SuperSampling;
    bool m_Interception;

    Vector CoPlanar(const Vector& n, const Vector& l, const Vector& v) const;
    double Blinn(const Vector& n, const Vector& l, const Vector& v) const;
    TColor CalculateLightColor(const Scene::ptr &scene,
            const IntersectionCtx ctx,
            const Vector &surfaceNormal,
            const Vector &surfacePoint,
            const Vector &viewerPosition,
            const double ie,
            const double f) const;

public:
    RayTracingContext(const PixelBuffer::ptr &pixelBuffer,
                      const Camera::ptr &camera,
                      const Scene::ptr &scene,
                      const double ie,
                      const double f,
                      const RayTracingBlock::ptr &rayTracingBlock,
                      const bool doBumpMapping,
                      const bool shadowing,
                      const bool reflection,
                      const bool superSampling,
                      const bool interception);
    RayTracingContext(const PixelBuffer::ptr &pixelBuffer,
                      const Camera::ptr &camera,
                      const Scene::ptr &scene,
                      const double ie,
                      const double f,
                      const bool doBumpMapping,
                      const bool shadowing,
                      const bool reflection,
                      const bool superSampling,
                      const bool interception);

    virtual ~RayTracingContext();
    void runInternal();

    TColor DoRayTracingInternal2(
            IntersectionCtx& intersectionCtx,
            const Vector &origin,
            const Vector &direction) const;
    int leftPixel() const;
    int topPixel() const;
    int witdh() const;
    int height() const;





public:
    typedef boost::shared_ptr<RayTracingContext> shared_ptr;
};




#endif // RAYTRACINGCONTEXT_H
