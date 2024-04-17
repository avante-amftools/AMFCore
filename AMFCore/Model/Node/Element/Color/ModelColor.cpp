//
//  ModelColor.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#include "ModelColor.hpp"

#include "tinyxml2.h"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelColor::Identifier("color");
    NodeIdentifier ModelColor::OtherIdentifier("colour");
    
    ModelElementPtr ModelColor::_newModelColor()
    {
        return std::make_shared<ModelColor>();
    }
    
    void ModelColor::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelColor);
            __newModelElementFunctions.emplace(OtherIdentifier, _newModelColor);

            initialized = true;
        }
    }
    
    ModelColorPtr ModelColor::newModelColor()
    {
         return std::dynamic_pointer_cast<ModelColor>(ModelElement::newModelElement(ModelColor::Identifier));
    }
    
    ModelColorPtr ModelColor::newModelColor(const DoubleColor& color)
    {
         auto result = ModelColor::newModelColor();
         result->setValueAsColor(color);
         return result;
    }

        
    void ModelColor::fromXML(const XMLElement* xmlElement)
    {
        super::fromXML(xmlElement);
        
        static const NodeIdentifier colorLabels[4] = { "r", "g", "b", "a" };
        
        // Move the r, g, b and a values to _color.

        for (auto i = R; i <= A; i++)
        {
            auto element = this->elementWithIdentifier(colorLabels[i]);
            
            if (element == nullptr)
            {
                // We don't consider missing alpha to be an error.
                
                if (i < 3)
                    throw(std::runtime_error("<color> could not locate required <" + colorLabels[i] + "> element"));
                else
                    _color[i] = 1.;
            }
            else
            {
                _color[i] = element->valueAsDouble();
                
                // Remove r, g, b and a elements from the model, we don't need them anymore.
                
                element->setParent(nullptr);
            }
        }
    }
    
    void ModelColor::childrenToXML(XMLElement* thisElement) const
    {
        for (auto i = R; i <= A; i++)
        {
            static const char* __labels[Channels] = { "r", "g", "b", "a" };
            
            auto channelValue = _color[i];
            
            XMLElement* channelElement = thisElement->InsertEndChild(thisElement->GetDocument()->NewElement(__labels[i]))->ToElement();
            
            channelElement->SetText(std::to_string(channelValue).c_str());
        }
        
        super::childrenToXML(thisElement);
    }

    
    void ModelColor::setValueAsString(const std::string& value)
    {
        if (value != "")
            throw(std::runtime_error(std::string(__PRETTY_FUNCTION__) + " called."));
    }
}
