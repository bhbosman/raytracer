#ifndef PLANE_H
#define PLANE_H

#include "sceneobject.h"
#include "intersection.h"
#include "ray.h"
#include "vector.h"

class Plane: public SceneObject
{
private:
    bool m_Rotate;
    typedef SceneObject inherited;
    Vector getNormal(const Vector & vec) const;
protected:
    Vector m_Normal;
    double m_D;

public:
    Plane(
            const Material::ptr& m,
            const MappingPointCalculation::ptr &colorCalculation,
            const Vector& normal,
            const Vector& pos,
            const bool rotate);
    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray &ray)  const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
    virtual BBox bixIt() const override;

};



#endif // PLANE_H
