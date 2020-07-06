#include "plane.h"
#include <math.h>
#include "rotation.h"

Plane::Plane(const Material::ptr &m,
        const MappingPointCalculation::ptr &colorCalculation,
        const Vector &normal,
        const Vector& pos, const bool rotate):
    inherited(m, colorCalculation),

    m_Rotate(rotate),
    m_Normal(normal.normalisedCopy()),
    m_D(-pos.dot(normal))
{
}

InterSectionType Plane::intersect(IntersectionCtx &ctx, const Ray& ray) const
{
    double D = m_Normal.dot(ray.dir());
    if (D != 0)
    {
        double tmpDist = -(m_Normal.dot(ray.origin()) + m_D) / D;
        if (tmpDist < ctx.time())
        {
            ctx.Assign(tmpDist, this, getNormal(0), InterSectionType_Outside, Surface2D, m_ColorCalculation);
            return InterSectionType_Outside;
        }

    }
    return InterSectionType_No;
}

Vector Plane::getNormal(const Vector &) const
{
    return m_Normal;
}

void Plane::Rotate(const Matrix &rotationMatrix)// origin)
{
    if (m_Rotate)
    {
        m_Normal = Rotation::PointRotationAroundMatrix(m_Normal, rotationMatrix);
    }
}

BBox Plane::bixIt() const
{
    return BBox(false, 0, 1);
}

