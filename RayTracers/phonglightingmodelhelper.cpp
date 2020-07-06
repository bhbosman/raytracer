#include "phonglightingmodelhelper.h"

PhongLightingParameters<double> PhongLightingModelHelper::CreateBlackAndWhiteParams(
        const double ie, const double ia, const double is, const double id,
        const double pa, const double ps, const double pd, const double f,
        const Vector &pointOfInterest,
        const Vector &normalAtPoint,
        const Vector &lightSourcePosition,
        const Vector &viewerPosition)
{
    Vector nUnit = normalAtPoint.normalisedCopy();
    Vector vUnit = (viewerPosition - pointOfInterest).normalisedCopy();
    Vector lUnit = (lightSourcePosition - pointOfInterest).normalisedCopy();
    double dotln = nUnit.dot(lUnit);
    Vector rUnit = 2 * dotln *  nUnit - lUnit;
    //
    return PhongLightingParameters<double>(
                ie,
                ia, is,
                id,
                pa,
                ps,
                pd,
                f,
                nUnit,
                lUnit,
                vUnit,
                rUnit);

}

PhongLightingParameters<double> PhongLightingModelHelper::CreateBlackAndWhiteParams(
        const Material &material,
        const PointLight &pointLight,
        const double ie,
        const double f,
        const Vector &pointOfInterest,
        const Vector &normalAtPoint,
        const Vector &viewerPosition)
{
    return CreateBlackAndWhiteParams(
                ie, pointLight.iaValue(), pointLight.isValue(), pointLight.idValue(),
                material.paValue(),
                material.psValue(),
                material.pdValue(), f,
                pointOfInterest,
                normalAtPoint,
                pointLight.position(),
                viewerPosition);
}

PhongLightingParameters<TColor> PhongLightingModelHelper::CreateColor(
        const TColor &ie,
        const TColor &ia,
        const TColor &is,
        const TColor &id,
        const TColor &pa,
        const TColor &ps,
        const TColor &pd,
        const double f,
        const Vector &pointOfInterest,
        const Vector &normalAtPoint,
        const Vector &lightSourcePosition,
        const Vector &viewerPosition)
{
    Vector nUnit = normalAtPoint.normalisedCopy();
    Vector vUnit = (viewerPosition - pointOfInterest).normalisedCopy();
    Vector lUnit = (lightSourcePosition - pointOfInterest).normalisedCopy();
    double dotln = nUnit.dot(lUnit);
    Vector rUnit = 2 * dotln *  nUnit - lUnit;
    //
    return PhongLightingParameters<TColor>(
                ie,
                ia,
                is,
                id,
                pa,
                ps,
                pd,
                f,
                nUnit,
                lUnit,
                vUnit,
                rUnit);
}

PhongLightingParameters<TColor> PhongLightingModelHelper::CreateColor(
        //const InterSectionType interSection,
        const IntersectionCtx& ctx,
        const Vector &surfaceNormal,
        const PointLight &pointLight,
        const TColor &ie, const
        double f,
        const Vector &viewerPosition,
        const Vector & pointofInterest)
{
    {



        const Material& material_local = (*ctx.sceneObject()->material());
//        const Vector& color_point_local = interSection.interSection(). colorPoint();
        const SurfaceD surfaceDimension = ctx.surfaceD();
        const MappingPointCalculation::ptr cal = ctx.colorCalculation();
        const TColor& color_point_color_local = material_local.color(
                    cal,
                    surfaceDimension,
                    pointofInterest);

        return CreateColor(
                    ie,
                    pointLight.iaColor(),
                    pointLight.isColor(),
                    pointLight.idColor(),
                    color_point_color_local * material_local.paValue(),
                    color_point_color_local * material_local.psValue(),
                    color_point_color_local * material_local.pdValue(),
                    f,
                    pointofInterest,
                    surfaceNormal,
                    pointLight.position(),
                    viewerPosition);
    }
}
