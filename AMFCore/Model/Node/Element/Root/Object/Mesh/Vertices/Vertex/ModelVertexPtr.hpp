//
//  ModelVertexPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef ModelVertexPtr_hpp
#define ModelVertexPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelVertex;
    
    typedef std::shared_ptr<ModelVertex> ModelVertexPtr;
    typedef std::shared_ptr<const ModelVertex> ConstModelVertexPtr;
}

#endif /* ModelVertexPtr_hpp */
