#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
#include <boost/shared_ptr.hpp>

#define MatrixSize 4

// Matrix is always a (row, col)

class Matrix
{
    friend class MatrixHelper;
public:
    Matrix()
    {
        memset(&m_data, 0, sizeof(m_data));
    }

    double m_data[MatrixSize] [MatrixSize];
    bool operator == (const Matrix& m);
public:
    typedef boost::shared_ptr<Matrix> ptr;
};

class MatrixHelper
{
private:
public:
    static Matrix Identity();
    static Matrix Scale(const double s);
    static Matrix Scale(const double sx, const double sy, const double sz);
    static Vector MatrixTimeVector(const Matrix& matrix, const Vector& vec);
    static Matrix MatrixTimeMatrix(const Matrix& matrixLeft, const Matrix& matrixRight);
    static Matrix AffineTransform(const Matrix& rotation, const Vector& v);

    static Matrix Transform(const Vector &t);
    static Matrix Transform(const double t);
    static Matrix Transform(const double x, const double y, const double z);

};
#endif // MATRIX_H
