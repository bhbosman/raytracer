#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"

TEST(MatrixTest, Test007)
{
    Vector origin(2, 10, 1);
    Vector destination(4,4,0);
    Vector axis = destination - origin;
    axis.normalise();
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(75));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(10, 0, 7);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    EXPECT_NEAR(-0.33779, pM.x, 10e-4);
    EXPECT_NEAR(-3.19782, pM.y, 10e-4);
    EXPECT_NEAR(+5.51135, pM.z, 10e-4);
}

TEST(MatrixTest, Test014)
{
    Vector origin(2, 10, 1);
    Vector destination(4,4,0);
    Vector axis = destination - origin;
    axis.normalise();
    Vector p(10, 0, 7);
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(p, axis, 75, origin);
    EXPECT_NEAR(-0.33779, pM.x, 10e-4);
    EXPECT_NEAR(-3.19782, pM.y, 10e-4);
    EXPECT_NEAR(+5.51135, pM.z, 10e-4);
}


