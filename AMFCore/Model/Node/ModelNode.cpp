//
//  ModelNode.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#include "ModelNode.hpp"

#include "ModelElement.hpp"

namespace AMFCore
{
    void ModelNode::initialize()
    {
    }

    ModelNode::ModelNode(const NodeIdentifier& identifier) :
    _identifier(identifier),
    _parent()
    {
    }
    
    ModelNodePtr ModelNode::setParent(ModelElementPtr parent)
    {
        _parent = parent;
        return shared_from_this();
    }
    
    ModelElementPtr ModelNode::parent()
    {
        return ModelElementPtr(_parent);
    }
    
    ConstModelElementPtr ModelNode::parent() const
    {
        return ConstModelElementPtr(_parent);
    }
    
    void ModelNode::debugShow(std::string indent)
    {
        const char* identifier = this->identifier().c_str();
        
        printf("%s%s %s\n", indent.c_str(), identifier, this->valueAsString().c_str());
    }

}
