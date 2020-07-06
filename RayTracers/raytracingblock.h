#ifndef RAYTRACINGBLOCK_H
#define RAYTRACINGBLOCK_H

#include "vector.h"
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "pixelbuffer.h"
#include "Color.h"
#include "PixelData.h"
#include <qrgb.h>

#define _RayTracingBlockSize_ 50

class RayTracingBlock{
private:
    uchar * m_PointerArray[_RayTracingBlockSize_];
    Vector m_CoordinateData[_RayTracingBlockSize_][_RayTracingBlockSize_];
    Vector m_DeltaPixelWidthVector;
    Vector m_DeltaPixelHeightVector;

    PixelData m_PixelData[_RayTracingBlockSize_][_RayTracingBlockSize_];


    PixelBuffer::ptr m_pixelBuffer; // I take a reference here, as I keep pointers to data that this object manage
    static PixelData clampColour3fToPixel(const TColor& color);
    int m_LeftPixel;
    int m_TopPixel;
    int m_Width;
    int m_Height;

public:
    RayTracingBlock(
            const int leftPixel,
            const int topPixel,
            const int width,
            const int height,
            const PixelBuffer::ptr& buffer);
    void setCoordinateData(const int x, const int y, const Vector& vec);
//    void setBottomRight(const int x, const int y, const Vector& vec);
//    void setTopLeft(const int x, const int y, const Vector& vec);
    void setDeltaPixelWidthVector(const Vector& v);
    void setDeltaPixelHeightVector(const Vector& v);


    void setColorData(const int x, const int y, const Vector& vec);
    TColor colorData(const int x, const int y) const
    {
        QRgb rgb = m_PixelData[y][x];
        const double r = (double)qRed(rgb) / 256;
        const double g = (double)qGreen(rgb) / 256;
        const double b = (double)qBlue(rgb) / 256;
        //
        return TColor(r, g, b);

    }
    const Vector coordinateData(const int x, const int y, const double xPercentage, const double yPercentage) const;
    const PixelBuffer::ptr& pixelBuffer() const;
    int leftPixel() const;
    int topPixel() const;
    int width() const;
    int height() const;
    void Paint() const;
public:
    typedef boost::shared_ptr<RayTracingBlock> ptr;
    typedef std::vector<ptr> ptr_vec;
};
#endif // RAYTRACINGBLOCK_H
