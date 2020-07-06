#ifndef PHONGLIGHTINGMODEL_H
#define PHONGLIGHTINGMODEL_H
#include "vector.h"
#include "pointlight.h"
#include "material.h"
#include "pointlight.h"
#include "color.h"

template <typename T>
class PhongLightingParameters
{
    friend class PhongLightingModelHelper;
private:
    T m_Ie;
    T m_Ia;
    T m_Is;
    T m_Id;
    T m_Pa;
    T m_Ps;
    T m_Pd;
    double m_F;
    Vector m_NUnit;
    Vector m_LUnit;
    Vector m_VUnit;
    Vector m_RUnit;
private:
    PhongLightingParameters():
        m_Ie(0),
        m_Ia(0),
        m_Is(0),
        m_Id(0),
        m_Pa(0),
        m_Ps(0),
        m_Pd(0),
        m_NUnit(0),
        m_LUnit(0),
        m_VUnit(0),
        m_RUnit(0)
    {

    }
    PhongLightingParameters(
            const T& ie,
            const T& ia,
            const T& is,
            const T& id,
            const T& pa,
            const T& ps,
            const T& pd,
            double f,
            const Vector& nUnit,
            const Vector& lUnit,
            const Vector& vUnit,
            const Vector& rUnit):
        m_Ie(ie),
        m_Ia(ia),
        m_Is(is),
        m_Id(id),
        m_Pa(pa),
        m_Ps(ps),
        m_Pd(pd),
        m_F(f),
        m_NUnit(nUnit),
        m_LUnit(lUnit),
        m_VUnit(vUnit),
        m_RUnit(rUnit)
    {
    }
public:
    const T& Ie() const
    {
        return m_Ie;
    }
    const T& Ia() const
    {
        return m_Ia;
    }
    const T& Is() const
    {
        return m_Is;
    }
    const T& Id() const
    {
        return m_Id;
    }
    const T& Pa() const
    {
        return m_Pa;
    }
    const T& Ps() const
    {
        return m_Ps;
    }
    const T& Pd() const
    {
        return m_Pd;
    }
    double F() const
    {
        return m_F;
    }
    const Vector& NUnit() const
    {
        return m_NUnit;
    }
    const Vector& LUnit() const
    {
        return m_LUnit;
    }
    const Vector& RUnit() const
    {
        return m_RUnit;
    }
    const Vector& VUnit() const
    {
        return m_VUnit;
    }
};


#endif // PHONGLIGHTINGMODEL_H
