#include "raytracingcontext_multithread.h"

RayTracingContext_MultiThread::RayTracingContext_MultiThread(
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
        const bool interception):
    inherited(pixelBuffer,
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
