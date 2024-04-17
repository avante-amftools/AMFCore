//
//  ModelColor.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef ModelColor_hpp
#define ModelColor_hpp

#include "ModelElement.hpp"

#include "ModelColorPtr.hpp"

#include "Color.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelColor : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelColor();
        
    public:
        static NodeIdentifier Identifier;
        static NodeIdentifier OtherIdentifier;

        static void initialize();
        
        static ModelColorPtr newModelColor();
        
        static ModelColorPtr newModelColor(const DoubleColor& color);

        ModelColor() : super(Identifier)
        { }
        
        virtual void fromXML(const XMLElement* xmlElement);
        
        virtual void childrenToXML(XMLElement* thisElement) const;

        virtual void setValueAsString(const std::string& value);
        
        const DoubleColor& valueAsColor() const
        { return _color; }
        
        void setValueAsColor(const DoubleColor& color)
        { _color = color; }
        
    protected:
        DoubleColor _color;
    };
}

#endif /* ModelColor_hpp */
