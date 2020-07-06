#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"

TEST(MatrixTest, Test001)
{
    Vector origin(0);
    Vector axis =  Vector::VECTOR_UNIT_Z;
    Matrix rotsssation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(45));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotsssation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(1, 0, 0);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    GTEST_ASSERT_EQ(cos(Rotation::degressToRadians(45)), pM.x);
    GTEST_ASSERT_EQ(sin(Rotation::degressToRadians(45)), pM.y);
}

TEST(MatrixTest, Test008)
{
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(Vector(1, 0, 0), Vector::VECTOR_UNIT_Z, 45, Vector(0));
    GTEST_ASSERT_EQ(cos(Rotation::degressToRadians(45)), pM.x);
    GTEST_ASSERT_EQ(sin(Rotation::degressToRadians(45)), pM.y);
}
