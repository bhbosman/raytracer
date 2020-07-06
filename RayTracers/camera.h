#ifndef CAMERA_H
#define CAMERA_H


#include "vector.h"
#include "NearPlane.h"
#include "matrix.h"
#include "rotation.h"

class Camera
{
private:
    Vector m_TopLeft;
    Vector m_BottomLeft;
    Vector m_CameraDirection;
    Vector	m_CameraPoint;
    double m_AspectRatio;
    double m_CameraDistance;
    NearPlane	m_NearPlane;
    void init();

public:
    Camera(
            const Vector& topLeft,
            const Vector& bottomLeft,
            const Vector& cameraDir,
            const double cameraDistance,
            const double aspectRatio);
    virtual ~Camera()
    {


    }
    const NearPlane &NearPlane() const;
    void ZoomIn();
    void ZoomOut();
    void moveLeft(double value);
    void moveRight(double value);
    void moveUp(double value);
    void moveDown(double value);
    void moveForward(double value);
    void moveBackward(double value);
    void AffineTransform(const Matrix& affineTransform, const bool direction);

    const Vector& cameraPoint() const;
    const Vector& cameraDirection() const;






public:
   typedef boost::shared_ptr<Camera> ptr;
   typedef std::vector<ptr> ptr_vec;

};

#endif // CAMERA_H
