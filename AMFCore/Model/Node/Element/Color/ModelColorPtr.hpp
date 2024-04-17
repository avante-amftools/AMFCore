//
//  ModelColorPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef ModelColorPtr_hpp
#define ModelColorPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelColor;
    
    typedef std::shared_ptr<ModelColor> ModelColorPtr;
    typedef std::shared_ptr<const ModelColor> ConstModelColorPtr;
}

#endif /* ModelColorPtr_hpp */
