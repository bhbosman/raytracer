#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H


#include <QImage>
#include <boost/shared_ptr.hpp>

class PixelBuffer
{
private:
    QImage m_Image;
public:
    PixelBuffer(int width, int height);
    int height() const;

    int width() const;
    int bytesPerLine();
    uchar *scanLine(int lineNumber);
    uchar *scanLine(int lineNumber, int linePos);
    int bytesPerPixel();
    void fill(uint color);
    QImage image();
    void clear();
    void save(QString filename) const;

public:
   typedef boost::shared_ptr<PixelBuffer> ptr;
   typedef std::vector<ptr> ptr_vec;
};

#endif // PIXELBUFFER_H
