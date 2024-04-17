//
//  ModelRoot.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#include "ModelRoot.hpp"

#include "ModelUnit.hpp"
#include "ModelColor.hpp"
#include "ModelObject.hpp"
#include "ModelMetadata.hpp"

#include "tinyxml2.h"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelRoot::Identifier("amf");
    
    
    ModelElementPtr ModelRoot::_newModelRoot()
    {
        return std::make_shared<ModelRoot>();
    }
    
    void ModelRoot::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelRoot);
            
            ModelUnit::initialize();
            
            ModelColor::initialize();
            
            ModelObject::initialize();
            
            ModelMetadata::initialize();
            
            // ModelMaterial::initialize();
            // ModelConstellation::initialize();
            
            initialized = true;
        }
    }
    
    std::unique_ptr<XMLDocument> ModelRoot::toXMLDocument() const
    {
        auto result = std::make_unique<XMLDocument>();
        
        XMLDeclaration* declaration = result->NewDeclaration();
        result->LinkEndChild(declaration);
        
        XMLElement* rootElement = result->InsertEndChild(result->NewElement(this->identifier().c_str()))->ToElement();
        
        const std::string& value(this->valueAsString());
        
        if (value != "")
        {
            rootElement->SetText(value.c_str());
        }
        
        this->childrenToXML(rootElement);
        
        return result;
    }

    ModelObjectPtr ModelRoot::newModelObject()
    {
        auto modelElement = ModelElement::newModelElement(ModelObject::Identifier);
        return std::dynamic_pointer_cast<ModelObject>(modelElement);
    }

    ModelUnitPtr ModelRoot::modelUnit()
    {
        return std::dynamic_pointer_cast<ModelUnit>(attributeWithIdentifier(ModelUnit::Identifier));
    }
    
    ConstModelUnitPtr ModelRoot::modelUnit() const
    {
        return std::dynamic_pointer_cast<const ModelUnit>(elementWithIdentifier(ModelUnit::Identifier));
    }

    
    ModelColorPtr ModelRoot::modelColor()
    {
        return std::dynamic_pointer_cast<ModelColor>(elementWithIdentifier(ModelColor::Identifier));
    }
    
    ConstModelColorPtr ModelRoot::modelColor() const
    {
        return std::dynamic_pointer_cast<const ModelColor>(elementWithIdentifier(ModelColor::Identifier));
    }

    ModelObjectPtr ModelRoot::defaultModelObject()
    {
        auto result = std::dynamic_pointer_cast<ModelObject>(elementWithIdentifier(ModelObject::Identifier));
        
        if (result == nullptr)
        {
            result = std::dynamic_pointer_cast<ModelObject>(this->newModelObject());
            result->setParent(sharedModelElementPtr());
        }
        
        return result;
    }
    
    ModelVolumePtr ModelRoot::defaultModelVolume()
    {
        return this->defaultModelObject()->defaultModelVolume();
    }

    
    std::vector<ModelObjectPtr> ModelRoot::modelObjects()
    {
        std::vector<ModelObjectPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelObject::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelObject>(*i));
        }
        
        return result;
    }
    
    const std::vector<ConstModelObjectPtr> ModelRoot::modelObjects() const
    {
        std::vector<ConstModelObjectPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelObject::Identifier)
                result.push_back(std::dynamic_pointer_cast<const ModelObject>(*i));
        }
        
        return result;
    }

    std::vector<ModelElementPtr> ModelRoot::modelMaterials()
    {
        std::vector<ModelElementPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == "material")
                result.push_back(std::dynamic_pointer_cast<ModelElement>(*i));
        }
        
        return result;
    }

    const std::vector<ConstModelElementPtr> ModelRoot::modelMaterials() const
    {
        std::vector<ConstModelElementPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == "material")
                result.push_back(std::dynamic_pointer_cast<const ModelElement>(*i));
        }
        
        return result;
    }

    std::vector<ModelElementPtr> ModelRoot::modelConstellations()
    {
        std::vector<ModelElementPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == "constellation")
                result.push_back(std::dynamic_pointer_cast<ModelElement>(*i));
        }
        
        return result;
    }
    
    const std::vector<ConstModelElementPtr> ModelRoot::modelConstellations() const
    {
        std::vector<ConstModelElementPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == "constellation")
                result.push_back(std::dynamic_pointer_cast<const ModelElement>(*i));
        }
        
        return result;
    }
}
