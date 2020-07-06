#ifndef RAYTRACINGCONTEXT_NOMULTITHREAD_H
#define RAYTRACINGCONTEXT_NOMULTITHREAD_H
#include "raytracingcontext.h"


class RayTracingContext_NoMultiThread: public RayTracingContext
{
private:
    typedef RayTracingContext inherited;
public:
    RayTracingContext_NoMultiThread(
            const PixelBuffer::ptr &pixelBuffer,
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

};


#endif // RAYTRACINGCONTEXT_NOMULTITHREAD_H
