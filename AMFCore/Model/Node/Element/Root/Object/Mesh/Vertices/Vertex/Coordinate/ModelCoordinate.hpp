//
//  ModelCoordinate.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef ModelCoordinate_hpp
#define ModelCoordinate_hpp

#include "ModelElement.hpp"

#include "ModelCoordinatePtr.hpp"
#include "ModelVertexPtr.hpp"

#include "Vector3D.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelCoordinate : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelCoordinate();
                
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        static ModelCoordinatePtr newModelCoordinate();
        
        static ModelCoordinatePtr newModelCoordinate(const DoubleVector3D& coordinate);
                
        ModelCoordinate() : super(Identifier)
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

#endif /* ModelCoordinate_hpp */
