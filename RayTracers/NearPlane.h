#ifndef NEARPLANE_H
#define NEARPLANE_H


#include "vector.h"

struct NearPlane
{
    Vector m_TopLeft;
    Vector m_TopRight;
    Vector m_BottomLeft;
    Vector m_BottomRight;
};
#endif // NEARPLANE_H
