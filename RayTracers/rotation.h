#ifndef ROTATION_H
#define ROTATION_H


#include "vector.h"
#include "matrix.h"
#include <gtest/gtest.h>


class Rotation
{
//    friend class GTEST_TEST_CLASS_NAME_(RotationTest, RotationZAgainstGeneralRotation);
//    friend class GTEST_TEST_CLASS_NAME_(RotationTest, RotationXAgainstGeneralRotation);
//    friend class GTEST_TEST_CLASS_NAME_(RotationTest, RotationYAgainstGeneralRotation);

private:

public:
    static double degressToRadians(const double degree);

    static Matrix RotationAroundAxis(const Vector &axis, const double rad);
    static Vector PointRotationAroundMatrix(const Vector &point, const Matrix &rotationMatrix);
    static Vector PointRotationAroundAxisAtOrigin(const Vector &point, const Vector &axis, const double degrees, const Vector &origin);
    static Matrix RotationAroundAxisAtOrigin(const Vector &axis, const double degrees, const Vector &origin);
    static Matrix RotationX(const double rad);
    static Matrix RotationY(const double rad);
    static Matrix RotationZ(const double rad);
};

#endif // ROTATION_H
