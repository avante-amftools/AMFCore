//
//  ModelCoordinatePtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef ModelCoordinatePtr_hpp
#define ModelCoordinatePtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelCoordinate;
    
    typedef std::shared_ptr<ModelCoordinate> ModelCoordinatePtr;
    typedef std::shared_ptr<const ModelCoordinate> ConstModelCoordinatePtr;
}

#endif /* ModelCoordinatePtr_hpp */
