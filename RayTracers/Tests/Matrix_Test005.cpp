#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"

TEST(MatrixTest, Test005)
{
    Vector origin(1, 4, 2);
    Vector destination(2,1,4);
    Vector axis = destination - origin;
    axis.normalise();
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(120));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(4, 2, 1);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    EXPECT_NEAR(1.87019, pM.x, 10e-4);
    EXPECT_NEAR(4.37018, pM.y, 10e-4);
    EXPECT_NEAR(5.62019, pM.z, 10e-4);
}

TEST(MatrixTest, Test012)
{
    Vector origin(1, 4, 2);
    Vector destination(2,1,4);
    Vector axis = destination - origin;
    axis.normalise();
    Vector p(4, 2, 1);
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(p, axis, 120, origin);

    EXPECT_NEAR(1.87019, pM.x, 10e-4);
    EXPECT_NEAR(4.37018, pM.y, 10e-4);
    EXPECT_NEAR(5.62019, pM.z, 10e-4);
}

