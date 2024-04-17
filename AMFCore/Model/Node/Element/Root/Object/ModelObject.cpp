//
//  ModelObject.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#include "ModelObject.hpp"
#include "ModelRoot.hpp"
#include "ModelMesh.hpp"
#include "ModelColor.hpp"
#include "ModelMetadata.hpp"
#include "ModelMetadataType.hpp"

#include <assert.h>

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelObject::Identifier("object");
    
    ModelElementPtr ModelObject::_newModelObject()
    {
        return std::make_shared<ModelObject>();
    }
    
    void ModelObject::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelObject);
            
            ModelColor::initialize();
            ModelMesh::initialize();
            
            initialized = true;
        }
    }
    
    const std::string& ModelObject::name() const
    {
        return this->modelName()->valueAsString();
    }


    ModelMeshPtr ModelObject::defaultModelMesh()
    {
        // There can be only one!
        
        ModelMeshPtr result = this->modelMesh();
        if (result == nullptr)
        {
            result = std::dynamic_pointer_cast<ModelMesh>(this->newModelMesh());
            result->setParent(this->sharedModelElementPtr());
            
            ModelMeshPtr test = this->modelMesh();
            
            assert(test == result);
        }
        
        return result;
    }

    ModelVolumePtr ModelObject::defaultModelVolume()
    {
        return this->defaultModelMesh()->defaultModelVolume();
    }
    
    ModelMeshPtr ModelObject::newModelMesh()
    {
        return ModelMesh::newModelMesh();
    }

    ModelMeshPtr ModelObject::modelMesh()
    {
        return std::dynamic_pointer_cast<ModelMesh>(elementWithIdentifier(ModelMesh::Identifier));
    }

    ConstModelMeshPtr ModelObject::modelMesh() const
    {
        return std::dynamic_pointer_cast<const ModelMesh>(elementWithIdentifier(ModelMesh::Identifier));
    }
    
    ModelMetadataPtr ModelObject::modelName()
    {
        return this->metadataWithType(ModelMetadataType::MetadataTypeName);
    }
    
    ConstModelMetadataPtr ModelObject::modelName() const
    {
        return this->metadataWithType(ModelMetadataType::MetadataTypeName);
    }
}
