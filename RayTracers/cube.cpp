#include "cube.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "intersection.h"
#include "rotation.h"

Cube::Cube(const Material::ptr &m,
           const Vector &minVector,
           const Vector &maxVector):
    inherited(m, MappingPointCalculation::ptr(new StandardMappingPointCalculation()))

{
    bounds[0] = minVector;
    bounds[1] = maxVector;
}

InterSectionType Cube::intersect(IntersectionCtx& ctx, const Ray &r) const
{
    double tmin, tmax, tymin, tymax, tzmin, tzmax;
    tmin = (bounds[r.sign(0)].x - r.origin().x) * r.inv_direction().x;
    tmax = (bounds[1-r.sign(0)].x - r.origin().x) * r.inv_direction().x;
    tymin = (bounds[r.sign(1)].y - r.origin().y) * r.inv_direction().y;
    tymax = (bounds[1-r.sign(1)].y - r.origin().y) * r.inv_direction().y;
    if ( (tmin > tymax) || (tymin > tmax) )
    {
        return InterSectionType_No;
    }
    if (tymin > tmin)
    {
        tmin = tymin;
    }
    if (tymax < tmax)
    {
        tmax = tymax;
    }
    tzmin = (bounds[r.sign(2)].z - r.origin().z) * r.inv_direction().z;
    tzmax = (bounds[1-r.sign(2)].z - r.origin().z) * r.inv_direction().z;
    if ( (tmin > tzmax) || (tzmin > tmax) )
    {
        return InterSectionType_No;
    }
    if (tzmin > tmin)
    {
        tmin = tzmin;
    }
    if (tzmax < tmax)
    {
        tmax = tzmax;
    }
    if (tmin < ctx.time())
    {
        ctx.Assign(tmin, this, -r.dir(),InterSectionType_Outside, Surface3D, m_ColorCalculation);
        return InterSectionType_Outside;
    }


    return InterSectionType_No;
}

Vector Cube::getNormal(const Vector &/*vec*/) const
{
    Vector res(0);
    return res;
}

void Cube::Rotate(const Matrix &/*rotationMatrix*/)
{
    //    m_Origin = Rotation::PointRotationAroundMatrix(m_Origin, rotationMatrix);
}





InterSectionType CubeContainer::intersect(IntersectionCtx &ctx, const Ray &ray) const
{
    InterSectionType result = inherited::intersect(ctx, ray);
//    if(result == InterSectionType_Outside)
//    {
//    }
    return result;
}

const SceneObject::ptr_vec &CubeContainer::sceneObjects() const
{
    return m_VisualObjects;
}
