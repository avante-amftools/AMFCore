//
//  ModelAttribute.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef ModelAttribute_hpp
#define ModelAttribute_hpp

#include <map>

#include "ModelNode.hpp"

#include "ModelAttributePtr.hpp"

#include "ModelElement.hpp"
#include "ModelElementPtr.hpp"

namespace tinyxml2
{
    class XMLNode;
    class XMLAttribute;
    class XMLElement;
};

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelAttribute : public ModelNode
    {
    private:
        typedef ModelNode super;
        
    protected:
        ModelAttributePtr sharedModelAttributePtr()
        { return std::dynamic_pointer_cast<ModelAttribute>(shared_from_this()); }

    public:
        ModelAttribute(const NodeIdentifier& identifier) : super(identifier)
        { }
        
        virtual ModelNodePtr setParent(ModelElementPtr parent);

        // virtual ModelNodePtr init();
        
        virtual void fromXML(const XMLAttribute* xmlAttribute);
        
        virtual void toXML(XMLElement* ownerElement) const;
        
    protected:
        static std::map<const NodeIdentifier, ModelElement::NewModelAttributeFunction>& newModelAttributeFunctions()
        { return ModelElement::__newModelAttributeFunctions; }
    };
}

#endif /* ModelAttribute_hpp */
