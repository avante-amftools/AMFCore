//
//  STLPrimitive.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/25/23.
//

#ifndef STLPrimitive_hpp
#define STLPrimitive_hpp

#include "Vector3D.hpp"

#include <architecture/byte_order.h>
#include <sstream>

#include "Buffer.hpp"

// #include <assert.h>

namespace AMFCore
{
    
#pragma pack(push)
#pragma pack(1)
    
    template <class T>
    struct STLPrimitive
    {
        T value;
        
        inline STLPrimitive() :
        value(0)
        { }
        
        inline STLPrimitive(const T& value_) :
        value(value_)
        { }
        
        inline STLPrimitive(Buffer& buffer)
        {
            readBinaryFrom(buffer, *this);
        }
        
        inline void toNativeEndian()
        {
#if (BYTE_ORDER == BIG_ENDIAN)
            std::reverse(reinterpret_cast<char*>(&value), reinterpret_cast<char*>(&value)+sizeof(T));
#endif
        }
        
        inline void toStreamEndian()
        {
            this->toNativeEndian();
        }
        
        inline void writeAsciiTo(std::stringstream& stream)
        {
            stream << value;
        }
    };
    
    template <typename T>
    bool operator < (const STLPrimitive<T>& lhs, const STLPrimitive<T>& rhs)
    {
        return (lhs.value < rhs.value);
    }
    
    template <typename T>
    bool operator == (const STLPrimitive<T>& lhs, const STLPrimitive<T>& rhs)
    {
        bool result = nearEqual(lhs.value, rhs.value);
        return result;
    }
    
    template <typename T>
    bool operator > (const STLPrimitive<T>& lhs, const STLPrimitive<T>& rhs)
    {
        return (lhs.value > rhs.value);
    }
    
    typedef STLPrimitive<int16_t> STL_int16_t;
    typedef STLPrimitive<int32_t> STL_int32_t;
    
    struct STLVec3
    {
        STLPrimitive<float> x;
        STLPrimitive<float> y;
        STLPrimitive<float> z;
        
        inline STLVec3()
        { }
        
        inline STLVec3(const STLVec3& vector) :
        x(vector.x), y(vector.y), z(vector.z)
        { }
        
        inline STLVec3(float x_, float y_, float z_) :
        x(x_), y(y_), z(z_)
        { }
        
        inline STLVec3(const SingleVector3D vector) :
        x(vector.x()), y(vector.y()), z(vector.z())
        {}
        
        inline STLVec3(const DoubleVector3D& vector) :
        x(vector.x()), y(vector.y()), z(vector.z())
        { }

        float& operator[] (int i)
        { return (i==0 ? x.value : i==1 ? y.value : z.value); }
        
        inline void toNativeEndian()
        {
            x.toNativeEndian();
            y.toNativeEndian();
            z.toNativeEndian();
        }
        
        inline void toStreamEndian()
        {
            this->toNativeEndian();
        }
        
        inline void writeAsciiTo(std::stringstream& stream, const char* label)
        {
            stream << label << " ";
            
            x.writeAsciiTo(stream);
            stream << " ";
            
            y.writeAsciiTo(stream);
            stream << " ";
            
            z.writeAsciiTo(stream);
            stream << std::endl;
        }
        
        inline const DoubleVector3D asVector3D() const
        {
            return DoubleVector3D(x.value, y.value, z.value);
        }
    };
    
    struct STLTriangle
    {
        STLVec3 normal;
        STLVec3 v1;
        STLVec3 v2;
        STLVec3 v3;
        STL_int16_t attributeBytes;
                
        inline STLTriangle()
        { }
        
        inline STLTriangle(const STLTriangle& triangle) :
        normal(triangle.normal), v1(triangle.v1), v2(triangle.v2), v3(triangle.v3), attributeBytes(triangle.attributeBytes)
        { }
        
        inline STLTriangle(STLVec3 normal_, STLVec3 v1_, STLVec3 v2_, STLVec3 v3_, STL_int16_t attributeBytes_) :
        normal(normal_), v1(v1_), v2(v2_), v3(v3_), attributeBytes(attributeBytes_)
        { }
        
        inline STLTriangle(Buffer& buffer)
        {
            readBinaryFrom(buffer, *this);
        }
        
        STLVec3& operator[] (int i)
        { return (i==0 ? v1 : i==1 ? v2 : v3); }
        
        inline void toNativeEndian()
        {
            normal.toNativeEndian();
            v1.toNativeEndian();
            v2.toNativeEndian();
            v3.toNativeEndian();
            attributeBytes.toNativeEndian();
            
            printf("STLTriangle:\n");
            printf("normal: [%f %f %f]\n", normal.x.value, normal.y.value, normal.z.value);
            printf("    v1: [%f %f %f]\n", v1.x.value, v1.y.value, v1.z.value);
            printf("    v2: [%f %f %f]\n", v2.x.value, v2.y.value, v2.z.value);
            printf("    v3: [%f %f %f]\n", v3.x.value, v3.y.value, v3.z.value);
            printf("  attr: %04X\n", attributeBytes.value);
        }
        
        inline void toStreamEndian()
        {
            this->toNativeEndian();
        }
        
        inline void writeAsciiTo(std::stringstream& stream)
        {
            normal.writeAsciiTo(stream, " facet normal");
            
            stream << "  outer loop" << std::endl;
            
            for (int i = 0; i < 3; i++)
            {
                (*this)[i].writeAsciiTo(stream, "  vertex");
            }
            
            stream << " endloop" << std::endl;
            stream << "endfacet" << std::endl;
        }
    };
    
#pragma pack(pop)
        
}

#endif /* STLPrimitive_hpp */
