#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Color.h"
#include "vector.h"
#include <boost/shared_ptr.hpp>
#include <vector>

class PointLight
{
private:
    TColor m_Color;
    Vector m_Position;
    double m_Ia;
    double m_Id;
    double m_Is;

    TColor m_Color_dot_m_Ia;
    TColor m_Color_dot_m_Id;
    TColor m_Color_dot_m_Is;

public:
    PointLight();
    PointLight(const TColor& color, const Vector& position, const double idis);
    virtual ~PointLight();

    const TColor& color() const;
    const Vector& position() const;
    double iaValue() const;
    double isValue() const;
    double idValue() const;
    const TColor idColor() const;
    const TColor isColor() const;
    const TColor iaColor() const;




 public:
    typedef boost::shared_ptr<PointLight> ptr;
    typedef std::vector<ptr> ptr_vec;
};

#endif // POINTLIGHT_H
