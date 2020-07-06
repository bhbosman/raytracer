#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"


TEST(MatrixTest, Test013)
{
    Vector origin(20, 20, 20);
    Vector destination(0,1,1);
    Vector axis = destination - origin;
    axis.normalise();
    Matrix rotation = Rotation::RotationAroundAxis(axis, Rotation::degressToRadians(275));

    Matrix originTransform = MatrixHelper::Transform(origin);
    Matrix M = MatrixHelper::MatrixTimeMatrix(originTransform, rotation);

    Matrix originNegativeTransform = MatrixHelper::Transform(-origin);
    M = MatrixHelper::MatrixTimeMatrix(M, originNegativeTransform);

    Vector p(5, 0, 4);
    Vector pM = MatrixHelper::MatrixTimeVector(M, p);

    EXPECT_NEAR(+4.94156, pM.x, 10e-4);
    EXPECT_NEAR(+4.08698, pM.y, 10e-4);
    EXPECT_NEAR(-0.0254626, pM.z, 10e-4);
}

TEST(MatrixTest, Test006)
{
    Vector origin(20, 20, 20);
    Vector destination(0,1,1);
    Vector axis = destination - origin;
    axis.normalise();
    Vector p(5, 0, 4);
    Vector pM = Rotation::PointRotationAroundAxisAtOrigin(p, axis, 275, origin);

    EXPECT_NEAR(+4.94156, pM.x, 10e-4);
    EXPECT_NEAR(+4.08698, pM.y, 10e-4);
    EXPECT_NEAR(-0.0254626, pM.z, 10e-4);
}

