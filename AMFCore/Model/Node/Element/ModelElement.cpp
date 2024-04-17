//
//  ModelElement.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#include "ModelElement.hpp"

#include "ModelAttribute.hpp"
#include "ModelColor.hpp"
#include "ModelMetadata.hpp"

#include "remove.hpp"
#include "tinyxml2.h"

#include <assert.h>

namespace AMFCore
{
    using namespace tinyxml2;
    
    ModelElementPtr ModelElement::newModelElement(const NodeIdentifier& identifier)
    {
        auto i = __newModelElementFunctions.find(identifier);
        
        auto modelElement = (i != __newModelElementFunctions.end() ?
                             i->second() :
                             std::make_shared<ModelElement>(identifier));
        
        return modelElement;
    }
    
    ModelAttributePtr ModelElement::newModelAttribute(const NodeIdentifier& identifier)
    {
        auto i = __newModelAttributeFunctions.find(identifier);
        
        auto modelAttribute = (i != __newModelAttributeFunctions.end() ?
                               i->second() :
                               std::make_shared<ModelAttribute>(identifier));
        
        return modelAttribute;
    }

    ModelNodePtr ModelElement::setParent(ModelElementPtr parent)
    {
        // Remove attribute from old parent.
        
        ModelElementPtr oldParent(_parent.lock());
        
        if (oldParent)
            oldParent->removeElement(sharedModelElementPtr());
        
        auto result = super::setParent(parent);
        
        // Add attribute to new parent.
        
        ModelElementPtr newParent(_parent.lock());
        
        if (newParent)
        {
            newParent->addElement(sharedModelElementPtr());
        }
        
        return result;
    }

    /*
    ModelNodePtr ModelElement::init()
    {
        ModelElementPtr parent(_parent.lock());
                
        if (parent)
        {
            return parent->addElement(std::dynamic_pointer_cast<ModelElement>(shared_from_this()));
        }
        
        return shared_from_this();
    }
     */
    
    void ModelElement::fromXML(const XMLElement* xmlElement)
    {
        auto sharedThis = this->sharedModelElementPtr();
        
        auto xmlAttribute = xmlElement->FirstAttribute();
        
        while (xmlAttribute != nullptr)
        {
            ModelAttributePtr modelAttribute = ModelElement::newModelAttribute(xmlAttribute->Name());
            
            modelAttribute->fromXML(xmlAttribute);
            
            modelAttribute->setParent(sharedThis);
            
            xmlAttribute = xmlAttribute->Next();
        }
        
        auto childXMLElement = xmlElement->FirstChildElement();

        while (childXMLElement != nullptr)
        {
            ModelElementPtr modelElement = ModelElement::newModelElement(childXMLElement->Name());  // Color created here.
            
            modelElement->fromXML(childXMLElement);
            
            modelElement->setParent(sharedThis);
            
            childXMLElement = childXMLElement->NextSiblingElement();
        }
        
        // Read this element's value.
        
        auto value = xmlElement->GetText();
        
        this->setValueAsString(value ? value : "");
    }
    
    void ModelElement::toXML(XMLElement* ownerElement) const
    {
        XMLElement* thisElement = ownerElement->InsertEndChild(ownerElement->GetDocument()->NewElement(this->identifier().c_str()))->ToElement();
        
        const std::string& value(this->valueAsString());

        if (value != "")
        {
            thisElement->SetText(value.c_str());
        }

        this->childrenToXML(thisElement);
    }
    
    void ModelElement::childrenToXML(XMLElement* thisElement) const
    {
        for (auto i = _attributes.begin(); i != _attributes.end(); i++)
        {
            (*i)->toXML(thisElement);
        }
        
        for  (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            (*i)->toXML(thisElement);
        }
    }


        
    ModelAttributePtr ModelElement::addAttribute(ModelAttributePtr modelAttribute)
    {
        _attributes.push_back(modelAttribute);
        
        return modelAttribute;
    }
    
    // Remove an attribute node from this node.
    
    void ModelElement::removeAttribute(ModelAttributePtr modelAttribute)
    {
        _attributes.erase(std::remove(_attributes.begin(), _attributes.end(), modelAttribute), _attributes.end());
    }
    
    void ModelElement::removeAttributes(const std::set<ModelAttributePtr>& toRemove)
    {
        // Optimized removal of attributes from an element.
        
        // Uses the "erase-remove" idiom to remove attributes.
        
        AMFCore::erase(_attributes, toRemove);
    }
    
    void ModelElement::removeAttributes(const std::vector<ModelAttributePtr>& toRemove)
    {
        std::set<ModelAttributePtr> setToRemove;
        
        for (auto i = toRemove.begin(); i != toRemove.end(); i++)
            setToRemove.insert(*i);
        
        this->removeAttributes(setToRemove);
    }
    
    ModelAttributePtr ModelElement::attributeWithIdentifier(const NodeIdentifier& identifier)
    {
        for (auto i = _attributes.begin(); i != _attributes.end(); i++)
            if ((*i)->identifier() == identifier)
                return (*i);
        
        return NULL;
    }
    
    ConstModelAttributePtr ModelElement::attributeWithIdentifier(const NodeIdentifier& identifier) const
    {
        for (auto i = _attributes.begin(); i != _attributes.end(); i++)
            if ((*i)->identifier() == identifier)
                return (*i);
        
        return NULL;
    }
    
