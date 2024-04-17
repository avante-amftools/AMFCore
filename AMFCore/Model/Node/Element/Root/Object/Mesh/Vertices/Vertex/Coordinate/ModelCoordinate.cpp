//
//  ModelCoordinate.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#include "ModelCoordinate.hpp"

#include "ModelVertex.hpp"

#include "tinyxml2.h"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelCoordinate::Identifier("coordinates");
    
    ModelElementPtr ModelCoordinate::_newModelCoordinate()
    {
        return std::make_shared<ModelCoordinate>();
    }
    
    void ModelCoordinate::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelCoordinate);

            initialized = true;
        }
    }
    
    ModelCoordinatePtr ModelCoordinate::newModelCoordinate()
    {
        return std::dynamic_pointer_cast<ModelCoordinate>(ModelElement::newModelElement(ModelCoordinate::Identifier));
    }
    
    ModelCoordinatePtr ModelCoordinate::newModelCoordinate(const DoubleVector3D& coordinate)
    {
        auto result = ModelCoordinate::newModelCoordinate();
        
        result->setValueAsVector3D(coordinate);
        
        return result;
    }

    void ModelCoordinate::fromXML(const XMLElement* xmlElement)
    {
        static const char* labels[3] { "x", "y", "z" };
                
        // Load everything except for the actual coordinate values as ModelElement objects.
        
        super::fromXML(xmlElement);
        
        // Move the x, y, z and a values to _color.
        
        for (auto i = V0; i <= V2; i++)
        {
            auto element = this->elementWithIdentifier(labels[i]);
            {
                if (element == nullptr)
                    throw(std::runtime_error("could not locate required <" + std::string(labels[i]) + "> element"));
                
                _valueAsVector3D[i] = element->valueAsDouble();
            }
        }
    }
        
    void ModelCoordinate::debugShow(std::string indent)
    {
        const char* identifier = this->identifier().c_str();
        
        DoubleVector3D coordinates = this->valueAsVector3D();

        printf("%s%s %s [%f %f %f]\n", indent.c_str(), identifier, this->valueAsString().c_str(),
               coordinates[X],
               coordinates[Y],
               coordinates[Z]);
    }

}
