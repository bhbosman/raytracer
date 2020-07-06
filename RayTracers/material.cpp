#include "material.h"
#include "PerlinNoise.h"

Material::Material(
        double ps,
        double pd)
    :
      m_Pa(0),
      m_Ps(ps),
      m_Pd(pd)
{
}

Material::~Material()
{

}

double Material::pdValue() const
{
    return m_Pd;
}

double Material::psValue() const
{
    return m_Ps;
}

double Material::paValue() const
{
    return m_Pa;
}


const TColor Material::pdColor(const MappingPointCalculation::ptr &calculator,
        const SurfaceD &dimension,
        const Vector& position) const
{
    return m_Pd * color(calculator, dimension, position);
}

const TColor Material::psColor(
        const MappingPointCalculation::ptr &calculator,
        const SurfaceD &dimension,
        const Vector& position) const
{
    return m_Ps * color( calculator, dimension, position);
}

const TColor Material::paColor(
        const MappingPointCalculation::ptr &calculator,
        const SurfaceD &dimension,
        const Vector& position) const
{
    return m_Pa * color(calculator, dimension, position);
}

const Vector Material::noise(const Vector &/*position*/) const
{
    return TColor(0);
}

ChessBoardMaterial::ChessBoardMaterial(
        double ps,
        double pd,
        const TColor &color1,
        const TColor &color2):
    inherited(ps, pd),
    m_Color1(color1),
    m_Color2(color2)
{

}

const TColor ChessBoardMaterial::color(
        const MappingPointCalculation::ptr &calculator,
        const SurfaceD &dimension,
        const Vector &position) const
{
    Vector d = calculator->calculate(position);

    if (dimension == Surface2D)
    {
        double x =abs((floor(d.x / 10)));
        double y =abs((floor(d.y / 10)));
        int r = (int)(x + y) % 2;
        if (r == 1)
        {
            return m_Color2;
        }
    }
    else if (dimension == Surface3D)
    {

        double x =abs((floor(d.x / 0.10)));
        double y =abs((floor(d.y / 0.10)));
        int r = (int)(x + y) % 2;
        if (r == 1)
        {
            return m_Color2;
        }


    }
    return m_Color1;
}


ScatterBoardMaterial::ScatterBoardMaterial(double ps,
        double pd,
        const TColor &color1,
        const TColor &color2):
    inherited(ps, pd),
    m_Color1(color1),
    m_Color2(color2)
{

}

const TColor ScatterBoardMaterial::color(
        const MappingPointCalculation::ptr &/*calculator*/,
        const SurfaceD &/*dimension*/,
        const Vector &/*position*/) const
{
    int r = rand() %2;
    if (r == 1)
    {
        return m_Color2;
    }
    else
    {
        return m_Color1;
    }
}

PerlinNoiseMaterial::PerlinNoiseMaterial(double ps, double pd, const TColor &color):
    inherited(ps, pd)
{
    double delta = 1.0 / 512.0;
    double runner = 0.5;
    for(int i = 0; i < 256; i++)
    {
        TColor temp = runner *color;
        m_Color2[i] = temp;
        runner += delta;
    }
}

const TColor PerlinNoiseMaterial::color(
        const MappingPointCalculation::ptr &/*calculator*/,
        const SurfaceD &/*dimension*/,
        const Vector &position) const
{
    double v[3] = {position.x, position.y, position.z};
    double perlin = fabs(noise3(v) * 255);
    perlin = fmin(255, fmax(0, perlin));
    int dd = int(perlin);
    return m_Color2[dd];
}

const Vector PerlinNoiseMaterial::noise(const Vector &position) const
{
    double x = noise1(position.x);
    double y = noise1(position.y);
    double z = noise1(position.z);

    return TColor(x, y, z);
}


StandardMaterial::StandardMaterial(
        double ps,
        double pd,
        const TColor &colour): inherited(ps, pd), m_Color(colour)
{

}


const TColor TextureMaterial::color(const MappingPointCalculation::ptr &calculator, const SurfaceD &, const Vector &position) const
{
    const Vector uv = calculator->calculate(position);

    const int x = int((double)m_Image.width()  * uv.x);
    const int y = int((double)m_Image.height()  * uv.y);

    bool b =  (x >= 0);
    b &= (x <= m_Image.width());
    b &= (y >= 0);
    b &= (y <= m_Image.height());
    if(b)
    {
        QRgb rgb = m_Image.pixel(x, y);
        const double r = (double)qRed(rgb) / 256;
        const double g = (double)qGreen(rgb) / 256;
        const double b = (double)qBlue(rgb) / 256;
        //
        return TColor(r, g, b);
    }
    else
    {
        return TColor(0);
    }
}
