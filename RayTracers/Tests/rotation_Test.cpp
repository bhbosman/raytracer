#include <protocols/rwhod.h>
#include <gtest/gtest.h>
//#include <google/protobuf/extension_set.h>
#include "vector.h"
#include "matrix.h"
#include "rotation.h"


TEST(RotationTest, RotationZAgainstGeneralRotation)
{
    Vector v(1, 1, 1);
    Matrix m1 = Rotation::RotationZ(Rotation::degressToRadians(45));
    Vector ans1 =  MatrixHelper::MatrixTimeVector(m1, v);
    Matrix m2 = Rotation::RotationAroundAxis(Vector::VECTOR_UNIT_Z, Rotation::degressToRadians(45));
    Vector ans2 =  MatrixHelper::MatrixTimeVector(m2, v);
    GTEST_ASSERT_EQ(true, ans1==ans2);
}

TEST(RotationTest, RotationXAgainstGeneralRotation)
{
    Vector v(1, 1, 1);
    Matrix m1 = Rotation::RotationX(Rotation::degressToRadians(45));
    Vector ans1 =  MatrixHelper::MatrixTimeVector(m1, v);
    Matrix m2 = Rotation::RotationAroundAxis(Vector::VECTOR_UNIT_X, Rotation::degressToRadians(45));
    Vector ans2 =  MatrixHelper::MatrixTimeVector(m2, v);
    GTEST_ASSERT_EQ(true, ans1==ans2);
}

TEST(RotationTest, RotationYAgainstGeneralRotation)
{
    Vector v(1, 1, 1);
    Matrix m1 = Rotation::RotationY(Rotation::degressToRadians(45));
    Vector ans1 =  MatrixHelper::MatrixTimeVector(m1, v);
    Matrix m2 = Rotation::RotationAroundAxis(Vector::VECTOR_UNIT_Y, Rotation::degressToRadians(45));
    Vector ans2 =  MatrixHelper::MatrixTimeVector(m2, v);
    GTEST_ASSERT_EQ(true, ans1==ans2);
}
