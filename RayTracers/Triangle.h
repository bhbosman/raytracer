#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "sceneobject.h"
#include "intersection.h"
#include "ray.h"
#include "vector.h"

class Triangle: public SceneObject
{
private:
    typedef SceneObject inherited;
    Vector getNormal(const Vector & vec) const;
protected:
    Vector m_V0;
    Vector m_V1;
    Vector m_V2;
    Vector m_Normal0;
    Vector m_Normal1;
    Vector m_Normal2;


public:
    Triangle(
            const Material::ptr& m,
            const MappingPointCalculation::ptr &colorCalculation);

    Triangle(
            const Material::ptr& m,
            const MappingPointCalculation::ptr &colorCalculation,
            const Vector& v0,
            const Vector& v1,
            const Vector& v2);
    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray &ray) const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
    virtual BBox bixIt() const override;
};
#endif // TRIANGLE_H
