#ifndef BOXEDSCENE_H
#define BOXEDSCENE_H


#include <vector>
#include "sceneobject.h"
#include "pointlight.h"
#include <map>
#include "cube.h"
#include "intersectionwithsceneobject.h"
#include "scene.h"
#include "BoxKey.h"



class BoxedScene: public virtual Scene
{
private:
    typedef Scene inherited;
    SceneObject::ptr_vec m_VisualObjects;
    typedef std::map<BoxKey, CubeContainer::ptr> MapType;
    typedef MapType::const_iterator MapType_const_iterator;
    MapType m_Map;
    int m_BlockSizeX;
    int m_BlockSizeY;
    int m_BlockSizeZ;
public:
    BoxedScene(const int blockSizeX, const int blockSizeY, const int blockSizeZ):
    inherited(), m_BlockSizeX(blockSizeX), m_BlockSizeY(blockSizeY), m_BlockSizeZ(blockSizeZ)
    {

    }

    void AddSceneObjectBegin();
    void AddSceneObjectEnd();

    virtual void AddSceneObject(const SceneObject::ptr& object) override;
    virtual void Rotate(const Matrix& rotationMatrix) const;
    virtual const SceneObject::ptr_vec &VisualObjects() const override;

public:
    typedef boost::shared_ptr<BoxedScene> ptr;
};

#endif // BOXEDSCENE_H
