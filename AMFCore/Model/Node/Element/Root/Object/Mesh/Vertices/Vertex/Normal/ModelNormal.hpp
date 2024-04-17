//
//  ModelNormal.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/8/23.
//

#ifndef ModelNormal_hpp
#define ModelNormal_hpp

#include "ModelElement.hpp"

#include "ModelNormalPtr.hpp"

#include "Vector3D.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelNormal : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelNormal();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        static ModelNormalPtr newModelNormal();
        
        static ModelNormalPtr newModelNormal(const DoubleVector3D& normal);
        
        ModelNormal() : super(Identifier)
        { }
        
        virtual void fromXML(const XMLElement* xmlElement);
        
        const DoubleVector3D& valueAsVector3D() const
        { return _valueAsVector3D; }
        
        void setValueAsVector3D(const DoubleVector3D& value)
        { _valueAsVector3D = value; }
        
        virtual void debugShow(std::string indent = "");

    protected:
        DoubleVector3D _valueAsVector3D;
    };
}

#endif /* ModelNormal_hpp */
