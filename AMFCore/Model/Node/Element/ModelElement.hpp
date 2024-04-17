//
//  ModelElement.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef ModelElement_hpp
#define ModelElement_hpp

#include <map>
#include <set>
#include <vector>

#include "ModelNode.hpp"

#include "ModelElementPtr.hpp"
#include "ModelAttributePtr.hpp"
#include "ModelMetadataPtr.hpp"

namespace tinyxml2
{
    class XMLElement;
};

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelElement : public ModelNode
    {
        friend class ModelAttribute;
        
    private:
        typedef ModelNode super;
        
    protected:
        typedef ModelElementPtr (*NewModelElementFunction)();
        
        typedef ModelAttributePtr (*NewModelAttributeFunction)();

    public:
        static ModelElementPtr newModelElement(const NodeIdentifier& identifier);

        static ModelAttributePtr newModelAttribute(const NodeIdentifier& identifier);

        ModelElement(const NodeIdentifier& identifier) : super(identifier)
        { }

        virtual ModelNodePtr setParent(ModelElementPtr parent);

        /*
        virtual ModelNodePtr init();
        */
        
        virtual void fromXML(const XMLElement* xmlElement);
        
        virtual void toXML(XMLElement* ownerElement) const;
        
        virtual void childrenToXML(XMLElement* thisElement) const;
        
        ModelElementPtr sharedModelElementPtr()
        { return std::dynamic_pointer_cast<ModelElement>(shared_from_this()); }
        
        // Attributes
        
        std::vector<ModelAttributePtr>& attributes()
        { return _attributes; }

        virtual ModelAttributePtr addAttribute(ModelAttributePtr modelAttribute);
        
        // Remove an attribute node from this node.
        
        virtual void removeAttribute(ModelAttributePtr modelAttribute);
        
        virtual void removeAttributes(const std::set<ModelAttributePtr>& toRemove);

        virtual void removeAttributes(const std::vector<ModelAttributePtr>& toRemove);
        
        ModelAttributePtr attributeWithIdentifier(const NodeIdentifier& identifier);
        
        ConstModelAttributePtr attributeWithIdentifier(const NodeIdentifier& identifier) const;

        // Elements
        
        std::vector<ModelElementPtr>& elements()
        { return _elements; }

        virtual ModelElementPtr addElement(ModelElementPtr modelElement);

        virtual void removeElement(ModelElementPtr modelElement);
        
        virtual void removeElements(const std::set<ModelElementPtr>& toRemove);
        
        virtual void removeElements(const std::vector<ModelElementPtr>& toRemove);

        ModelElementPtr elementWithIdentifier(const NodeIdentifier& identifier);
        
        ConstModelElementPtr elementWithIdentifier(const NodeIdentifier& identifier) const;
        
        // Find all elements with the specified identifier.
        
        std::vector<ModelElementPtr> elementsWithIdentifier(const NodeIdentifier& identifier);
        
        const std::vector<ConstModelElementPtr> elementsWithIdentifier(const NodeIdentifier& identifier) const;
        
        // Detail nodes (Attributes, Color, Metadata)
        
        std::vector<ModelNodePtr> modelDetails();
        
        const std::vector<ConstModelNodePtr> modelDetails() const;
        
        std::vector<ModelMetadataPtr> modelMetadatas();
        
        const std::vector<ConstModelMetadataPtr> modelMetadatas() const;

        ModelMetadataPtr metadataWithType(const std::string& type);
        
        ConstModelMetadataPtr metadataWithType(const std::string& type) const;

        virtual void debugShow(std::string indent = "");

    protected:
        std::vector<ModelElementPtr> _elements;
        std::vector<ModelAttributePtr> _attributes;

        static std::map<const NodeIdentifier, NewModelElementFunction> __newModelElementFunctions;

        static std::map<const NodeIdentifier, NewModelAttributeFunction> __newModelAttributeFunctions;
    };
}

#endif /* ModelElement_hpp */
