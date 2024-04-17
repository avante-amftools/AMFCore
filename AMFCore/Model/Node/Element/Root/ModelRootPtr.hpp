//
//  ModelRootPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelRootPtr_hpp
#define ModelRootPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelRoot;
    
    typedef std::shared_ptr<ModelRoot> ModelRootPtr;
    typedef std::shared_ptr<const ModelRoot> ConstModelRootPtr;
}

#endif /* ModelRootPtr_hpp */
