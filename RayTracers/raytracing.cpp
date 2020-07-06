#include "raytracing.h"
#include "boxedscene.h"
#include "raytracingcontext.h"
#include "raytracingcontext_nomultithread.h"
#include "normalscene.h"

RayTracing::RayTracing():
    m_DoBumpMapping(false),
    m_Shadowing(false),
    m_MultiThreaded(true),
    m_Blocks(false),
    m_Reflection(false),
    m_Interception(false)
{

}


Vector RayTracing::CalculatePixelVector(
        const Camera::ptr &camera,
        const int x,
        const int y,
        const Vector& dx,
        const Vector& dy,
        const double xPercentage,
        const double yPercentage) const
{
    return camera->NearPlane().m_TopLeft
            + (((double)x + xPercentage) *dx)
            + (((double)y + yPercentage) * dy);

}

Scene::ptr RayTracing::BuildBoxes(const Scene::ptr &scene) const
{
    const BoxedScene::ptr result(new BoxedScene(100, 100, 1000));
    for(
        PointLight::ptr_vec::const_iterator it = scene->PointLights().begin();
        it != scene->PointLights().end();
        it++)
    {
        result->AddPointLight((*it));
    }
    result->AddSceneObjectBegin();
    for(
        SceneObject::ptr_vec::const_iterator it = (*scene).VisualObjects().begin();
        it != scene->VisualObjects().end();
        ++it)
    {
        result->AddSceneObject(*it);
    }
    result->AddSceneObjectEnd();
    //
    return result;
}


Scene::ptr RayTracing::copyScene(const Scene::ptr &scene) const
{
    const Scene::ptr result(new NormalScene());
    for(
        PointLight::ptr_vec::const_iterator it = scene->PointLights().begin();
        it != scene->PointLights().end();
        it++)
    {
        result->AddPointLight((*it));
    }
    for(
        SceneObject::ptr_vec::const_iterator it = (*scene).VisualObjects().begin();
        it != scene->VisualObjects().end();
        ++it)
    {
        result->AddSceneObject(*it);
    }
    //
    return result;
}


Vector RayTracing::CalculatePixelVector(
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera,
        const int x,
        const int y) const
{
    Vector pixelWidthVector = camera->NearPlane().m_TopRight - camera->NearPlane().m_TopLeft;
    pixelWidthVector /= (double)pixelBuffer->width();
    Vector pixelHeightVector = camera->NearPlane().m_BottomLeft - camera->NearPlane().m_TopLeft;
    pixelHeightVector /= (double)pixelBuffer->height();
    //
    return CalculatePixelVector(camera, x, y, pixelWidthVector, pixelHeightVector, 0.5, 0.5);
}

void RayTracing::CalculateWindowCoordinates(
        RayTracingBlock::ptr_vec &data,
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera) const
{
    Vector pixelWidthVector = camera->NearPlane().m_TopRight - camera->NearPlane().m_TopLeft;
    pixelWidthVector /= (double)pixelBuffer->width();
    Vector pixelHeightVector = camera->NearPlane().m_BottomLeft - camera->NearPlane().m_TopLeft;
    pixelHeightVector /= (double)pixelBuffer->height();

    for(int outerY = 0; outerY < pixelBuffer->height(); outerY += _RayTracingBlockSize_)
    {
        for(int outerX = 0; outerX < pixelBuffer->width(); outerX += _RayTracingBlockSize_)
        {
            RayTracingBlock *block = new RayTracingBlock(outerX, outerY, _RayTracingBlockSize_, _RayTracingBlockSize_,  pixelBuffer);
            data.push_back(RayTracingBlock::ptr(block));
            block->setDeltaPixelWidthVector(pixelWidthVector);
            block->setDeltaPixelHeightVector(pixelHeightVector);

            for(int innerY = outerY; innerY < outerY + _RayTracingBlockSize_; innerY++)
            {
                for(int innerX = outerX; innerX < outerX + _RayTracingBlockSize_; innerX++)
                {
                    Vector v = CalculatePixelVector(camera, innerX, innerY, pixelWidthVector, pixelHeightVector, 0.5, 0.5);
                    block->setCoordinateData(innerX - outerX, innerY - outerY, v);
                }
            }
        }
    }

}


bool RayTracing::doBumpMapping() const
{
    return m_DoBumpMapping;
}

void RayTracing::setDoBumpMapping(bool v)
{
    m_DoBumpMapping = v;
}

bool RayTracing::shadowing() const
{
    return m_Shadowing;
}

void RayTracing::setShawowing(bool v)
{
    m_Shadowing = v;
}

void RayTracing::setmultiThreaded(bool v)
{
    m_MultiThreaded = v;
}

bool RayTracing::multiThreaded() const
{
    return m_MultiThreaded;
}

void RayTracing::setBlocks(bool v)
{
    m_Blocks =  v;
}

bool RayTracing::blocks() const
{
    return m_Blocks;
}

void RayTracing::DoNoMultiThreadedRayTracing(
        const RayTracingBlock::ptr_vec& data,
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera,
        const Scene::ptr &scene,
        const double ie,
        const double f) const
{
    for(RayTracingBlock::ptr_vec::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        const RayTracingBlock::ptr entry_ptr = *it;

        RayTracingContext_NoMultiThread ptr(pixelBuffer, camera, scene, ie, f, entry_ptr, m_DoBumpMapping, m_Shadowing, m_Reflection, m_SuperSampling, m_Interception);
        ptr.runInternal();
    }
}

void RayTracing::DoRayTracing(
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera,
        const Scene::ptr &scene,
        const double ie,
        const double f)
{
    RayTracingBlock::ptr_vec data;
    CalculateWindowCoordinates(data, pixelBuffer, camera);

    Scene::ptr newScene;
    if (m_Blocks && m_MultiThreaded)
    {
        newScene = BuildBoxes(scene);
    }
    else if(m_MultiThreaded)
    {
        newScene = copyScene(scene);
    }
    else
    {
        newScene = scene;
    }

    if(m_MultiThreaded)
    {
        DoMultiThreadedRayTracing(data, pixelBuffer, camera, newScene, ie, f);
    }
    else
    {
        DoNoMultiThreadedRayTracing(data, pixelBuffer, camera, newScene, ie, f);
    }
}



