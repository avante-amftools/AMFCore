//
//  ModelNormalPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/8/23.
//

#ifndef ModelNormalPtr_hpp
#define ModelNormalPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelNormal;
    
    typedef std::shared_ptr<ModelNormal> ModelNormalPtr;
    typedef std::shared_ptr<const ModelNormal> ConstModelNormalPtr;
}

#endif /* ModelNormalPtr_hpp */
