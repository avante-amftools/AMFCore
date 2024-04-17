//
//  ModelUnitPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/15/23.
//

#ifndef ModelUnitPtr_hpp
#define ModelUnitPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelUnit;
    
    typedef std::shared_ptr<ModelUnit> ModelUnitPtr;
    typedef std::shared_ptr<const ModelUnit> ConstModelUnitPtr;
}

#endif /* ModelUnitPtr_hpp */
