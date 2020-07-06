#include "pointlight.h"

PointLight::PointLight():
    m_Color(0),
    m_Position(0),
    m_Ia(0),
    m_Id(0),
    m_Is(0)
{
}

PointLight::PointLight(const TColor &color,
        const Vector &position,
        const double idis):
    m_Color(color),
    m_Position(position),
    m_Ia(0),
    m_Id(idis),
    m_Is(idis),
    m_Color_dot_m_Ia(0),
    m_Color_dot_m_Id(idis * color),
    m_Color_dot_m_Is(color * idis)

{
}

PointLight::~PointLight()
{

}

const TColor &PointLight::color() const
{
    return m_Color;
}

const Vector &PointLight::position() const
{
    return m_Position;
}

double PointLight::iaValue() const
{
    return m_Ia;
}

double PointLight::idValue() const
{
    return m_Id;
}

const TColor PointLight::idColor() const
{
    return m_Color_dot_m_Id;
}

const TColor PointLight::isColor() const
{
    return m_Color_dot_m_Is;
}

const TColor PointLight::iaColor() const
{
    return m_Color_dot_m_Ia;
}
double PointLight::isValue() const
{
    return m_Is;
}
