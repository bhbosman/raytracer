#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"


TEST(MatrixTest, Test002)
{
    Vector origin(0);
    Vector axis =  Vector::VECTOR_UNIT_Z;
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(30));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(1, 0, 0);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    GTEST_ASSERT_EQ(cos(Rotation::degressToRadians(30)), pM.x);
    GTEST_ASSERT_EQ(sin(Rotation::degressToRadians(30)), pM.y);
}

TEST(MatrixTest, Test009)
{
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(Vector(1, 0, 0), Vector::VECTOR_UNIT_Z, 30, Vector(0));

    GTEST_ASSERT_EQ(cos(Rotation::degressToRadians(30)), pM.x);
    GTEST_ASSERT_EQ(sin(Rotation::degressToRadians(30)), pM.y);
}
