#ifndef BUMPMAPPING_H
#define BUMPMAPPING_H
#include "vector.h"
class BumpMapping
{
private:
    double m_Epsilon;
public:
    BumpMapping(double ep);
    Vector calculateBump(const Vector& surfacePoint) const;

};

#endif // BUMPMAPPING_H
