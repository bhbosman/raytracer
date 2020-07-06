#include "camera.h"
#include "vector.h"

Camera::Camera(
        const Vector &topLeft,
        const Vector &bottomLeft,
        const Vector &cameraDir,
        const double cameraDistance,
        const double aspectRatio):
    m_TopLeft(topLeft),
    m_BottomLeft(bottomLeft),
    m_CameraDirection(cameraDir.normalisedCopy()),
    m_AspectRatio(aspectRatio),
    m_CameraDistance(cameraDistance)
{
    init();
}

void Camera::init()
{
    double height = (m_BottomLeft - m_TopLeft).length();
    double width = height * m_AspectRatio;
    if (m_CameraDistance == 0)
    {
        m_CameraDistance = 5;
    }
    // we need to find the right-top and right-bottom points of the near plane
    m_CameraDirection.normalise();
    Vector left2RightDir = (((m_BottomLeft - m_TopLeft)).normalisedCopy().crossProduct(m_CameraDirection));
    left2RightDir *= width;
    m_NearPlane.m_BottomLeft = m_BottomLeft;
    m_NearPlane.m_TopLeft = m_TopLeft;
    m_NearPlane.m_TopRight = left2RightDir + m_TopLeft;
    m_NearPlane.m_BottomRight= left2RightDir + m_BottomLeft;

    // camera point is the mid point of the four corners
    m_CameraPoint = (m_NearPlane.m_BottomLeft + m_NearPlane.m_BottomRight + m_NearPlane.m_TopLeft + m_NearPlane.m_TopRight) / 4.f;

    // put the camera's focus point behind the nead plane
    m_CameraPoint += -m_CameraDistance * m_CameraDirection;
}

const NearPlane& Camera::NearPlane()const
{
    return m_NearPlane;
}

const Vector &Camera::cameraPoint() const
{
    return m_CameraPoint;
}

const Vector &Camera::cameraDirection() const
{
    return m_CameraDirection;
}

void Camera::ZoomIn()
{
    m_CameraDistance += 0.5;
    init();
}

void Camera::ZoomOut()
{
    m_CameraDistance -= 0.5;
    if(m_CameraDistance < 1)
    {
        m_CameraDistance = 1;
    }
    init();
}

void Camera::moveLeft(double value)
{
    Vector axis = ((m_BottomLeft - m_TopLeft).normalisedCopy().crossProduct(m_CameraDirection));
    axis *= -value;
    Matrix m = MatrixHelper::AffineTransform(MatrixHelper::Identity(), axis);
    AffineTransform(m, false);
}

void Camera::moveRight(double value)
{
    Vector axis = ((m_BottomLeft - m_TopLeft).normalisedCopy().crossProduct(m_CameraDirection));
    axis *= value;
    Matrix m = MatrixHelper::AffineTransform(MatrixHelper::Identity(), axis);
    AffineTransform(m, false);
}

void Camera::moveUp(double value)
{
    Vector axis = (m_BottomLeft - m_TopLeft).normalisedCopy();
    axis *= value;
    Matrix m = MatrixHelper::AffineTransform(MatrixHelper::Identity(), axis);
    AffineTransform(m, false);
}

void Camera::moveDown(double value)
{
    Vector axis = (m_BottomLeft - m_TopLeft).normalisedCopy();
    axis *= -value;
    Matrix m = MatrixHelper::AffineTransform(MatrixHelper::Identity(), axis);
    AffineTransform(m, false);
}

void Camera::moveForward(double value)
{
    Vector axis = m_CameraDirection;
    axis *= value;
    Matrix m = MatrixHelper::AffineTransform(MatrixHelper::Identity(), axis);
    AffineTransform(m, false);
}

void Camera::moveBackward(double value)
{
    Vector axis = m_CameraDirection;
    axis *= -value;
    Matrix m = MatrixHelper::AffineTransform(MatrixHelper::Identity(), axis);
    AffineTransform(m, false);
}

void Camera::AffineTransform(const Matrix &affineTransform, const bool direction)
{
    m_TopLeft = Rotation::PointRotationAroundMatrix(m_TopLeft, affineTransform);
    m_BottomLeft = Rotation::PointRotationAroundMatrix(m_BottomLeft, affineTransform);
    if (direction)
    {
        m_CameraDirection = Rotation::PointRotationAroundMatrix(m_CameraDirection, affineTransform);
    }
    init();
}



