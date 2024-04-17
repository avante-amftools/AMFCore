//
//  ModelNormal.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/8/23.
//

#include "ModelNormal.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelNormal::Identifier("normal");
    
    ModelElementPtr ModelNormal::_newModelNormal()
    {
        return std::make_shared<ModelNormal>();
    }
    
    ModelNormalPtr ModelNormal::newModelNormal()
    {
        return std::dynamic_pointer_cast<ModelNormal>( ModelElement::newModelElement(ModelNormal::Identifier));
    }
    
    ModelNormalPtr ModelNormal::newModelNormal(const DoubleVector3D& normal)
    {
        auto result = ModelNormal::newModelNormal();
        result->setValueAsVector3D(normal);
        return result;
    }

    void ModelNormal::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelNormal);

            initialized = true;
        }
    }

#warning Remove this.
    void ModelNormal::fromXML(const XMLElement* xmlElement)
    {
        super::fromXML(xmlElement);
    }
    
    void ModelNormal::debugShow(std::string indent)
    {
        const char* identifier = this->identifier().c_str();
        
        DoubleVector3D vector = this->valueAsVector3D();
        
        printf("%s%s %s [%f %f %f]\n", indent.c_str(), identifier, this->valueAsString().c_str(),
               vector[X],
               vector[Y],
               vector[Z]);
    }

}
