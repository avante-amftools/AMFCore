//
//  ModelMetadataTypePtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/24/23.
//

#ifndef ModelMetadataTypePtr_hpp
#define ModelMetadataTypePtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelMetadataType;
    
    typedef std::shared_ptr<ModelMetadataType> ModelMetadataTypePtr;
    typedef std::shared_ptr<const ModelMetadataType> ConstModelMetadataTypePtr;
}

#endif /* ModelMetadataTypePtr_hpp */