    ModelElementPtr ModelElement::addElement(ModelElementPtr modelElement)
    {
        _elements.push_back(modelElement);
        
        return modelElement;
    }
    
    // Remove an element node from this node.
    
    void ModelElement::removeElement(ModelElementPtr modelElement)
    {
        _elements.erase(std::remove(_elements.begin(), _elements.end(), modelElement), _elements.end());
    }
    
    void ModelElement::removeElements(const std::set<ModelElementPtr>& toRemove)
    {
        // Optimized removal of children from a node.
        
        // Uses the "erase-remove" idiom to remove children.
        //
        // Notifies each child that was removed that it has been "orphaned" in
        //  order to prevent attempts to remove the child from its parent a second
        //  time.
        
        AMFCore::erase(_elements, toRemove);
    }
    
    void ModelElement::removeElements(const std::vector<ModelElementPtr>& toRemove)
    {
        std::set<ModelElementPtr> setToRemove;
        
        for (auto i = toRemove.begin(); i != toRemove.end(); i++)
            setToRemove.insert(*i);
        
        this->removeElements(setToRemove);
    }
    
    ModelElementPtr ModelElement::elementWithIdentifier(const NodeIdentifier& identifier)
    {
        std::vector<ModelElementPtr> elementsWithIdentifier = this->elementsWithIdentifier(identifier);
        
        // The element cannot be plural.
        
        assert(elementsWithIdentifier.size() < 2);

        // The element is allowed to be missing.
        
        if (elementsWithIdentifier.size() == 1)
            return elementsWithIdentifier.back();

        return nullptr;
    }
    
    ConstModelElementPtr ModelElement::elementWithIdentifier(const NodeIdentifier& identifier) const
    {
        std::vector<ConstModelElementPtr> elementsWithIdentifier = this->elementsWithIdentifier(identifier);
        
        // The element cannot be plural.
        
        assert(elementsWithIdentifier.size() < 2);
        
        // The element is allowed to be missing.
        
        if (elementsWithIdentifier.size() == 1)
            return elementsWithIdentifier.back();
        
        return nullptr;
    }
        
    std::vector<ModelElementPtr> ModelElement::elementsWithIdentifier(const NodeIdentifier& identifier)
    {
        std::vector<ModelElementPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == identifier)
                result.push_back(*i);
        }
        
        return result;
    }
    
    const std::vector<ConstModelElementPtr> ModelElement::elementsWithIdentifier(const NodeIdentifier& identifier) const
    {
        std::vector<ConstModelElementPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == identifier)
                result.push_back(*i);
        }
        
        return result;
    }
    
    std::vector<ModelNodePtr> ModelElement::modelDetails()
    {
        std::vector<ModelNodePtr> result;
        
        // Attributes
        
        for (auto i = _attributes.begin(); i != _attributes.end(); i++)
        {
            result.push_back(*i);
        }
        
        // Color elements
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if (std::dynamic_pointer_cast<ModelColor>(*i))
                result.push_back(*i);
        }
        
        // Metadata elements

        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if (std::dynamic_pointer_cast<ModelMetadata>(*i))
            {
                result.push_back(*i);
                (*i)->debugShow();
            }

        }
        
        return result;
    }
    
    const std::vector<ConstModelNodePtr> ModelElement::modelDetails() const
    {
        std::vector<ConstModelNodePtr> result;
        
        // Attributes
        
        for (auto i = _attributes.begin(); i != _attributes.end(); i++)
        {
            result.push_back(*i);
        }
        
        // Color elements
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelColor::Identifier)
                result.push_back(*i);
        }
        
        // Metadata elements
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelMetadata::Identifier)
                result.push_back(*i);
        }
        
        return result;
    }

    
    std::vector<ModelMetadataPtr> ModelElement::modelMetadatas()
    {
        std::vector<ModelMetadataPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelMetadata::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelMetadata>(*i));
        }
        
        return result;
    }
    
    const std::vector<ConstModelMetadataPtr> ModelElement::modelMetadatas() const
    {
        std::vector<ConstModelMetadataPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelMetadata::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelMetadata>(*i));
        }
        
        return result;
    }
    
    ModelMetadataPtr ModelElement::metadataWithType(const std::string& type)
    {
        auto modelMetadatas = this->modelMetadatas();
        
        for (auto i = modelMetadatas.begin(); i != modelMetadatas.end(); i++)
        {
            if ((*i)->type() == type)
                return *i;
        }
        
        return nullptr;
    }
    
    ConstModelMetadataPtr ModelElement::metadataWithType(const std::string& type) const
    {
        auto modelMetadatas = this->modelMetadatas();

        for (auto i = modelMetadatas.begin(); i != modelMetadatas.end(); i++)
        {
            if ((*i)->type() == type)
                return *i;
        }
        
        return nullptr;
    }


    void ModelElement::debugShow(std::string indent)
    {
#if 1
        super::debugShow(indent);
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            (*i)->debugShow(indent + "  ");
        }
#endif
    }

    std::map<const NodeIdentifier, ModelElement::NewModelElementFunction> ModelElement::__newModelElementFunctions;
    
    std::map<const NodeIdentifier, ModelElement::NewModelAttributeFunction> ModelElement::__newModelAttributeFunctions;
}
