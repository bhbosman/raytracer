#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"

TEST(MatrixTest, Test004)
{
    Vector origin(1, 0, 1);
    Vector destination(0,0,3);
    Vector axis = destination - origin;
    axis.normalise();
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(30));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(0, 3, 0);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    EXPECT_NEAR(-1.18087, pM.x, 10e-4);
    EXPECT_NEAR(1.92726, pM.y, 10e-4);
    EXPECT_NEAR(-0.590436, pM.z, 10e-4);
}

TEST(MatrixTest, Test011)
{
    Vector origin(1, 0, 1);
    Vector destination(0,0,3);
    Vector axis = destination - origin;
    axis.normalise();
    Vector p(0, 3, 0);
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(p, axis, 30, origin);

    EXPECT_NEAR(-1.18087, pM.x, 10e-4);
    EXPECT_NEAR(1.92726, pM.y, 10e-4);
    EXPECT_NEAR(-0.590436, pM.z, 10e-4);
}

