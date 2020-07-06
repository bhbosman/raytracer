#include "raytracingcontext_nomultithread.h"

RayTracingContext_NoMultiThread::RayTracingContext_NoMultiThread(
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
        const bool interception
        ): inherited(
               pixelBuffer,
               camera,
               scene,
               ie,
               f,
               rayTracingBlock,
               doBumpMapping,
               shadowing,
               reflection,
               superSampling,
               interception)
{
}

