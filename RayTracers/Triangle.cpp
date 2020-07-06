#include "Triangle.h"

Triangle::Triangle(
        const Material::ptr &m,
        const MappingPointCalculation::ptr &colorCalculation):
    inherited(m, colorCalculation),
    m_V0(0,0,0),
    m_V1(0,0,0),
    m_V2(0,0,0),
    m_Normal0(0,1,0),
    m_Normal1(0,1,0),
    m_Normal2(0,1,0)
{
}
Triangle::Triangle(const Material::ptr &m,
        const MappingPointCalculation::ptr &colorCalculation,
        const Vector &v0,
        const Vector &v1,
        const Vector &v2):
    inherited(m, colorCalculation),
    m_V0(v0),
    m_V1(v1),
    m_V2(v2),
    m_Normal0(0),
    m_Normal1(0),
    m_Normal2(0)
{
    Vector line01 = v1 - v0;
    Vector line02 = v2 - v0;
    m_Normal0 = line01.crossProduct(line02);
    m_Normal1 = line01.crossProduct(line02);
    m_Normal2 = line01.crossProduct(line02);
}

InterSectionType Triangle::intersect(IntersectionCtx &ctx, const Ray &ray) const
{
    Vector e1 = m_V1 - m_V0;
    Vector e2 = m_V2 - m_V0;
    Vector p = ray.dir().crossProduct(e2);
    double a = e1.dot(p);
    if ((-1e-7 < a) && (a < 1e-7))
    {
        return InterSectionType_No;
    }
    double f = 1.0 / a;
    Vector s= ray.origin() - m_V0;
    double u = f * (s.dot(p));
    if ((u < 0.0) || (u > 1.0))
    {
        return InterSectionType_No;
    }
    Vector q = s.crossProduct(e1);
    double v = f * (ray.dir().dot(q));
    if ((v < 0.0) || (u + v > 1.0))
    {
        return InterSectionType_No;
    }
    double t = f *(e2.dot(q));

    Vector n = (1.0 - u - v) * m_Normal0 + u * m_Normal1 + v * m_Normal2;
    n.normalise();

    if (t < ctx.time())
    {
        ctx.Assign(t, this, n, InterSectionType_Outside,
                   Surface2D,
                   m_ColorCalculation);
        return InterSectionType_Outside;
    }

    return InterSectionType_No;
}

Vector Triangle::getNormal(const Vector &/*vec*/) const
{
 return m_Normal0;
}

void Triangle::Rotate(const Matrix &/*rotationMatrix*/)
{

}

BBox Triangle::bixIt() const
{
    Vector minVector = m_V0;
    Vector maxVector = m_V0;
    minVector.x = m_V1.x < minVector.x ? m_V1.x: minVector.x;
    minVector.y = m_V1.y < minVector.y ? m_V1.y: minVector.y;
    minVector.z = m_V1.z < minVector.y ? m_V1.z: minVector.z;
    minVector.x = m_V2.x < minVector.x ? m_V2.x: minVector.x;
    minVector.y = m_V2.y < minVector.y ? m_V2.y: minVector.y;
    minVector.z = m_V2.z < minVector.y ? m_V2.z: minVector.x;

    maxVector.x = m_V1.x > maxVector.x ? m_V1.x: maxVector.x;
    maxVector.y = m_V1.y > maxVector.y ? m_V1.y: maxVector.y;
    maxVector.z = m_V1.z > maxVector.y ? m_V1.z: maxVector.z;
    maxVector.x = m_V2.x > maxVector.x ? m_V2.x: maxVector.x;
    maxVector.y = m_V2.y > maxVector.y ? m_V2.y: maxVector.y;
    maxVector.z = m_V2.z > maxVector.y ? m_V2.z: maxVector.z;

    return BBox(true, minVector, maxVector);
}
