#include "colorcalculation.h"
#include "rotation.h"

StandardMappingPointCalculation::StandardMappingPointCalculation():
    inherited()
{
}

Vector StandardMappingPointCalculation::calculate(const Vector &pos) const
{

    return pos;
}

void StandardMappingPointCalculation::Rotate(const Matrix &/*rotationMatrix*/)
{

}

Mapping3DTo2DPoint::Mapping3DTo2DPoint(const Vector &normal):
    inherited(),
    m_RotationMatrix(Rotation::RotationAroundAxisAtOrigin(
                         normal.crossProduct(Vector::VECTOR_UNIT_Z).normalisedCopy(),
                         acos(normal.dot(Vector::VECTOR_UNIT_Z)) * 180/ M_PI / 2,
                         0))
{

}

Vector Mapping3DTo2DPoint::calculate(const Vector &pos) const
{
    Vector newPos = MatrixHelper::MatrixTimeVector(m_RotationMatrix, pos);
    return newPos;
}

void Mapping3DTo2DPoint::Rotate(const Matrix &/*rotationMatrix*/)
{

}


Mapping3DTo2DPointInSphere::Mapping3DTo2DPointInSphere(
        const Vector &axis,
        const Vector &origin,
        const double radius,
        const bool turnAround):inherited(),
    m_RotationMatrix(Rotation::RotationAroundAxisAtOrigin(
                         axis.crossProduct(Vector::VECTOR_UNIT_Z).normalisedCopy(),
                         acos(axis.dot(Vector::VECTOR_UNIT_Z)) * 180/ M_PI / 2,
                         0)),
    m_AxisRotation(0),
    m_TurnAround(turnAround),
    m_Axis(axis),
    m_Origin(origin),
    m_Radius(radius)
{

}


Vector Mapping3DTo2DPointInSphere::calculate(const Vector &pos) const
{
    const Vector d = Vector(
                (pos.x - m_Origin.x) / m_Radius,
                (pos.y - m_Origin.y) / m_Radius,
                (pos.z - m_Origin.z) / m_Radius);
    double uComp = (atan2(d.z, d.x) + m_AxisRotation) / (2 * M_PI);
    double vComp =  (2 * asin(d.y)) / (2 *M_PI);

    if(vComp > 0.5)
    {
        double delta = vComp - 0.5;
        vComp = -(0.5 - delta);
    }
    if(vComp < -0.5)
    {
        double delta2 = vComp + 0.5;
        vComp = (0.5 + delta2);
    }
    if (uComp > 0.5)
    {
        double delta = uComp - 0.5;
        uComp = -(0.5 - delta);
    }
    else if (uComp < -0.5)
    {
        double delta = uComp + 0.5;
        uComp = (0.5 + delta);
    }
    const double u = 0.5 - uComp;
    const double v = 0.5 - vComp;
    //
    return Vector(u, v, 0);
}

void Mapping3DTo2DPointInSphere::Rotate(const Matrix &rotationMatrix)
{
    m_Origin = MatrixHelper::MatrixTimeVector(rotationMatrix, m_Origin);
    if (m_TurnAround)
    {

        m_AxisRotation += 0.5;

        if (m_AxisRotation > (2 * M_PI))
        {
            m_AxisRotation -=(2 * M_PI);
        }
        if (m_AxisRotation < (-2 * M_PI))
        {
            m_AxisRotation +=(2 * M_PI);
        }
    }

}

MappingPointCalculation::MappingPointCalculation()
{

}

MappingPointCalculation::~MappingPointCalculation()
{

}

void MappingPointCalculation::Rotate(const Matrix &/*rotationMatrix*/)
{
}

Vector MappingPointCalculation::calculate(const Vector &pos) const
{
    return pos;
}


Mapping3DTo2DPointInPlane::Mapping3DTo2DPointInPlane(const Vector &normal): inherited(normal)
{

}

Vector Mapping3DTo2DPointInPlane::calculate(const Vector &pos) const
{
    const double blockSize = 150;
    Vector newPos = inherited::calculate(pos);


    double xBlocks = ceil(newPos.x / blockSize);
    double yBlocks = ceil(newPos.y / blockSize);
    double x = (newPos.x / blockSize);
    double y = (newPos.y / blockSize);


    newPos.x = fabs(xBlocks - x);
    newPos.y = fabs(yBlocks - y);
    return newPos;
}

void Mapping3DTo2DPointInPlane::Rotate(const Matrix &/*rotationMatrix*/)
{

}
