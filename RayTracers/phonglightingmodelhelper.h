#ifndef PHONGLIGHTINGMODELHELPER_H
#define PHONGLIGHTINGMODELHELPER_H
#include "vector.h"
#include "phonglightingmodel.h"
#include "intersection.h"

#include "intersectionwithsceneobject.h"

class PhongLightingModelHelper
{
public:
    static PhongLightingParameters<double> CreateBlackAndWhiteParams(
            const double ie,
            const double ia,
            const double is,
            const double id,
            const double pa,
            const double ps,
            const double pd,
            const double f,
            const Vector &pointOfInterest,
            const Vector &normalAtPoint,
            const Vector &lightSourcePosition,
            const Vector &viewerPosition);
    static PhongLightingParameters<double> CreateBlackAndWhiteParams(
            const Material &material,
            const PointLight &pointLight,
            const double ie,
            const double f,
            const Vector &pointOfInterest,
            const Vector &normalAtPoint,
            const Vector &viewerPosition);



    static PhongLightingParameters<TColor> CreateColor(
            const TColor& ie,
            const TColor& ia,
            const TColor& is,
            const TColor& id,
            const TColor& pa,
            const TColor& ps,
            const TColor& pd,
            const double f,
            const Vector &pointOfInterest,
            const Vector &normalAtPoint,
            const Vector &lightSourcePosition,
            const Vector &viewerPosition);
    static PhongLightingParameters<TColor> CreateColor(const IntersectionCtx &ctx,
            const Vector &surfaceNormal,
            const PointLight &pointLight,
            const TColor& ie,
            const double f,
            const Vector &viewerPosition, const Vector &pointofInterest);
};

#endif // PHONGLIGHTINGMODELHELPER_H
