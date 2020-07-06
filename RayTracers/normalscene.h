#ifndef NORMALSCENE_H
#define NORMALSCENE_H


#include <vector>
#include "sceneobject.h"
//#include "pointlight.h"
//#include <map>
//#include "intersectionwithsceneobject.h"
#include "scene.h"
class NormalScene: public virtual Scene
{
private:
    typedef Scene inherited;
    SceneObject::ptr_vec m_VisualObjects;
public:
    NormalScene(): inherited()
    {

    }
    virtual void ClearScene()
    {
        inherited::ClearScene();
        m_VisualObjects.clear();
    }

    virtual void AddSceneObject(const SceneObject::ptr& object) override;
    virtual void Rotate(const Matrix& rotationMatrix) const override;
    virtual const SceneObject::ptr_vec &VisualObjects() const override;
    virtual BBox bixIt() const;

};



#endif // NORMALSCENE_H
