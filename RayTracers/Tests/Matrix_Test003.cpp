#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"

TEST(MatrixTest, Test003)
{
    Vector origin(0);
    Vector axis =  Vector::VECTOR_UNIT_Z;
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(302));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(1, 0, 0);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    GTEST_ASSERT_EQ(cos(Rotation::degressToRadians(302)), pM.x);
    GTEST_ASSERT_EQ(sin(Rotation::degressToRadians(302)), pM.y);
}

TEST(MatrixTest, Test010)
{
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(Vector(1, 0, 0), Vector::VECTOR_UNIT_Z, 302, Vector(0));

    GTEST_ASSERT_EQ(cos(Rotation::degressToRadians(302)), pM.x);
    GTEST_ASSERT_EQ(sin(Rotation::degressToRadians(302)), pM.y);
}

