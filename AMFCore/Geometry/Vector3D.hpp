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
        
        static constexpr Vector3D infinity()
        {
            return Vector3D(std::numeric_limits<T>::infinity(),
                            std::numeric_limits<T>::infinity(),
                            std::numeric_limits<T>::infinity());
        }
        static constexpr Vector3D minus_nfinity()
        {
            return Vector3D(-std::numeric_limits<T>::infinity(),
                            -std::numeric_limits<T>::infinity(),
                            -std::numeric_limits<T>::infinity());
        }

        static constexpr Vector3D zero()
        {
            return Vector3D();
        }

        Vector3D() :
        _v { (T)0 }
        { }
        
        Vector3D(uint32_t x, uint32_t y, uint32_t z) :
        _v { (T)x, (T)y, (T)z }
        { }
        
        Vector3D(float x, float y, float z) :
        _v { (T)x, (T)y, (T)z }
        { }
        
        Vector3D(double x, double y, double z) :
        _v { (T)x, (T)y, (T)z }
        { }
        
        Vector3D(const Vector3D<uint32_t> rhs) :
        _v { (T)rhs.x(), (T)rhs.y(), (T)rhs.z() }
        { }
        
        Vector3D(const Vector3D<float> rhs) :
        _v { (T)rhs.x(), (T)rhs.y(), (T)rhs.z() }
        { }
        
        Vector3D(const Vector3D<double> rhs) :
        _v { (T)rhs.x(), (T)rhs.y(), (T)rhs.z() }
        { }
        
        T& operator [] (Axis index)
        { return _v[index]; }
        
        const T operator [] (Axis index) const
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

        T& v0()
        { return _v[V0]; }
        
        T v0() const
        { return _v[V0]; }
        
        T& v1()
        { return _v[V1]; }
        
        T v1() const
        { return _v[V1]; }
        
        T& v2()
        { return _v[V2]; }
        
        T v2() const
        { return _v[V2]; }

        Vector3D min(const Vector3D rhs) const
        {
            return Vector3D(std::min(_v[0], rhs._v[0]),
                            std::min(_v[1], rhs._v[1]),
                            std::min(_v[2], rhs._v[2]));
        }
        
        Vector3D max(const Vector3D rhs) const
        {
            return Vector3D(std::max(_v[0], rhs._v[0]),
                            std::max(_v[1], rhs._v[1]),
                            std::max(_v[2], rhs._v[2]));
        }
        
        const bool operator == (const Vector3D& rhs) const
        {
            return (x() == rhs.x()) && (y() == rhs.y()) && (z() == rhs.z());
        }
        
        const bool operator != (const Vector3D& rhs) const
        {
            return (x() != rhs.x()) || (y() != rhs.y()) || (z() != rhs.z());
        }
        
        const bool operator < (const Vector3D& rhs) const
        {
            return ((x() < rhs.x()) ? true :
                    (x() > rhs.x()) ? false :
                    (y() < rhs.y()) ? true :
                    (y() > rhs.y()) ? false :
                    (z() < rhs.z()));
        }
        
        const bool operator > (const Vector3D& rhs) const
        {
            return ((x() > rhs.x()) ? true :
                    (x() < rhs.x()) ? false :
                    (y() > rhs.y()) ? true :
                    (y() < rhs.y()) ? false :
                    (z() > rhs.z()));
        }
        
        const bool operator <= (const Vector3D& rhs) const
        {
            return !((*this) > rhs);
        }
        
        const bool operator >= (const Vector3D& rhs) const
        {
            return !((*this) < rhs);
        }
        
        Vector3D operator + (const Vector3D& rhs) const
        {
            return Vector3D(x()+rhs.x(), y()+rhs.y(), z()+rhs.z());
        }
        
        Vector3D& operator += (const Vector3D& rhs)
        {
            x() += rhs.x(); y() += rhs.y(); z() += rhs.z();
            return *this;
        }
        
        Vector3D operator + (const double rhs) const
        {
            return Vector3D(x()+rhs, y()+rhs, z()+rhs);
        }
        
        Vector3D& operator += (const double rhs)
        {
            x() += rhs; y() += rhs; z() += rhs;
            return *this;
        }
        
        
        Vector3D operator - (const Vector3D& rhs) const
        {
            return Vector3D(x()-rhs.x(), y()-rhs.y(), z()-rhs.z());
        }
        
        Vector3D& operator -= (const Vector3D& rhs)
        {
            x() -= rhs.x(); y() -= rhs.y(); z() -= rhs.z();
            return *this;
        }
        
        Vector3D operator - (const double rhs) const
        {
            return Vector3D(x()-rhs, y()-rhs, z()-rhs);
        }
        
        Vector3D& operator -= (const double rhs)
        {
            x() -= rhs; y() -= rhs; z() -= rhs;
            return *this;
        }
        
        Vector3D operator * (const double rhs) const
        {
            return Vector3D(x()*rhs, y()*rhs, z()*rhs);
        }
        
        Vector3D& operator *= (const double rhs)
        {
            x() *= rhs; y() *= rhs; z() *= rhs;
            return *this;
        }
        
        Vector3D operator / (const double rhs) const
        {
            return Vector3D(x()/rhs, y()/rhs, z()/rhs);
        }
        
        Vector3D& operator /= (const double rhs)
        {
            x() /= rhs; y() /= rhs; z() /= rhs;
            return *this;
        }
        
        // Cross product.
        //  This was operator ^ (bitwise exclusive OR) in ImatiSTL.
        
        Vector3D crossProduct(const Vector3D& rhs) const
        {
            return Vector3D(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
                            _v[2]*rhs._v[0]-_v[0]*rhs._v[2],
                            _v[0]*rhs._v[1]-_v[1]*rhs._v[0]);
        }
        
        // Dot product.
        //  This was operator * (multiply) in ImatiSTL.
        
        double dotProduct(const Vector3D& rhs) const
        {
            return (_v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2]);
        }
        
        double length() const
        {
            return std::sqrt(_v[X]*_v[X] + _v[Y]*_v[Y] + _v[Z]*_v[Z]);
        }
        
    };
    
    typedef Vector3D<uint32_t> UInt32Vector3D;
    typedef Vector3D<float> SingleVector3D;
    typedef Vector3D<double> DoubleVector3D;
    
    /*
    struct DoubleVector3DTrio
    {
        DoubleVector3D values[3];
    };
     */
    
    typedef DoubleVector3D DoubleVector3DTrio[3];
}

#endif /* Vector3D_hpp */
