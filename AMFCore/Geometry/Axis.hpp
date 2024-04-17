//
//  Axis.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef Axis_hpp
#define Axis_hpp

namespace AMFCore
{
    enum Axis {
        X,
        Y,
        Z,
        Undefined,
        V0 = X,
        V1 = Y,
        V2 = Z
    };
    enum Axes { XY, YZ, ZX };
    
    inline Axis operator++(Axis const& rhs)
    { return Axis(rhs + 1); }
    
    inline Axis& operator++(Axis& rhs, int)
    {
        rhs = Axis(rhs + 1);
        return rhs;
    }
    
    inline Axis operator--(Axis const& rhs)
    { return Axis(rhs - 1); }
    
    inline Axes operator++(Axes const& rhs)
    { return Axes(rhs + 1); }
    
    inline Axes& operator++(Axes& rhs, int)
    {
        rhs = Axes(rhs + 1);
        return rhs;
    }
    
    inline Axes operator--(Axes const& rhs)
    { return Axes(rhs - 1); }
}

#endif /* Axis_hpp */
