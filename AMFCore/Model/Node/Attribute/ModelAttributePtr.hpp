//
//  ModelAttributePtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef ModelAttributePtr_hpp
#define ModelAttributePtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelAttribute;
    
    typedef std::shared_ptr<ModelAttribute> ModelAttributePtr;
    typedef std::shared_ptr<const ModelAttribute> ConstModelAttributePtr;
    typedef std::weak_ptr<ModelAttribute> WeakModelAttributePtr;
    typedef std::weak_ptr<const ModelAttribute> ConstWeakModelAttributePtr;
}

#endif /* ModelAttributePtr_hpp */
