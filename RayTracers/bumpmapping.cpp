#include "bumpmapping.h"
#include "PerlinNoise.h"
BumpMapping::BumpMapping(double ep):
    m_Epsilon(ep)
{
}

Vector BumpMapping::calculateBump(const Vector &surfacePoint) const
{
    double x1;
    {
        double noiseData[3] = {surfacePoint.x + m_Epsilon, surfacePoint.y, surfacePoint.z};
        x1 = noise3(noiseData);
    }
    double x2;
    {
        double noiseData[3] = {surfacePoint.x -  m_Epsilon, surfacePoint.y, surfacePoint.z};
        x2 = noise3(noiseData);
    }
    double y1;
    {
        double noiseData[3] = {surfacePoint.x, surfacePoint.y +  m_Epsilon, surfacePoint.z};
        y1 = noise3(noiseData);
    }
    double y2;
    {
        double noiseData[3] = {surfacePoint.x, surfacePoint.y -  m_Epsilon, surfacePoint.z};
        y2 = noise3(noiseData);
    }
    double z1;
    {
        double noiseData[3] = {surfacePoint.x, surfacePoint.y, surfacePoint.z +  m_Epsilon};
        z1 = noise3(noiseData);
    }
    double z2;
    {
        double noiseData[3] = {surfacePoint.x, surfacePoint.y, surfacePoint.z +  m_Epsilon};
        z2 = noise3(noiseData);
    }
    return Vector(x1 - x2, y1 - y2, z1 - z2);
}
