#ifndef RAYTRACINGCONTEXT_MULTITHREAD_H
#define RAYTRACINGCONTEXT_MULTITHREAD_H

#include <boost/shared_ptr.hpp>
#include "raytracingcontext.h"
#include <QAtomicInt>
#include <vector>
class RayTracingContext_MultiThread: public RayTracingContext
{
private:
    typedef RayTracingContext inherited;
public:
    RayTracingContext_MultiThread(const PixelBuffer::ptr &pixelBuffer,
            const Camera::ptr &camera,
            const Scene::ptr &scene,
            const double ie,
            const double f,
            const RayTracingBlock::ptr &rayTracingBlock,
            const bool doBumpMapping,
            const bool shadowing,
            const bool reflection, const bool superSampling, const bool interception);
public:
    void add();
    bool remove();
    typedef boost::shared_ptr<RayTracingContext_MultiThread> shared_ptr;
    typedef std::vector<shared_ptr> shared_ptr_vector;
    typedef shared_ptr_vector::const_iterator const_iterator;
};
#endif // RAYTRACINGCONTEXT_MULTITHREAD_H
