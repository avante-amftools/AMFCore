//
//  ModelVolumePtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelVolumePtr_hpp
#define ModelVolumePtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelVolume;
    
    typedef std::shared_ptr<ModelVolume> ModelVolumePtr;
    typedef std::shared_ptr<const ModelVolume> ConstModelVolumePtr;
}

#endif /* ModelVolumePtr_hpp */
