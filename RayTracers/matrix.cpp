#include "matrix.h"
#include "vector.h"
#include <math.h>

Matrix MatrixHelper::Identity()
{
    Matrix res;
    res.m_data[0][0] = 1;
    res.m_data[1][1] = 1;
    res.m_data[2][2] = 1;
    res.m_data[3][3] = 1;
    //
    return res;
}

Matrix MatrixHelper::Scale(const double s)
{
    return Scale(s, s, s);
}

Matrix MatrixHelper::Scale(const double sx, const double sy, const double sz)
{
    Matrix res = Identity();
    //
    res.m_data[0][0] = sx;
    res.m_data[1][1] = sy;
    res.m_data[2][2] = sz;
    res.m_data[3][3] = 1;
    //
    return res;
}

Matrix MatrixHelper::Transform(const Vector& t)
{
    Matrix res = Identity();
    //
    res.m_data[0][3] = t.x;
    res.m_data[1][3] = t.y;
    res.m_data[2][3] = t.z;
    res.m_data[3][3] = 1;
    //
    return res;
}

Matrix MatrixHelper::Transform(const double t)
{
    return Transform(Vector(t, t, t));
}

Matrix MatrixHelper::Transform(const double x, const double y, const double z)
{
    return Transform(Vector(x, y, z));

}

Vector MatrixHelper::MatrixTimeVector(const Matrix &matrix, const Vector &vec)
{
    double x = vec.x * matrix.m_data[0][0] + vec.y * matrix.m_data[0][1] + vec.z * matrix.m_data[0][2] + vec.w * matrix.m_data[0][3];
    double y = vec.x * matrix.m_data[1][0] + vec.y * matrix.m_data[1][1] + vec.z * matrix.m_data[1][2] + vec.w * matrix.m_data[1][3];
    double z = vec.x * matrix.m_data[2][0] + vec.y * matrix.m_data[2][1] + vec.z * matrix.m_data[2][2] + vec.w * matrix.m_data[2][3];
    double w = vec.x * matrix.m_data[3][0] + vec.y * matrix.m_data[3][1] + vec.z * matrix.m_data[3][2] + vec.w * matrix.m_data[3][3];
    //
    return Vector (x, y, z, w);
}

Matrix MatrixHelper::MatrixTimeMatrix(const Matrix &matrixLeft, const Matrix &matrixRight)
{
    Matrix res;
    for (int row = 0; row < MatrixSize; row++)
    {
        for (int col = 0; col < MatrixSize; col++)
        {
            double cellvalue = 0;
            for (int i = 0; i < MatrixSize; i++)
            {
                cellvalue += matrixLeft.m_data[row][i] * matrixRight.m_data[i][col];

            }
            res.m_data[row][col] =  cellvalue;
        }
    }
    return res;
}

Matrix MatrixHelper::AffineTransform(const Matrix &rotation, const Vector &v)
{
    Matrix L = Transform(v);
    Matrix res = MatrixTimeMatrix(L, rotation);
    return res;
}

bool Matrix::operator ==(const Matrix &m)
{
    for(int row = 0; row < MatrixSize; row ++)
    {
        for(int col = 0; col < MatrixSize; col++)
        {
            if (this->m_data[row][col] != m.m_data[row][col])
            {
                return false;
            }
        }
    }
    return true;
}

