#include "scene.h"
#include "plane.h"
#include "rotation.h"
#include "normalscene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::ClearAll()
{
    ClearPointLights();
    ClearScene();
}

void Scene::ClearPointLights()
{
    m_PointLights.clear();
}

void Scene::ClearScene()
{
    m_PointLights.clear();
}

void Scene::AddSceneObject(SceneObject *object)
{
    SceneObject::ptr x(object);
    AddSceneObject(x);
}

void NormalScene::AddSceneObject(const SceneObject::ptr& object)
{
    m_VisualObjects.push_back(object);
}

void Scene::AddPointLight(PointLight *object)
{
    AddPointLight(PointLight::ptr(object));
}

void Scene::AddPointLight(const PointLight::ptr &object)
{
    m_PointLights.push_back(object);
}

void Scene::Rotate(const Vector &axis, const double degrees, const Vector& origin) const
{
    Matrix M = Rotation::RotationAroundAxisAtOrigin(axis, degrees, origin);
    this->Rotate(M);
}

void Scene::scale(const double scale) const
{
    Matrix M = MatrixHelper::Scale(scale);
    this->Rotate(M);
 }

void NormalScene::Rotate(const Matrix &rotationMatrix) const
{
    for(
        SceneObject::ptr_vec::const_iterator it = m_VisualObjects.begin();
        it != m_VisualObjects.end();
        ++it)
    {
        const SceneObject::ptr& entry = (*it);
        entry->Rotate(rotationMatrix);
    }
}

const SceneObject::ptr_vec &NormalScene::VisualObjects() const
{
    return m_VisualObjects;
}

const PointLight::ptr_vec &Scene::PointLights() const
{
    return m_PointLights;
}





InterSectionType Scene::SendRayToScene(const Ray &ray) const
{
    IntersectionCtx ctx(ray.direction(), ray.origin());
    return  SendRayToScene(ctx, ray);
}

InterSectionType Scene::SendRayToScene(IntersectionCtx& ctx, const Ray &ray) const
{
    InterSectionType smallest = InterSectionType_No;
    for(
        SceneObject::ptr_vec::const_iterator it = VisualObjects().begin();
        it != VisualObjects().end();
        ++it)
    {
        const SceneObject& entry = *(*it);
        IntersectionCtx ctx_local(ray.direction(), ray.origin());
        InterSectionType interSection = entry.intersect(ctx_local, ray);
        if (interSection != InterSectionType_No)
        {
            if (ctx_local.time() > 1e-7)
            {
                switch (interSection)
                {
                case InterSectionType_Outside:
                    if(ctx_local.time() <  ctx.time())
                    {
                        ctx.Assign(
                                    ctx_local.time(),
                                    ctx_local.sceneObject(),
                                    ctx_local.normal(),
                                    ctx_local.interSectionType(),
                                    ctx_local.surfaceD(),
                                    ctx_local.colorCalculation());
                        smallest = interSection;
                    }
                    break;
                case InterSectionType_Inside:
                    break;

                default:
                    break;
                }
            }
        }
    }
    return smallest;
}


