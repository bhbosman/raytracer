#ifndef VECTOR_H
#define VECTOR_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <cmath>



#include <math.h>

class Vector
{
public:
    union
    {
        struct
        {
            double x;
            double y;
            double z;
            double w;
        };
        struct
        {
            double r;
            double g;
            double b;
        };
        struct
        {
            double data[3];
        };

    };


    Vector()
    {
        x = y = z = 0;
        w = 1;
    }
    Vector(const Vector& vec)
    {
        x =vec.x;
        y =vec.y;
        z =vec.z;
        w = vec.w;
    }
    Vector(const double x, const double y, const double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w =  1;
    }
    Vector(const double x, const double y, const double z, const double w)
    {
        this->x =x;
        this->y = y;
        this->z = z;
        this->w = w;
    }
    inline Vector( const double f )
    {
        x = y = z = f;
        w = 1;
    }

    inline Vector& operator = ( const Vector& vec )
    {
        x = vec.x;
        y = vec.y;
        z = vec.z;
        w = vec.w;
        return *this;
    }

    inline Vector operator + ( const Vector& vec ) const
    {
        return Vector(
                    x + vec.x,
                    y + vec.y,
                    z + vec.z);
    }

    inline Vector operator - ( const Vector& vec ) const
    {
        return Vector(
                    x - vec.x,
                    y - vec.y,
                    z - vec.z);
    }

    inline Vector operator * ( const double rLeftSideValue ) const
    {
        return Vector(
                    x * rLeftSideValue,
                    y * rLeftSideValue,
                    z * rLeftSideValue);
    }

    bool operator == (const Vector &a)
    {
        bool b = fabs(a.x - this->x) <= 10e-4;
        b &= fabs(a.y - this->y) <= 10e-4;
        b &= fabs(a.z - this->z) <= 10e-4;

        return b;
    }

    inline Vector operator / ( const double rLeftSideValue ) const
    {

        double fInv = 1.f / rLeftSideValue;

        return Vector(
                    x * fInv,
                    y * fInv,
                    z * fInv);
    }

    inline Vector operator - () const
    {
        return Vector(-x, -y, -z);
    }
    inline friend Vector operator * ( const double rLeftSideValue, const Vector& vRightSide )
    {
        return Vector(
                    rLeftSideValue * vRightSide.x,
                    rLeftSideValue * vRightSide.y,
                    rLeftSideValue * vRightSide.z);
    }

    inline friend Vector operator / ( const double rLeftSideValue, const Vector& vRightSide )
    {
        return Vector(
                    rLeftSideValue / vRightSide.x,
                    rLeftSideValue / vRightSide.y,
                    rLeftSideValue / vRightSide.z);
    }

    inline friend Vector operator + (const Vector& leftSideValue, const double rightSideValue)
    {
        return Vector(
                    leftSideValue.x + rightSideValue,
                    leftSideValue.y + rightSideValue,
                    leftSideValue.z + rightSideValue);
    }

    inline friend Vector operator * (const Vector& leftSideValue, const Vector& rightSideValue)
    {
        return Vector(
                    leftSideValue.x * rightSideValue.x,
                    leftSideValue.y * rightSideValue.y,
                    leftSideValue.z * rightSideValue.z);
    }

    inline friend Vector operator + (const double leftSideValue, const Vector& rightSideValue)
    {
        return Vector(
                    leftSideValue + rightSideValue.x,
                    leftSideValue + rightSideValue.y,
                    leftSideValue + rightSideValue.z);
    }

    inline friend Vector operator - (const Vector& leftSideValue, const double rightSideValue)
    {
        return Vector(
                    leftSideValue.x - rightSideValue,
                    leftSideValue.y - rightSideValue,
                    leftSideValue.z - rightSideValue);
    }

    inline friend Vector operator - (const double leftSideValue, const Vector& rightSideValue)
    {
        return Vector(
                    leftSideValue - rightSideValue.x,
                    leftSideValue - rightSideValue.y,
                    leftSideValue - rightSideValue.z);
    }

    // arithmetic updates
    inline Vector& operator += ( const Vector& vRightSide )
    {
        x += vRightSide.x;
        y += vRightSide.y;
        z += vRightSide.z;

        return *this;
    }

    inline Vector& operator += ( const double rLeftSideValue )
    {
        x += rLeftSideValue;
        y += rLeftSideValue;
        z += rLeftSideValue;
        return *this;
    }

    inline Vector& operator -= ( const Vector& vRightSide )
    {
        x -= vRightSide.x;
        y -= vRightSide.y;
        z -= vRightSide.z;
        return *this;
    }

    inline Vector& operator -= ( const double rLeftSideValue )
    {
        x -= rLeftSideValue;
        y -= rLeftSideValue;
        z -= rLeftSideValue;
        return *this;
    }

    inline Vector& operator *= ( const double rLeftSideValue )
    {
        x *= rLeftSideValue;
        y *= rLeftSideValue;
        z *= rLeftSideValue;
        return *this;
    }

    inline Vector& operator *= ( const Vector& vRightSide )
    {
        x *= vRightSide.x;
        y *= vRightSide.y;
        z *= vRightSide.z;

        return *this;
    }

    inline Vector& operator /= ( const double rLeftSideValue )
    {
        double fInv = 1.f / rLeftSideValue;
        x *= fInv;
        y *= fInv;
        z *= fInv;

        return *this;
    }
    double length () const
    {
        return sqrt( squaredLength() );
    }
     double squaredLength () const
    {
        return ( x * x + y * y + z * z );
    }
     double dot(const Vector& vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }
     void normalise()
    {
        (*this) *= 1.f / length();
    }
     Vector crossProduct( const Vector& vRightSide ) const
    {
        return Vector(
                    y * vRightSide.z - z * vRightSide.y,
                    z * vRightSide.x - x * vRightSide.z,
                    x * vRightSide.y - y * vRightSide.x);
    }
     Vector normalisedCopy(void) const
    {
        Vector ret = *this;
        ret.normalise();
        return ret;
    }
    static const Vector VECTOR_ZERO;
    static const Vector VECTOR_UNIT_X;
    static const Vector VECTOR_NEGATIVE_UNIT_X;
    static const Vector VECTOR_UNIT_Y;
    static const Vector VECTOR_NEGATIVE_UNIT_Y;
    static const Vector VECTOR_UNIT_Z;
    static const Vector VECTOR_NEGATIVE_UNIT_Z;

public:
    typedef boost::shared_ptr<Vector> ptr;
    typedef std::vector<ptr> ptr_vec;

};
#endif // VECTOR_H
