#include "sphere.h"
#include "vector.h"
#include "ray.h"
#include "material.h"
#include "intersection.h"
#include "rotation.h"

Sphere::Sphere(
        const Material::ptr &m,
        const Vector &origin,
        const double radius):
    inherited(
        m,
        MappingPointCalculation::ptr(new StandardMappingPointCalculation())),
    m_Origin(origin),
    m_Radius(radius),
    m_SquareRadius(radius * radius),
    m_InverseRadius(1.0 / radius)
{

}


Sphere::Sphere(
        const Material::ptr &m,
        const MappingPointCalculation::ptr& calculation,
        const Vector &origin,
        const double radius):
    inherited(
        m,
        calculation),
    m_Origin(origin),
    m_Radius(radius),
    m_SquareRadius(radius * radius),
    m_InverseRadius(1.0 / radius)
{

}


InterSectionType Sphere::intersect(IntersectionCtx &ctx, const Ray &ray) const
{

    return intersect(ctx, ray, Vector(0));
}

InterSectionType Sphere::intersect(IntersectionCtx &ctx, const Ray &ray, const Vector &offset) const

{
    //http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-sphere-intersection/


    Vector rayPointToCentre = m_Origin + offset - ray.origin();

    // does the rayPointToCentre vector and the ray.direction show in the same direction?
    double tca = rayPointToCentre.dot(ray.dir());
    if (tca < 0)
    {
        return InterSectionType_No;
    }
    double squareD = rayPointToCentre.dot(rayPointToCentre) - tca * tca;
    if (squareD > m_SquareRadius)
    {
        return InterSectionType_No;
    }
    double squareTch = m_SquareRadius - squareD;
    double tch = sqrt(squareTch);
    //
    double t0 = tca - tch;
    Vector point = ray.pos(t0);

    if (t0 < ctx.time())
    {
        ctx.Assign(t0, this, getNormal(point),InterSectionType_Outside, Surface3D, m_ColorCalculation);
        return InterSectionType_Outside;
    }
    return InterSectionType_No;
}

Vector Sphere::getNormal(const Vector &vec) const
{
    Vector res = vec - m_Origin;
    res *= m_InverseRadius;
    return res;
}

void Sphere::Rotate(const Matrix &rotationMatrix)
{
    m_Origin = Rotation::PointRotationAroundMatrix(m_Origin, rotationMatrix);
    m_ColorCalculation->Rotate(rotationMatrix);
}

BBox Sphere::bixIt() const
{
    return BBox(
                true,
                Vector(m_Origin.x - m_Radius, m_Origin.y - m_Radius, m_Origin.z - m_Radius),
                Vector(m_Origin.x + m_Radius, m_Origin.y + m_Radius, m_Origin.z + m_Radius));
}

double Sphere::radius()
{
    return m_Radius;
}


