#ifndef CUBE_H
#define CUBE_H

#include "sceneobject.h"
#include "vector.h"


class Cube : public SceneObject
{
private:
    typedef SceneObject inherited;
private:
    Vector bounds[2];

    Vector getNormal(const Vector & vec) const;
public:
    Cube(const Material::ptr& m,
            const Vector& minVector,
            const Vector& maxVector);

    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray &r) const override;
    virtual BBox bixIt() const override
    {
        return BBox(true, bounds[0], bounds[1]);
    }
    virtual void Rotate(const Matrix& rotationMatrix) override;
    double radius();

public:
    typedef boost::shared_ptr<Cube> ptr;
    typedef std::vector<Cube> ptr_vec;
};



class CubeContainer: public Cube
{
private:
    typedef Cube inherited;

    SceneObject::ptr_vec m_VisualObjects;
public:
    CubeContainer(
            const TColor& color,
            const Vector& minVector,
            const Vector& maxVector):
        inherited(
            Material::ptr(new StandardMaterial(0.0, 1, color)),

            minVector,
            maxVector)
    {

    }
    virtual ~CubeContainer()
    {

    }
    void AddSceneObject(const SceneObject::ptr& object)
    {
        m_VisualObjects.push_back(object);
    }
    virtual InterSectionType intersect(IntersectionCtx& ctx, const Ray &ray) const override;
    const SceneObject::ptr_vec& sceneObjects() const;

public:
    typedef boost::shared_ptr<CubeContainer> ptr;
    typedef std::vector<CubeContainer> ptr_vec;
};

#endif // CUBE_H
