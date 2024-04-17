//
//  ModelMetadataPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 4/13/23.
//

#ifndef ModelMetadataPtr_hpp
#define ModelMetadataPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelMetadata;
    
    typedef std::shared_ptr<ModelMetadata> ModelMetadataPtr;
    typedef std::shared_ptr<const ModelMetadata> ConstModelMetadataPtr;
}

#endif /* ModelMetadataPtr_hpp */
