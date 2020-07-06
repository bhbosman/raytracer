#include "boxedscene.h"

void BoxedScene::AddSceneObjectBegin()
{
    m_Map.clear();
}

void BoxedScene::AddSceneObjectEnd()
{
    for(MapType_const_iterator it = m_Map.begin(); it != m_Map.end(); ++it)
    {
        const CubeContainer::ptr& cube_ptr = it->second;
        if (cube_ptr.get() != nullptr)
        {
            const CubeContainer& cube = (*cube_ptr);
            if (cube.sceneObjects().size() == 1)
            {
                m_VisualObjects.push_back(cube.sceneObjects().at(0));
            }
            else
            {
                m_VisualObjects.push_back(cube_ptr);
            }
        }
    }
}

void BoxedScene::AddSceneObject(const SceneObject::ptr &object)
{
    BBox box = object->bixIt();
    if (box.canBeBoxed())
    {
        const Vector boxVectorMin(box.minPoint().x / m_BlockSizeX, box.minPoint().y / m_BlockSizeY, box.minPoint().z / m_BlockSizeZ);
        const Vector boxVectorMax(box.maxPoint().x / m_BlockSizeX, box.maxPoint().y / m_BlockSizeY, box.maxPoint().z / m_BlockSizeZ);

        int smallX = (int)floor(boxVectorMin.x);
        int largeX = (int)ceil(boxVectorMax.x);
        int smallY = (int)floor(boxVectorMin.y);
        int largeY = (int)ceil(boxVectorMax.y);
        int smallZ = (int)floor(boxVectorMin.z);
        int largeZ = (int)ceil(boxVectorMax.z);

        static int color = 0;
        int blockCount = abs((smallX - largeX) * (smallY - largeY) * (smallZ - largeZ));
        if (blockCount == 1)
        {
            for(int x = smallX; x < largeX; x++)
            {
                for(int y = smallY; y < largeY; y++)
                {
                    for(int z = smallZ; z < largeZ; z++)
                    {
                        const BoxKey key = {(int)(m_BlockSizeX * x), (int)(m_BlockSizeY * y), (int)(m_BlockSizeZ * z)};
                        MapType::const_iterator it = m_Map.find(key);

                        CubeContainer::ptr tempCube(nullptr);

                        if (it == m_Map.end())
                        {
                            double x1 =  (double)x * m_BlockSizeX;
                            double y1 =  (double)y * m_BlockSizeY;
                            double z1 =  (double)z * m_BlockSizeZ;
                            double x2 =  x1 + m_BlockSizeX;
                            double y2 =  y1 + m_BlockSizeY;
                            double z2 =  z1 + m_BlockSizeZ;

                            const Vector cubeMin(x1, y1, z1);
                            const Vector cubeMax(x2, y2, z2);

                            TColor col = COLOUR_GREEN;
                            if (color % 3 == 1)
                            {
                                col = COLOUR_RED;
                            }
                            if (color % 3 == 2)
                            {
                                col = COLOUR_BLUE;
                            }

                            m_Map[key] = CubeContainer::ptr(new CubeContainer(col, cubeMin, cubeMax));

                            it = m_Map.find(key);
                            if (it != m_Map.end())
                            {
                                tempCube = it->second;
                            }
                            color++;
                        }
                        else
                        {
                             tempCube = it->second;
                        }
                        if (tempCube.get() != nullptr)
                        {
                            tempCube->AddSceneObject(object);
                        }
                    }
                }
            }
        }
        else
        {
            m_VisualObjects.push_back(object);
        }
    }
    else
    {
        m_VisualObjects.push_back(object);
    }

}

void BoxedScene::Rotate(const Matrix &rotationMatrix) const
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

const SceneObject::ptr_vec &BoxedScene::VisualObjects() const
{
    return m_VisualObjects;

}
