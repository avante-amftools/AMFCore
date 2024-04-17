//
//  ModelElement.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#include "ModelElement.hpp"
#include "ModelAttribute.hpp"

#include "tinyxml2.h"

#include <assert.h>

namespace AMFCore
{
    using namespace tinyxml2;
    
    ModelNodePtr ModelAttribute::setParent(ModelElementPtr parent)
    {
        // Remove attribute from old parent.
        
        ModelElementPtr oldParent(_parent.lock());
        
        if (oldParent)
            oldParent->removeAttribute(sharedModelAttributePtr());
        
        auto result = super::setParent(parent);
        
        // Add attribute to new parent.
        
        ModelElementPtr newParent(_parent.lock());
        
        if (newParent)
        {
            newParent->addAttribute(sharedModelAttributePtr());
        }
        
        return result;
    }

    /*
    ModelNodePtr ModelAttribute::init()
    {
        ModelElementPtr parent(_parent.lock());
        
        if (parent)
        {
            parent->addAttribute(std::dynamic_pointer_cast<ModelAttribute>(shared_from_this()));
        }
        
        return shared_from_this();
    }
     */
    
    void ModelAttribute::fromXML(const XMLAttribute* xmlAttribute)
    {
        this->setValueAsString(xmlAttribute->Value());
    }
    
    void ModelAttribute::toXML(XMLElement* ownerElement) const
    {
        assert(ownerElement != nullptr);
        
        ownerElement->SetAttribute(this->identifier().c_str(), this->valueAsString().c_str());
    }
}
