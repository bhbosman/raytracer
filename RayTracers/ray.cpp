#include "ray.h"
#include "vector.h"

Ray::Ray(const Vector& dir,
        const Vector& point):
    m_Dir(dir),
    m_Point(point)

{


    m_Inv_direction = Vector(1/ m_Dir.x, 1 / m_Dir.y, 1 / m_Dir.z);
    m_Sign[0] = (m_Inv_direction.x < 0);
    m_Sign[1] = (m_Inv_direction.y < 0);
    m_Sign[2] = (m_Inv_direction.z < 0);
}

const Vector& Ray::dir() const
{
    return m_Dir;
}

const Vector &Ray::direction() const
{
    return m_Dir;

}

const Vector& Ray::origin() const
{
    return m_Point;
}

Vector Ray::pos(const double time) const
{
    return m_Point + (time * m_Dir);
}


const Vector &Ray::inv_direction() const
{
    return m_Inv_direction;
}
