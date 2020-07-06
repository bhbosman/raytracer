#ifndef SPHERE_H
#define SPHERE_H
#include "sceneobject.h"
#include "vector.h"

class Sphere : public SceneObject
{
private:
    typedef SceneObject inherited;
private:
    Vector m_Origin;
    double m_Radius;
    double m_SquareRadius;
    double m_InverseRadius;
    Vector getNormal(const Vector & vec) const;
public:
    Sphere(
            const Material::ptr& m,
            const Vector& origin,
            const double radius);
    Sphere(
            const Material::ptr& m,
            const MappingPointCalculation::ptr& calculation,
            const Vector& origin,
            const double radius);

    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray &ray) const override;
    InterSectionType intersect(IntersectionCtx &ctx, const Ray &ray, const Vector& offset) const;
    virtual void Rotate(const Matrix& rotationMatrix) override;
    virtual BBox bixIt() const override;

    double radius();

public:
    typedef boost::shared_ptr<Sphere> ptr;
    typedef std::vector<ptr> ptr_vec;
};

#endif // SPHERE_H
