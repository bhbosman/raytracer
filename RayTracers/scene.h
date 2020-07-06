#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "sceneobject.h"
#include "pointlight.h"
#include <map>
#include "cube.h"
#include "intersectionwithsceneobject.h"

class Scene
{
private:
    PointLight::ptr_vec m_PointLights;
public:
    Scene();
    virtual ~Scene();
    void ClearAll();
    void ClearPointLights();
    virtual void ClearScene();
    virtual void AddSceneObject(const SceneObject::ptr& object) = 0;
    void AddPointLight(const PointLight::ptr &object);
    void AddSceneObject(SceneObject *object);
    void AddPointLight(PointLight *object);
    void Rotate(const Vector &axis, const double degrees, const Vector& origin) const;
    void scale(const double scale) const;

    virtual void Rotate(const Matrix& rotationMatrix) const = 0;
    virtual const SceneObject::ptr_vec &VisualObjects() const = 0;

    const PointLight::ptr_vec& PointLights() const ;
public:
   typedef boost::shared_ptr<Scene> ptr;
   typedef std::vector<ptr> ptr_vec;

    InterSectionType SendRayToScene(const Ray &ray) const;
    InterSectionType SendRayToScene(IntersectionCtx &ctx, const Ray &ray) const;
};
#endif // SCENE_H
