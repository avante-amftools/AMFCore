//
//  Color.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/7/23.
//

#ifndef Color_hpp
#define Color_hpp

#include <algorithm>

namespace AMFCore
{
    enum Channel {
        R,
        G,
        B,
        A,
        Channels
    };
    
    inline Channel operator++(Channel const& rhs)
    { return Channel(rhs + 1); }
    
    inline Channel& operator++(Channel& rhs, int)
    {
        rhs = Channel(rhs + 1);
        return rhs;
    }
    
    inline Channel operator--(Channel const& rhs)
    { return Channel(rhs - 1); }

    template <class T> class Color
    {
    protected:
        T _c[Channels];
        
    public:
        typedef T value_type;
                
        Color() :
        _c { 0 }
        { }
        
        Color(T r, T g, T b, T a) :
        _c { r, g, b, a }
        { }
                
        T& operator [] (Channel index)
        { return _c[index]; }
        
        const T operator [] (Channel index) const
        { return _c[index]; }
        
        T& r()
        { return _c[R]; }
        
        T r() const
        { return _c[R]; }
        
        T& g()
        { return _c[G]; }
        
        T g() const
        { return _c[G]; }
        
        T& b()
        { return _c[B]; }
        
        T b() const
        { return _c[B]; }

        T& a()
        { return _c[A]; }
        
        T a() const
        { return _c[A]; }

        const bool operator == (const Color<T>& rhs) const
        {
            return (_c[R] == rhs._c[R] &&
                    _c[G] == rhs._c[G] &&
                    _c[B] == rhs._c[B] &&
                    _c[A] == rhs._c[A]);
        }
        
        const bool operator < (const Color<T>& rhs) const
        {
            return (_c[R] < rhs._c[R] ? true :
                    _c[R] > rhs._c[R] ? false :
                    _c[G] < rhs._c[G] ? true :
                    _c[G] > rhs._c[G] ? false :
                    _c[B] < rhs._c[B] ? true :
                    _c[B] > rhs._c[B] ? false :
                    _c[A] < rhs._c[A] ? true :
                    _c[A] > rhs._c[A]);
        }
        
        const bool operator > (const Color<T>& rhs) const
        {
            return (_c[R] > rhs._c[R] ? true :
                    _c[R] < rhs._c[R] ? false :
                    _c[G] > rhs._c[G] ? true :
                    _c[G] < rhs._c[G] ? false :
                    _c[B] > rhs._c[B] ? true :
                    _c[B] < rhs._c[B] ? false :
                    _c[A] > rhs._c[A] ? true :
                    _c[A] < rhs._c[A]);
        }
    };
    
    // We can't use the template version for UInt8Color
    //  because it needs to work either big or little-endian.
    
    class UInt8Color
    {
    protected:
        uint32_t _c;
        
    public:
        enum { R, G, B, A };
        
        static UInt8Color White;

        UInt8Color() :
        _c(0)
        { }
        
        UInt8Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
        _c((uint32_t)(r) << 24 | (uint32_t)(g) << 16 | (uint32_t)(b) << 8 | (uint32_t)(a))
        { }
                
        UInt8Color(const UInt8Color& rhs) :
        _c(rhs._c)
        { }
        
        UInt8Color(const Color<float>& rhs) :
        UInt8Color(fromFloat(rhs.r()), fromFloat(rhs.g()), fromFloat(rhs.b()), fromFloat(rhs.a()))
        { }
        
        UInt8Color(const Color<double>& rhs) :
        UInt8Color(fromDouble(rhs.r()), fromDouble(rhs.g()), fromDouble(rhs.b()), fromDouble(rhs.a()))
        { }
        
        // No array accessors, because we're trying to keep this code uncomplicated.
        // Only const r, g, b and a accessors, see above...
                
        uint8_t r() const
        { return _c & 0xFF; }
                
        uint8_t g() const
        { return (_c >> 8) & 0xFF; }
                
        uint8_t b() const
        { return (_c >> 16) & 0xFF; }
                
        uint8_t a() const
        { return (_c >> 24) & 0xFF; }
        
        const bool operator == (const UInt8Color& rhs) const
        {
            return _c == rhs._c;
        }

        const bool operator < (const UInt8Color& rhs) const
        {
            return _c < rhs._c;
        }

        const bool operator > (const UInt8Color& rhs) const
        {
            return _c > rhs._c;
        }
        
        uint32_t rgba() const
        {
            return _c;
        }

    protected:
        static uint8_t fromFloat(float value)
        { return std::clamp(value * 255.0, 0.0, 255.0); }
        
        static uint8_t fromDouble(double value)
        { return std::clamp(value * 255.0, 0.0, 255.0); }

    };
    
    class SingleColor : public Color<float>
    {
    public:
        static SingleColor White;

        SingleColor() :
        Color()
        { }
        
        SingleColor(float r, float g, float b, float a) :
        Color(r, g, b, a)
        { }
        
        SingleColor(const Color<uint8_t>& rhs) :
        Color(fromUInt8(rhs.r()), fromUInt8(rhs.g()), fromUInt8(rhs.b()), fromUInt8(rhs.a()))
        { }
        
        SingleColor(const Color<float>& rhs) :
        Color(rhs.r(), rhs.g(), rhs.b(), rhs.a())
        { }
        
        SingleColor(const Color<double>& rhs) :
        Color(rhs.r(), rhs.g(), rhs.b(), rhs.a())
        { }
        
    protected:
        static float fromUInt8(uint8_t value)
        { return value / 255.0; }
    };
    
    class DoubleColor : public Color<double>
    {
    public:
        static DoubleColor White;

        DoubleColor() :
        Color()
        { }
        
        DoubleColor(float r, float g, float b, float a) :
        Color(r, g, b, a)
        { }
        
        DoubleColor(const Color<uint8_t>& rhs) :
        Color(fromUInt8(rhs.r()), fromUInt8(rhs.g()), fromUInt8(rhs.b()), fromUInt8(rhs.a()))
        { }
        
        DoubleColor(const Color<float>& rhs) :
        Color(rhs.r(), rhs.g(), rhs.b(), rhs.a())
        { }
        
        DoubleColor(const Color<double>& rhs) :
        Color(rhs.r(), rhs.g(), rhs.b(), rhs.a())
        { }
        
    protected:
        static double fromUInt8(uint8_t value)
        { return value / 255.0; }
    };
    
    typedef DoubleColor DoubleColorTrio[3];
}

#endif /* Color_hpp */
