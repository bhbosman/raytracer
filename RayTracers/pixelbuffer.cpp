#include <QImage>

#include "pixelbuffer.h"

PixelBuffer::PixelBuffer(int width, int height):
    m_Image(width, height, QImage::Format_RGB32)
{

}

int PixelBuffer::height() const
{
    return m_Image.height();
}

int PixelBuffer::width()const
{
    return m_Image.width();
}

int PixelBuffer::bytesPerLine()
{
    return m_Image.bytesPerLine();
}

uchar *PixelBuffer::scanLine(int lineNumber)
{
    return m_Image.scanLine(lineNumber);
}

uchar *PixelBuffer::scanLine(int lineNumber, int linePos)
{
    uchar *result = scanLine(lineNumber);
    result += linePos * bytesPerPixel();
    return result;
}

int PixelBuffer::bytesPerPixel()
{
    return bytesPerLine() / width();
}

void PixelBuffer::fill(uint color)
{
    m_Image.fill(color);
}

QImage PixelBuffer::image()
{
    return m_Image;
}

void PixelBuffer::clear()
{
    m_Image.fill(0);

}

void PixelBuffer::save(QString filename) const
{
    m_Image.save(filename, 0, 100);

}
