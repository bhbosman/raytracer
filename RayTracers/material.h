#ifndef MATERIAL_H
#define MATERIAL_H


#include "Color.h"
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "SurfaceDimension.h"
#include "colorcalculation.h"
#include <qrgb.h>
#include <qimage.h>

class Material
{
private:
    double m_Pa;
    double m_Ps;
    double m_Pd;

public:

    Material(
            double ps,
            double pd);
    virtual ~Material();

    double pdValue() const;
    double psValue() const;
    double paValue() const;

    const TColor pdColor(const MappingPointCalculation::ptr &calculator, const SurfaceD &dimension, const Vector& position) const;
    const TColor psColor(const MappingPointCalculation::ptr& calculator,const SurfaceD &dimension, const Vector& position) const;
    const TColor paColor(const MappingPointCalculation::ptr& calculator,const SurfaceD &dimension, const Vector& position) const;
    virtual const TColor color(const MappingPointCalculation::ptr &/*calculator*/,
            const SurfaceD &/*dimension*/,
            const Vector& /*position*/) const
    {
        return 0;

    }
    virtual const Vector noise(const Vector& position) const;
public:
    typedef boost::shared_ptr<Material> ptr;
    typedef std::vector<Material::ptr> ptr_vec;
};

class StandardMaterial: public Material
{
private:
    TColor m_Color;

    typedef Material inherited;


public:
    StandardMaterial(double ps,
            double pd,
            const TColor& colour);
    virtual const TColor color(const MappingPointCalculation::ptr &/*calculator*/,
            const SurfaceD &/*dimension*/,
            const Vector& /*position*/) const override
    {
        return m_Color;
    }

};

class ChessBoardMaterial: public Material
{
private:
    typedef Material inherited;
    TColor m_Color1;
    TColor m_Color2;

public:
    ChessBoardMaterial(double ps,
            double pd,
            const TColor& color1, const TColor &color2);
    virtual const TColor color(
            const MappingPointCalculation::ptr& calculator,
            const SurfaceD &dimension,
            const Vector& position) const override;

};

class ScatterBoardMaterial: public Material
{
private:
    typedef Material inherited;
    TColor m_Color1;
    TColor m_Color2;

public:
    ScatterBoardMaterial(
            double ps,
            double pd,
            const TColor& color1,
            const TColor &color2);
    virtual const TColor color(
            const MappingPointCalculation::ptr& calculator,
            const SurfaceD &dimension,
            const Vector& position) const override;
};


class PerlinNoiseMaterial: public Material
{
private:
    typedef Material inherited;
    TColor m_Color2[256];

public:
    PerlinNoiseMaterial(double ps,
            double pd,
            const TColor& color);
    virtual const TColor color(
            const MappingPointCalculation::ptr& calculator,
            const SurfaceD &dimension,
            const Vector& position) const override;
    virtual const Vector noise(const Vector& position) const override;
};

class TextureMaterial: public Material
{
private:
    typedef Material inherited;
    QImage m_Image;
public:
    TextureMaterial(const double ps, const double pd, const QString& fileName): inherited(ps, pd),
        m_Image(fileName)
    {


    }

    virtual const TColor color(
            const MappingPointCalculation::ptr& calculator,
            const SurfaceD &/*dimension*/,
            const Vector& position) const override;
};





extern Material::ptr g_Space;
#endif // MATERIAL_H
