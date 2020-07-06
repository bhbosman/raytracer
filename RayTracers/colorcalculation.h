#ifndef COLORCALCULATION_H
#define COLORCALCULATION_H
#include "vector.h"

#include <vector>
#include <boost/shared_ptr.hpp>
#include "matrix.h"


class MappingPointCalculation
{

public:
    MappingPointCalculation();
    virtual ~MappingPointCalculation();
    virtual void Rotate(const Matrix& rotationMatrix);
    virtual Vector calculate(const Vector& pos) const;
    typedef boost::shared_ptr<MappingPointCalculation> ptr;
};


class StandardMappingPointCalculation: public MappingPointCalculation
{
private:
    typedef MappingPointCalculation inherited;
public:
    StandardMappingPointCalculation();
    virtual Vector calculate(const Vector& pos) const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
};


class Mapping3DTo2DPoint: public MappingPointCalculation
{
private:
    typedef MappingPointCalculation inherited;
    Matrix m_RotationMatrix;
public:
    Mapping3DTo2DPoint(const Vector& normal);
    virtual Vector calculate(const Vector& pos) const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
};




class Mapping3DTo2DPointInPlane: public Mapping3DTo2DPoint
{
private:
    typedef Mapping3DTo2DPoint inherited;
public:
    Mapping3DTo2DPointInPlane(const Vector& normal);
    virtual Vector calculate(const Vector& pos) const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
};



class Mapping3DTo2DPointInSphere: public MappingPointCalculation
{
private:
    typedef MappingPointCalculation inherited;
    Matrix m_RotationMatrix;
    double m_AxisRotation;
    bool  m_TurnAround;
private:
    Vector m_Axis;
    Vector m_Origin;
    double m_Radius;

public:
    Mapping3DTo2DPointInSphere(
            const Vector& axis,
            const Vector& origin,
            const double radius,
            const bool turnAround);
    virtual Vector calculate(const Vector& pos) const override;
    virtual void Rotate(const Matrix& rotationMatrix) override;
};
#endif // COLORCALCULATION_H
