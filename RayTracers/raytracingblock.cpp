#include "raytracingblock.h"

PixelData RayTracingBlock::clampColour3fToPixel(const TColor &color)
{
    unsigned int red	= (unsigned int)(color.r * 256);
    unsigned int green	= (unsigned int)(color.g * 256);
    unsigned int blue	= (unsigned int)(color.b * 256);
    if (red > 255)
    {
        red = 255;
    }
    if (green > 255)
    {
        green = 255;
    }
    if (blue > 255)
    {
        blue = 255;
    }
    return (red << 16) | (green << 8) | blue;
}

RayTracingBlock::RayTracingBlock(
        const int leftPixel,
        const int topPixel,
        const int width,
        const int height,
        const PixelBuffer::ptr &buffer):
    m_pixelBuffer(buffer),
    m_LeftPixel(leftPixel),
    m_TopPixel(topPixel),
    m_Width(width),
    m_Height(height)
{
    memset(&m_PointerArray, 0, sizeof(m_PointerArray));
    //
    for(int y = topPixel; y < topPixel + _RayTracingBlockSize_; y++)
    {
        uchar *scanPos =  buffer->scanLine(y, leftPixel);
        m_PointerArray[y - topPixel] = scanPos;
    }
}

void RayTracingBlock::setCoordinateData(const int x, const int y, const Vector &vec)
{
    m_CoordinateData[x][y] = vec;
}

//void RayTracingBlock::setBottomRight(const int x, const int y, const Vector &vec)
//{
//    m_BottomRight[x][y] = vec;
//}

//void RayTracingBlock::setTopLeft(const int x, const int y, const Vector &vec)
//{
//    m_TopLeftCoordinateData[x][y] = vec;
//}

void RayTracingBlock::setDeltaPixelWidthVector(const Vector &v)
{
    m_DeltaPixelWidthVector = v;
}

void RayTracingBlock::setDeltaPixelHeightVector(const Vector &v)
{
    m_DeltaPixelHeightVector = v;
}

void RayTracingBlock::setColorData(const int x, const int y, const Vector& vec)
{
    PixelData pix = clampColour3fToPixel(vec);
    m_PixelData[y][x] = pix;

}

const Vector RayTracingBlock::coordinateData(const int x, const int y, const double xPercentage, const double yPercentage) const
{
    return m_CoordinateData[x][y]
            + (xPercentage * m_DeltaPixelWidthVector)
            + (yPercentage * m_DeltaPixelHeightVector);
}

const PixelBuffer::ptr &RayTracingBlock::pixelBuffer() const
{
    return m_pixelBuffer;
}

int RayTracingBlock::leftPixel() const
{
    return m_LeftPixel;
}

int RayTracingBlock::topPixel() const
{
    return m_TopPixel;
}

int RayTracingBlock::width() const
{
    return m_Width;
}

int RayTracingBlock::height() const
{
    return m_Height;
}

void RayTracingBlock::Paint() const
{
    for(int i = 0; i < _RayTracingBlockSize_; i++)
    {
        uchar* p = m_PointerArray[i];
        memmove(p, &m_PixelData[i][0], sizeof(PixelData) * _RayTracingBlockSize_);
    }
}
