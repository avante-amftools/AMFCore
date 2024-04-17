//
//  ModelObjectPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelObjectPtr_hpp
#define ModelObjectPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelObject;
    
    typedef std::shared_ptr<ModelObject> ModelObjectPtr;
    typedef std::shared_ptr<const ModelObject> ConstModelObjectPtr;
}

#endif /* ModelObjectPtr_hpp */
