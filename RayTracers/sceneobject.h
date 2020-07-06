#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include "intersection.h"
#include "ray.h"
#include "vector.h"
#include "material.h"
#include "matrix.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "colorcalculation.h"
#include <map>

class BBox
{
private:
    bool m_CanBeBoxed;
    Vector m_MinPoint;
    Vector m_MaxPoint;

public:
    BBox(const bool canBeBoxed, const Vector& minPoint, const Vector& maxPoint):
        m_CanBeBoxed(canBeBoxed),
        m_MinPoint(minPoint),
        m_MaxPoint(maxPoint)
    {
    }
    bool canBeBoxed()
    {
        return m_CanBeBoxed;
    }
    Vector minPoint()
    {
        return m_MinPoint;
    }
    Vector maxPoint()
    {
        return m_MaxPoint;
    }

public:
    typedef boost::shared_ptr<BBox> ptr;
};
class SceneObject;

class IntersectionCtx
{
private:
    Vector m_RayDirection;
    Vector m_RayOrigin;
    unsigned char* m_SceneObject;
    double m_Time;
    Vector m_Normal;
    InterSectionType m_InterSectionType;
    SurfaceD m_SurfaceD;
    MappingPointCalculation::ptr m_ColorCalculation;

public:
    IntersectionCtx(
            const Vector& rayDirection,
            const Vector& rayOrigin);

    void Assign(
            const double objectTime,
            const SceneObject* a,
            const Vector& normal,
            const InterSectionType interSectionType,
            const SurfaceD surfaceD,
            const MappingPointCalculation::ptr& colorCalculation);
    const SceneObject* sceneObject() const;
    double time() const;
    const Vector& rayDirection() const;

    const Vector& rayOrigin() const;
    const Vector& normal() const;
    const Vector calculatePos() const;
    InterSectionType interSectionType() const;
    SurfaceD surfaceD() const;
    const MappingPointCalculation::ptr& colorCalculation() const;
};






class SceneObject
{
public:
    typedef boost::shared_ptr<SceneObject> ptr;
    typedef std::vector<ptr> ptr_vec;
private:
    Material::ptr m_Material;
protected:
    MappingPointCalculation::ptr m_ColorCalculation;

public:
    //    vo/*id ff( Ctx& abc)
    //    {
    //        SceneObject* f = this;
    //        abc.set_dd(f);

    //    }*/

    SceneObject(
            const Material::ptr &m,
            const MappingPointCalculation::ptr& colorCalculation);
    virtual ~SceneObject();
    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray& ray) const = 0;
    virtual BBox bixIt() const = 0;
    virtual void Rotate(const Matrix& rotationMatrix) = 0;
//    virtual Vector getNormal(const Vector& point) const = 0;
    const Material::ptr &material() const;


    // To be removed....
//    virtual bool intersectOutside(const Ray& ray) = 0;

};



#endif // SCENEOBJECTS_H
