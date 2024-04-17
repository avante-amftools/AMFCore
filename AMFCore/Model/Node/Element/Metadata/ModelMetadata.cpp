//
//  ModelMetadata.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 4/13/23.
//

#include "ModelMetadata.hpp"

#include "ModelAttribute.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelMetadata::Identifier("metadata");
    
    ModelElementPtr ModelMetadata::_newModelMetadata()
    {
        return std::make_shared<ModelMetadata>();
    }
    
    void ModelMetadata::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelMetadata);

            initialized = true;
        }
    }
    
    const std::string& ModelMetadata::type() const
    {
        auto typeAttribute = this->attributeWithIdentifier("type");
        
        return typeAttribute->valueAsString();
    }
    
    void ModelMetadata::setType(const std::string& type)
    {
        auto typeAttribute = this->attributeWithIdentifier("type");
        
        typeAttribute->setValueAsString(type);
    }
    
    void ModelMetadata::debugShow(std::string indent)
    {
        /*
        const char* identifier = this->identifier().c_str();
        
        printf("%s%s %s %s\n", indent.c_str(), identifier, this->type().c_str(), this->valueAsString().c_str());
         */
    }


}
