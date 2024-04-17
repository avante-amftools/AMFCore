//
//  ModelNode.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef ModelNode_hpp
#define ModelNode_hpp

#include <bitset>

#include "AMFCore.hpp"

#include "ModelNodePtr.hpp"

#include "ModelElementPtr.hpp"

namespace AMFCore
{
    typedef std::string NodeIdentifier;
        
    class ModelNode : public std::enable_shared_from_this<ModelNode>
    {        
    public:
        static void initialize();
        
        ModelNode(const NodeIdentifier& identifier);
        
        // virtual ModelNodePtr init() = 0;
        
        virtual ~ModelNode()
        { }
                        
        const NodeIdentifier& identifier() const
        { return _identifier; }
        
        virtual const std::string& valueAsString() const
        { return _value; }
        
        virtual void setValueAsString(const std::string& value)
        { _value = value; }
        
        int32_t valueAsInt32() const
        { return (this->valueAsString().size() == 0) ? 0 : std::stoi(this->valueAsString()); }
        
        void setValueAsInt32(int32_t value)
        { this->setValueAsString(std::to_string(value)); }
        
        double valueAsDouble() const
        { return (this->valueAsString().size() == 0) ? 0. : std::stod(this->valueAsString()); }
        
        void setValueAsDouble(double value)
        { this->setValueAsString(std::to_string(value)); }

        std::bitset<32>& flags()
        { return _flags; }
        
        /// Access the node's flags from a const context.  The reference returned is *not* const. Modifying flags will not alter the behavior of the AMFCore library, so it is allowed to modify them from a const context.
        
        std::bitset<32>& flags() const
        { return const_cast<ModelNode*>(this)->_flags; }
        
        /// Set the node's parent node.  After a node is created, and its values are set, setParent must be called in order to place the node in the model hierarchy.
        /// setParent is allowed to substitute an identical node for the one that was created.  The returned value should replace the called object.
        /// Note: Because vertex nodes are shared, and organized in a set, they should be considered "const" once their parent has been set.
        
        virtual ModelNodePtr setParent(ModelElementPtr parent);
        
        ModelElementPtr parent();
        
        ConstModelElementPtr parent() const;
        
        virtual void debugShow(std::string indent = "");

        // Protected/Private interface

    protected:
        const NodeIdentifier _identifier;
        std::weak_ptr<ModelElement> _parent;
        
        std::string _value;
        std::bitset<32> _flags;
        
    private:
        ModelNode();    // No default constructor.
    };
}

#endif /* ModelNode_hpp */
