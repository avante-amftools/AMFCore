//
//  ModelNodePtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef ModelNodePtr_hpp
#define ModelNodePtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelNode;
    
    typedef std::shared_ptr<ModelNode> ModelNodePtr;
    typedef std::shared_ptr<const ModelNode> ConstModelNodePtr;
}

#endif /* ModelNodePtr_hpp */
