//
//  ModelMeshPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelMeshPtr_hpp
#define ModelMeshPtr_hpp

#include <memory>

namespace AMFCore
{
    class ModelMesh;
    
    typedef std::shared_ptr<ModelMesh> ModelMeshPtr;
    typedef std::shared_ptr<const ModelMesh> ConstModelMeshPtr;
}

#endif /* ModelMeshPtr_hpp */
