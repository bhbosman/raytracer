#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"
#include "phonglightingmodel.h"
#include "phonglightingmodelhelper.h"
#include "phonelightingmodelcalculation.h"

TEST(PhongLightingModelTest, Test002)
{
    double ie = 0;
    double ia = 0.2;
    double pa = 0.4;
    double id = 1;
    double pd = 0.3;
    double is = 1;
    double ps = 0.1;
    double f = 10;
    Vector pointOfInterest(40, 10, 27);
    Vector normalAtPoint(0.57735, -0.57735, 0.57735);
    Vector lightSourcePosition(22, 22, 0);
    Vector viewerPosition(-15,22,0);

    PhongLightingParameters<double> params = PhongLightingModelHelper::CreateBlackAndWhiteParams(
                ie, ia, is, id,
                pa, ps, pd, f,
                pointOfInterest,normalAtPoint, lightSourcePosition, viewerPosition);

    double value = PhoneLightingModelCalculation<double>::Calculate(params);

    EXPECT_NEAR(f, params.F(), 10e-4);
    EXPECT_NEAR(ie, params.Ie(), 10e-4);
    EXPECT_NEAR(ia, params.Ia(), 10e-4);
    EXPECT_NEAR(is, params.Is(), 10e-4);
    EXPECT_NEAR(id, params.Id(), 10e-4);
    EXPECT_NEAR(pa, params.Pa(), 10e-4);
    EXPECT_NEAR(pd, params.Pd(), 10e-4);
    EXPECT_NEAR(ps, params.Ps(), 10e-4);

    bool b = Vector(0.57735, -0.57735, 0.57735) == params.NUnit();
    GTEST_ASSERT_EQ(true, b);
    b = Vector(-0.520266,0.346844,-0.780399) == params.LUnit();
    GTEST_ASSERT_EQ(true, b);
    b = Vector(-0.880931,0.192203,-0.432457) == params.VUnit();
    GTEST_ASSERT_EQ(true, b);
    b = Vector(-0.578073,0.751495,-0.31794) == params.RUnit();
    GTEST_ASSERT_EQ(true, b);
    EXPECT_NEAR(0.08, value, 10e-4);
}
