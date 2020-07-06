#include "raytracingcontext.h"
#include "phonelightingmodelcalculation.h"
#include "phonglightingmodelhelper.h"

RayTracingContext::RayTracingContext(
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera,
        const Scene::ptr &scene,
        const double ie,
        const double f,
        const RayTracingBlock::ptr& rayTracingBlock,
        const bool doBumpMapping,
        const bool shadowing,
        const bool reflection,
        const bool superSampling,
        const bool interception):
    m_PixelBuffer(pixelBuffer),
    m_Camera(camera),
    m_Scene(scene),
    m_Ie(ie),
    m_F(f),
    m_DoBumpMapping(doBumpMapping),
    m_Reflection(reflection),
    m_BumpMapping(0.2),
    m_Shadowing(shadowing),
    m_RayTracingBlock(rayTracingBlock),
    m_SuperSampling(superSampling),
    m_Interception(interception)
{

}

RayTracingContext::RayTracingContext(
        const PixelBuffer::ptr &pixelBuffer,
        const Camera::ptr &camera,
        const Scene::ptr &scene,
        const double ie,
        const double f,
        const bool doBumpMapping,
        const bool shadowing,
        const bool reflection,
        const bool superSampling,
        const bool interception):
    m_PixelBuffer(pixelBuffer),
    m_Camera(camera),
    m_Scene(scene),
    m_Ie(ie),
    m_F(f),
    m_DoBumpMapping(doBumpMapping),
    m_Reflection(reflection),
    m_BumpMapping(0.2),
    m_Shadowing(shadowing),
    m_SuperSampling(superSampling),
    m_Interception(interception)
{

}



RayTracingContext::~RayTracingContext()
{
}





void RayTracingContext::runInternal()
{

    RayTracingBlock& entry = (*m_RayTracingBlock);
    const Camera& camera_local = (*m_Camera);
    for(int x = 0; x < _RayTracingBlockSize_; x++)
    {
        for(int y = 0; y < _RayTracingBlockSize_; y++)
        {
            Vector windowCoordinate = entry.coordinateData(x, y, 0.5, 0.5);
            Vector direction = windowCoordinate - camera_local.cameraPoint();
            direction.normalise();
            IntersectionCtx intersectionCtx(direction, camera_local.cameraPoint());
            TColor c = DoRayTracingInternal2(
                        intersectionCtx,
                        camera_local.cameraPoint(),
                        direction);
            entry.setColorData(x, y, c);
        }
    }
    if (m_SuperSampling)
    {
        bool resetmap[_RayTracingBlockSize_][_RayTracingBlockSize_];
        memset(resetmap, 0, sizeof(resetmap));

        for(int x = 0; x < _RayTracingBlockSize_-1; x++)
        {
            for(int y = 0; y < _RayTracingBlockSize_- 1; y++)
            {
                TColor base =  entry.colorData(x, y);
                TColor other = entry.colorData(x, y + 1);
                if ((base -  other).length() > 0.01)
                {
                    resetmap[x][y] = true;
                    resetmap[x][y+1] = true;
                }
                other = entry.colorData(x+1, y);
                if ((base -  other).length() > 0.01)
                {
                    resetmap[x][y] = true;
                    resetmap[x+1][y] = true;
                }
                other = entry.colorData(x+1, y+1);
                if ((base -  other).length() > 0.01)
                {
                    resetmap[x][y] = true;
                    resetmap[x+1][y+1] = true;
                }
            }
        }
        double samples = 0.25;
        for(int x = 0; x < _RayTracingBlockSize_-1; x++)
        {
            for(int y = 0; y < _RayTracingBlockSize_- 1; y++)
            {
                if(resetmap[x][y])
                {
                    int count = 0;
                    TColor c(0);
                    for(double xPercentage = samples; xPercentage < 1.0; xPercentage += samples)
                    {
                        for(double yPercentage = samples; yPercentage < 1.0; yPercentage += samples)
                        {
                            Vector windowCoordinate = entry.coordinateData(x, y, xPercentage, yPercentage);
                            Vector direction = windowCoordinate - camera_local.cameraPoint();
                            direction.normalise();
                            IntersectionCtx intersectionCtx(direction, camera_local.cameraPoint());
                            count++;
                            c += DoRayTracingInternal2(
                                        intersectionCtx,
                                        camera_local.cameraPoint(),
                                        direction);

                        }

                    }


                    c /= count;

                    entry.setColorData(x, y, c);

                }

            }
        }
    }

    entry.Paint();
}

