#ifndef RAY_H
#define RAY_H


#include "vector.h"

class Ray
{
private:
    Vector m_Dir;
    Vector m_Point;
    Vector m_Inv_direction;
    int m_Sign[3];
public:

    Ray(const Vector& dir, const Vector& point);
    const Vector& dir() const;
    const Vector& direction() const;
    const Vector& origin() const;
    Vector pos(const double time) const;
    const Vector& inv_direction() const;
    int sign(int index) const
    {
        return m_Sign[index];
    }

};



#endif // RAY_H
