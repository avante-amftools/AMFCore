//
//  ModelTrianglePtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/4/23.
//

#ifndef ModelTrianglePtr_hpp
#define ModelTrianglePtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelTriangle;
    
    typedef std::shared_ptr<ModelTriangle> ModelTrianglePtr;
    typedef std::shared_ptr<const ModelTriangle> ConstModelTrianglePtr;
}

#endif /* ModelTrianglePtr_hpp */
