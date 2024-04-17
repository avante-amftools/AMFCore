//
//  ModelVerticesPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/5/23.
//

#ifndef ModelVerticesPtr_hpp
#define ModelVerticesPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelVertices;
    
    typedef std::shared_ptr<ModelVertices> ModelVerticesPtr;
    typedef std::shared_ptr<const ModelVertices> ConstModelVerticesPtr;
}

#endif /* ModelVerticesPtr_hpp */
