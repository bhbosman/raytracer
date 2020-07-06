#include <gtest/gtest.h>
#include "matrix.h"
#include "rotation.h"
#include "vector.h"
#include "phonglightingmodel.h"
#include "phonglightingmodelhelper.h"
#include "phonelightingmodelcalculation.h"

TEST(PhongLightingModelTest, Test001)
{
    double ie = 0.2;
    double ia = 0.1;
    double is = 0.3;
    double id = 0.3;
    double pa = 0.1;
    double ps = 0.5;
    double pd =0;
    double f = 8;
    Vector pointOfInterest(5, 5, 2);
    Vector normalAtPoint(0.928477,0,0.371391);
    Vector lightSourcePosition(20, 7, 2);
    Vector viewerPosition(20, 0, 10);

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

    bool b = Vector(0.928477,0,0.371391) == params.NUnit();
    GTEST_ASSERT_EQ(true, b);
    b = Vector(0.991228,0.132164,0) == params.LUnit();
    GTEST_ASSERT_EQ(true, b);
    b = Vector(0.846499,-0.282166,0.451466) == params.VUnit();
    GTEST_ASSERT_EQ(true, b);
    b = Vector(0.717786,-0.132164,0.683605) == params.RUnit();
    GTEST_ASSERT_EQ(true, b);
    EXPECT_NEAR(0.312503, value, 10e-4);
}
