#include "rotation.h"
#include "vector.h"
#include "matrix.h"

Matrix Rotation::RotationAroundAxis(const Vector &axis, const double rad)
{
    Matrix res;
    // Got out of the text book
    double c = cos(rad);
    double s = sin(rad);
    double a = 1 - c;
    // Row 0
    Vector normaxis = axis.normalisedCopy();
    res.m_data[0][0] = a * normaxis.x * normaxis.x + c;
    res.m_data[0][1] = a * normaxis.x * normaxis.y - s * normaxis.z;
    res.m_data[0][2] = a * normaxis.x * normaxis.z + s * normaxis.y;
    res.m_data[0][3] = 0;
    // Row 1
    res.m_data[1][0] = a * normaxis.x * normaxis.y + s * normaxis.z;
    res.m_data[1][1] = a * normaxis.y * normaxis.y + c;
    res.m_data[1][2] = a * normaxis.y * normaxis.z - s * normaxis.x;
    res.m_data[1][3] = 0;
    // Row2
    res.m_data[2][0] = a * normaxis.x * normaxis.z - s * normaxis.y;
    res.m_data[2][1] = a * normaxis.y * normaxis.z + s * normaxis.x;
    res.m_data[2][2] = a * normaxis.z * normaxis.z + c;
    res.m_data[2][3] = 0;
    // Row 3
    res.m_data[3][0] = 0;
    res.m_data[3][1] = 0;
    res.m_data[3][2] = 0;
    res.m_data[3][3] = 1;
    //
    return res;
}
Vector Rotation::PointRotationAroundMatrix(const Vector &point, const Matrix &rotationMatrix)
{
    return MatrixHelper::MatrixTimeVector(rotationMatrix, point);
}
Vector Rotation::PointRotationAroundAxisAtOrigin(const Vector &point, const Vector &axis, const double degrees, const Vector &origin)
{
    Matrix M = RotationAroundAxisAtOrigin(axis, degrees, origin);
    return MatrixHelper::MatrixTimeVector(M, point);
}
Matrix Rotation::RotationAroundAxisAtOrigin(const Vector &axis, const double degrees, const Vector &origin)
{
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(degrees));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    return MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

}
Matrix Rotation::RotationX(const double rad)
{
    // Got out of the text book
    double c = cos(rad);
    double s = sin(rad);
    Matrix res = MatrixHelper::Identity();
    // Row 1
    res.m_data[1][1] = c;
    res.m_data[1][2] = -s;
    // Row 2
    res.m_data[2][1] = s;
    res.m_data[2][2] = c;
    //
    return res;
}
Matrix Rotation::RotationY(const double rad)
{
    // Got out of the text book
    double c = cos(rad);
    double s = sin(rad);
    Matrix res = MatrixHelper::Identity();
    // Row 0
    res.m_data[0][0] = c;
    res.m_data[0][2] = s;
    // Row 2
    res.m_data[2][0] = -s;
    res.m_data[2][2] = c;
    //
    return res;
}
Matrix Rotation::RotationZ(const double rad)
{
    // Got out of the text book
    double c = cos(rad);
    double s = sin(rad);
    Matrix res = MatrixHelper::Identity();
    // Row 0
    res.m_data[0][0] = c;
    res.m_data[0][1] = -s;
    // Row 1
    res.m_data[1][0] = s;
    res.m_data[1][1] = c;
    //
    return res;
}
double Rotation::degressToRadians(double degree)
{
    return degree * M_PI / 180;
}
