#ifndef RAYTRACING_H
#define RAYTRACING_H

#include "camera.h"
#include "scene.h"
#include "raytracingblock.h"
#include "ray.h"
#include "sceneobject.h"
#include "intersection.h"
#include "pointlight.h"
#include "material.h"



class RayTracing
{

private:
protected:
    bool m_DoBumpMapping;
    bool m_Shadowing;
    bool m_MultiThreaded;
    bool m_Blocks;
    bool m_Reflection;
    bool m_SuperSampling;
    bool m_Interception;
    void CalculateWindowCoordinates
    (RayTracingBlock::ptr_vec &data,
     const PixelBuffer::ptr& pixelBuffer,
     const Camera::ptr &camera) const;
    void DoNoMultiThreadedRayTracing(
            const RayTracingBlock::ptr_vec &data,
            const PixelBuffer::ptr& pixelBuffer,
            const Camera::ptr &camera,
            const Scene::ptr &scene,
            const double ie,
            const double f) const;

    virtual void DoMultiThreadedRayTracing(
            const RayTracingBlock::ptr_vec &data,
            const PixelBuffer::ptr& pixelBuffer,
            const Camera::ptr &camera,
            const Scene::ptr &scene,
            const double ie,
            const double f) = 0;

public:
   RayTracing();
    void DoRayTracing(const PixelBuffer::ptr& pixelBuffer,
            const Camera::ptr &camera,
            const Scene::ptr &scene,
            const double ie,
            const double f);

    Vector CalculatePixelVector(
            const PixelBuffer::ptr &pixelBuffer,
            const Camera::ptr &camera,
            const int x,
            const int y) const;



    Vector CalculatePixelVector(
            const Camera::ptr &camera,
            const int x,
            const int y,
            const Vector &dx,
            const Vector &dy,
            const double xPercentage,
            const double yPercentage) const;
    Scene::ptr BuildBoxes(const Scene::ptr &scene) const;
    Scene::ptr copyScene(const Scene::ptr &scene) const;

    bool doBumpMapping() const;
    void setDoBumpMapping(bool v);
    bool shadowing() const;
    void setShawowing(bool v);
    void setmultiThreaded(bool v);
    bool multiThreaded() const;
    void setBlocks(bool v);
    bool blocks() const;
    void setReflection(bool v)
    {
        m_Reflection = v;
    }
    bool reflection() const
    {
        return m_Reflection;
    }
    bool superSampling() const
    {
        return m_SuperSampling;

    }
    void setSuperSampling(bool v)
    {
        m_SuperSampling = v;
    }
    bool interception() const
    {
        return m_Interception;
    }
    void setInterception(bool v)

    {
     m_Interception = v;
    }

};




#endif // RAYTRACING_H
