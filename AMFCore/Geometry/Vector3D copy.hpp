//
//  Vector3D.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/9/23.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

#include "Axis.hpp"
#include <stdint.h>
#include <algorithm>
#include <cmath>

namespace AMFCore
{
    template <class T> class Vector3D
    {
    protected:
        T _v[3];
        
    public:
        typedef T value_type;
        
        Vector3D() :
        _v { (T)0 }
        { }
        
        Vector3D(T x, T y, T z) :
        _v { x, y, z }
        { }
        
        T& operator [] (int index)
        { return _v[index]; }
        
        const T operator [] (int index) const
        { return _v[index]; }
        
        T& x()
        { return _v[X]; }

        T x() const
        { return _v[X]; }
        
        T& y()
        { return _v[Y]; }

        T y() const
        { return _v[Y]; }
        
        T& z()
        { return _v[Z]; }

        T z() const
        { return _v[Z]; }
        
        Vector3D<T> min(const Vector3D<T> rhs) const
        {
            return Vector3D<T>(std::min(_v[0], rhs._v[0]),
                               std::min(_v[1], rhs._v[1]),
                               std::min(_v[2], rhs._v[2]));
        }

        Vector3D<T> max(const Vector3D<T> rhs) const
        {
            return Vector3D<T>(std::max(_v[0], rhs._v[0]),
                               std::max(_v[1], rhs._v[1]),
                               std::max(_v[2], rhs._v[2]));
        }
        
        const bool operator == (const Vector3D<T>& rhs) const
        {
            return (x() == rhs.x()) && (y() == rhs.y()) && (z() == rhs.z());
        }
        
        const bool operator != (const Vector3D<T>& rhs) const
        {
            return (x() != rhs.x()) || (y() != rhs.y()) || (z() != rhs.z());
        }
        
        const bool operator < (const Vector3D<T>& rhs) const
        {
            return ((x() < rhs.x()) ? true :
                    (x() > rhs.x()) ? false :
                    (y() < rhs.y()) ? true :
                    (y() > rhs.y()) ? false :
                    (z() < rhs.z()));
        }
        
        const bool operator > (const Vector3D<T>& rhs) const
        {
            return ((x() > rhs.x()) ? true :
                    (x() < rhs.x()) ? false :
                    (y() > rhs.y()) ? true :
                    (y() < rhs.y()) ? false :
                    (z() > rhs.z()));
        }
        
        const bool operator <= (const Vector3D<T>& rhs) const
        {
            return !((*this) > rhs);
        }
        
        const bool operator >= (const Vector3D<T>& rhs) const
        {
            return !((*this) < rhs);
        }
        
        Vector3D<T> operator + (const Vector3D<T>& rhs) const
        {
            return Point3D(x()+rhs.x(), y()+rhs.y(), z()+rhs.z());
        }
        
        Vector3D<T>& operator += (const Vector3D<T>& rhs)
        {
            x() += rhs.x(); y() += rhs.y(); z() += rhs.z();
            return *this;
        }
        
        Vector3D<T> operator + (const double rhs) const
        {
            return Vector3D<T>(x()+rhs, y()+rhs, z()+rhs);
        }
        
        Vector3D<T>& operator += (const double rhs)
        {
            x() += rhs; y() += rhs; z() += rhs;
            return *this;
        }
        
        
        Vector3D operator - (const Vector3D& rhs) const
        {
            return Vector3D(x()-rhs.x(), y()-rhs.y(), z()-rhs.z());
        }
        
        Vector3D<T>& operator -= (const Vector3D<T>& rhs)
        {
            x() -= rhs.x(); y() -= rhs.y(); z() -= rhs.z();
            return *this;
        }
        
        Vector3D<T> operator - (const double rhs) const
        {
            return Vector3D<T>(x()-rhs, y()-rhs, z()-rhs);
        }
        
        Vector3D<T>& operator -= (const double rhs)
        {
            x() -= rhs; y() -= rhs; z() -= rhs;
            return *this;
        }
        
        Vector3D<T> operator * (const double rhs) const
        {
            return Point3D(x()*rhs, y()*rhs, z()*rhs);
        }
        
        Vector3D<T>& operator *= (const double rhs)
        {
            x() *= rhs; y() *= rhs; z() *= rhs;
            return *this;
        }
        
        Vector3D<T> operator / (const double rhs) const
        {
            return Vector3D<T>(x()/rhs, y()/rhs, z()/rhs);
        }
        
        Vector3D<T>& operator /= (const double rhs)
        {
            x() /= rhs; y() /= rhs; z() /= rhs;
            return *this;
        }
        
        // Cross product.
        //  This was operator ^ (bitwise exclusive OR) in ImatiSTL.
        
        Vector3D<T> crossProduct(const Vector3D<T>& rhs) const
        {
            return Vector3D<T>(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
                           _v[2]*rhs._v[0]-_v[0]*rhs._v[2],
                           _v[0]*rhs._v[1]-_v[1]*rhs._v[0]);
        }
        
        // Dot product.
        //  This was operator * (multiply) in ImatiSTL.
        
        double dotProduct(const Vector3D<T>& rhs) const
        {
            return (_v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2]);
        }
        
        double length() const
        {
            return std::sqrt(_v[X]*_v[X] + _v[Y]*_v[Y] + _v[Z]*_v[Z]);
        }

    };
    
    class UInt32Vector3D : public Vector3D<uint32_t>
    {
    public:
        UInt32Vector3D() :
        Vector3D()
        { }
        
        UInt32Vector3D(uint32_t x, uint32_t y, uint32_t z) :
        Vector3D(x, y, z)
        { }

        UInt32Vector3D(const UInt32Vector3D& rhs) :
        Vector3D(rhs.x(), rhs.y(), rhs.z())
        { }
    };

    class SingleVector3D : public Vector3D<float>
    {
    public:
        SingleVector3D() :
        Vector3D()
        { }
        
        SingleVector3D(float x, float y, float z) :
        Vector3D(x, y, z)
        { }
        
        SingleVector3D(const SingleVector3D& rhs) :
        Vector3D(rhs.x(), rhs.y(), rhs.z())
        { }
        
        SingleVector3D(const Vector3D<double>& rhs) :
        Vector3D(rhs.x(), rhs.y(), rhs.z())
        { }
    };

    class DoubleVector3D : public Vector3D<double>
    {
    public:
        DoubleVector3D() :
        Vector3D()
        { }
        
        DoubleVector3D(float x, float y, float z) :
        Vector3D(x, y, z)
        { }
        
        DoubleVector3D(const Vector3D<float>& rhs) :
        Vector3D(rhs.x(), rhs.y(), rhs.z())
        { }
        
        DoubleVector3D(const DoubleVector3D& rhs) :
        Vector3D(rhs.x(), rhs.y(), rhs.z())
        { }
    };
}

#endif /* Vector3D_hpp */