TColor RayTracingContext::DoRayTracingInternal2(
        IntersectionCtx &intersectionCtx,
        const Vector& origin,
        const Vector& direction
        ) const
{
    Vector origin_local = origin;
    Vector direction_local = direction;


    TColor result(0, 0, 0);
    int n = 0;
    double cumulativeReflect = 1;
    int reflectionCount = 1;
    if (m_Reflection)
    {
        reflectionCount = 8;
    }
    while (true)
    {
        if (reflectionCount == n)
        {
            break;
        }
        n++;

        Ray r(direction_local, origin_local);
        //
        IntersectionCtx ctx_local(direction_local, origin_local);
        InterSectionType interSectionWithSceneObject = m_Scene->SendRayToScene(ctx_local, r);
        if (interSectionWithSceneObject != InterSectionType_No)
        {
            if (ctx_local.sceneObject() != nullptr)
            {
                intersectionCtx.Assign(
                            ctx_local.time(),
                            ctx_local.sceneObject(),
                            ctx_local.normal(),
                            ctx_local.interSectionType(),
                            ctx_local.surfaceD(),
                            ctx_local.colorCalculation());


                Vector surfacePoint = ctx_local.calculatePos();
                Vector surfaceNormal = ctx_local.normal();
                if (m_DoBumpMapping)
                {
                    Vector delta = m_BumpMapping.calculateBump(surfacePoint);
                    surfaceNormal += delta;
                    surfaceNormal.normalise();
                }

                TColor c= CalculateLightColor(
                            m_Scene,
                            ctx_local,
                            surfaceNormal,
                            surfacePoint,
                            r.origin(),
                            m_Ie,
                            m_F) * cumulativeReflect;

                result  += c;

                cumulativeReflect *= ctx_local.sceneObject()->material().get()->psValue();


                //next iteration
                origin_local = surfacePoint;
                direction_local = direction_local -2 * (direction_local * surfaceNormal) * surfaceNormal;
                direction_local.normalise();
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    //
    return result;
}

int RayTracingContext::leftPixel() const
{
    return m_RayTracingBlock->leftPixel();
}

int RayTracingContext::topPixel() const
{
    return m_RayTracingBlock->topPixel();
}

int RayTracingContext::witdh() const
{
    return m_RayTracingBlock->width();
}

int RayTracingContext::height() const
{
    return m_RayTracingBlock->width();
}

TColor RayTracingContext::CalculateLightColor(
        const Scene::ptr &scene,
        const IntersectionCtx ctx,
        const Vector& surfaceNormal,
        const Vector& surfacePoint,
        const Vector& viewerPosition,
        const double ie,
        const double f) const
{
    TColor res = 0;
    for(
        PointLight::ptr_vec::const_iterator it = (*scene).PointLights().begin();
        it != (*scene).PointLights().end();
        it++)
    {
        PointLight light = *(*it);

        Vector lightDirection = surfacePoint - light.position();
        double brightness = 1 / lightDirection.length();
        bool b = false;
        if (m_Interception)
        {
        lightDirection.normalise();
        Ray lightPointRay(lightDirection, light.position());
        IntersectionCtx lightPointCtx(lightDirection, light.position());
        InterSectionType rayIntersection = scene->SendRayToScene(lightPointCtx, lightPointRay);

        b = (rayIntersection != InterSectionType_No);
        if (b)
        {
            Vector point2 =  lightPointCtx.calculatePos();
            Vector delta = point2 - surfacePoint;
            b = delta == Vector(1e-07);
        }
        }
        else
        {
            b = true;
        }
        if (b)
        {
            PhongLightingParameters<TColor> params = PhongLightingModelHelper::CreateColor(
//                        intersectionWithSceneObject,
                        ctx,
                        surfaceNormal,
                        light,
                        ie,
                        f,
                        viewerPosition,
                        surfacePoint);



            double shadowFactor = 1;
            if (m_Shadowing)
            {
                Vector n0 = CoPlanar(params.NUnit(), params.LUnit(), params.VUnit());
                n0.normalise();
                shadowFactor = Blinn(n0, params.LUnit(), params.VUnit());
            }
            TColor c = PhoneLightingModelCalculation<TColor>::Calculate(params);
            res += c * brightness * shadowFactor;
        }
    }
    return res;
}



Vector RayTracingContext::CoPlanar(const Vector &n, const Vector &l, const Vector &v) const
{
    Vector above = (n.dot(l)) * l + (n.dot(v)) * v - (v.dot(l)) * (v.dot(n)) * l - (v.dot(l) * (l.dot(n)) * v);
    double below = 1 - powf(v.dot(l), 2);

    return above / below;
}

double RayTracingContext::Blinn(const Vector &n, const Vector &l, const Vector &v) const
{

    Vector h = (l + v) / ((l + v).length());
    h.normalise();
    Vector h1 = 2 * h.dot(n) * n - h;
    h1.normalise();
    //    Vector h1 = h.reflect(n);//  - 2 * h.dot(n) * n;

    double v_DOT_h1 = v.dot(h1);
    double n_DOT_l = n.dot(l);
    double n_DOT_v = n.dot(v);
    double l_DOT_h1 = l.dot(h1);
    double n_DOT_h = n.dot(h);
    double h_DOT_v = h.dot(v);

    if ((v_DOT_h1 >= 0) || (n_DOT_v >= n_DOT_l))
    {
        return 1;
    }
    else if ((v_DOT_h1 < 0) && (l_DOT_h1 >= 0))
    {
        double above = 2 * n_DOT_h * n_DOT_v;
        double below = h_DOT_v;

        return above/below;
    }
    else if ((v_DOT_h1 < 0) && (l_DOT_h1< 0) && (n_DOT_v < n_DOT_l))
    {
        return n_DOT_v / n_DOT_l;
    }
    return 0;
}
