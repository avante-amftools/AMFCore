//
//  ModelElementPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef ModelElementPtr_hpp
#define ModelElementPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelElement;
    
    typedef std::shared_ptr<ModelElement> ModelElementPtr;
    typedef std::shared_ptr<const ModelElement> ConstModelElementPtr;
    typedef std::weak_ptr<ModelElement> WeakModelElementPtr;
    typedef std::weak_ptr<const ModelElement> ConstWeakModelElementPtr;
}

#endif /* ModelElementPtr_hpp */
