#include "sceneobject.h"
#include "intersection.h"
#include "ray.h"
#include "vector.h"

const Material::ptr& SceneObject::material() const
{
    return m_Material;
}

SceneObject::SceneObject(
        const Material::ptr &m,
        const MappingPointCalculation::ptr &colorCalculation):
    m_Material(m),
    m_ColorCalculation(colorCalculation)
{
}

SceneObject::~SceneObject()
{
}



IntersectionCtx::IntersectionCtx(const Vector &rayDirection, const Vector &rayOrigin):
    m_RayDirection(rayDirection),
    m_RayOrigin(rayOrigin),
    m_SceneObject(nullptr),
    m_Time(MAXFLOAT),
    m_InterSectionType(InterSectionType_No),
    m_SurfaceD(Surface2D),
    m_ColorCalculation(nullptr)
{
}

void IntersectionCtx::Assign(const double objectTime, const SceneObject *a, const Vector &normal, const InterSectionType interSectionType, const SurfaceD surfaceD, const MappingPointCalculation::ptr &colorCalculation)



{
    if (objectTime < m_Time)
    {
        m_SceneObject = (unsigned char*)a;
        m_Time = objectTime;
        m_Normal = normal;
        m_InterSectionType = interSectionType;
        m_SurfaceD = surfaceD;
        m_ColorCalculation = colorCalculation;
    }
}

const SceneObject *IntersectionCtx::sceneObject() const
{
    return (SceneObject*)m_SceneObject;
}

double IntersectionCtx::time() const
{
    return m_Time;
}

const Vector &IntersectionCtx::rayDirection() const
{
    return m_RayDirection;
}

const Vector &IntersectionCtx::normal() const
{
    return m_Normal;
}

const Vector IntersectionCtx::calculatePos() const
{
    return m_RayOrigin + (m_Time * m_RayDirection);
}

InterSectionType IntersectionCtx::interSectionType() const
{
    return m_InterSectionType;
}

SurfaceD IntersectionCtx::surfaceD() const
{
    return m_SurfaceD;
}

const MappingPointCalculation::ptr &IntersectionCtx::colorCalculation() const
{
    return m_ColorCalculation;
}


const Vector &IntersectionCtx::rayOrigin() const
{
    return m_RayOrigin;
}
