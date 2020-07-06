#include "normalscene.h"



BBox NormalScene::bixIt() const
{
    Vector minVector(MAXFLOAT);
    Vector maxVector(-MAXFLOAT);

    for(
        SceneObject::ptr_vec::const_iterator it = VisualObjects().begin();
        it != VisualObjects().end();
        ++it)
    {
        const SceneObject& entry = *(*it);
        BBox bb = entry.bixIt();


        minVector.x = bb.minPoint().x < minVector.x ? bb.minPoint().x: minVector.x;
        minVector.y = bb.minPoint().y < minVector.y ? bb.minPoint().y: minVector.y;
        minVector.z = bb.minPoint().z < minVector.y ? bb.minPoint().z: minVector.z;



        maxVector.x = bb.maxPoint().x > maxVector.x ? bb.maxPoint().x: maxVector.x;
        maxVector.y = bb.maxPoint().y > maxVector.y ? bb.maxPoint().y: maxVector.y;
        maxVector.z = bb.maxPoint().z > maxVector.y ? bb.maxPoint().z: maxVector.z;


    }
    return BBox(true, minVector, maxVector);


}
