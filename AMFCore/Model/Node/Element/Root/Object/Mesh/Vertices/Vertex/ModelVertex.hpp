//
//  ModelVertex.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#ifndef ModelVertex_hpp
#define ModelVertex_hpp

#include "ModelElement.hpp"

#include "ModelVertexPtr.hpp"

#include "ModelVerticesPtr.hpp"
#include "ModelMeshPtr.hpp"
#include "ModelCoordinatePtr.hpp"
#include "ModelNormalPtr.hpp"
#include "ModelColorPtr.hpp"

#include "Vector3D.hpp"
#include "Color.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelVertex : public ModelElement
    {
        // <vertex>
        //      <coordinates>
        //          <x>     double
        //          <y>     double
        //          <z>     double
        //      <normal>
        //          <nx>    double
        //          <ny>    double
        //          <nz>    double
        //      <color>     ModelColor
        //
        
        friend class ModelVertices; // So ModelVertices can set index.
        

        // When comparing ModelVertex objects, we need to compare coordinates, normals and color.
        //  We must not compare indices, as those are used to share ModelVertex objects.
        
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelVertex();
        
    public:
        static NodeIdentifier Identifier;

        static const NodeIdentifier CoordinatesIdentifier;
        static const NodeIdentifier NormalIdentifier;

        static void initialize();
        
        static ModelVertexPtr newModelVertex();
        
        static ModelVertexPtr newModelVertex(const DoubleVector3D coordinate,
                                             const DoubleVector3D* normal,
                                             const DoubleColor* color);


        ModelVertex() : super(Identifier)
        { }
        
        virtual void fromXML(const XMLElement* xmlElement);
                
        ModelCoordinatePtr modelCoordinate();
        
        ConstModelCoordinatePtr modelCoordinate() const;
        
        ModelNormalPtr modelNormal();
        
        ConstModelNormalPtr modelNormal() const;
                
        ModelColorPtr modelColor();
        
        ConstModelColorPtr modelColor() const;
        
        // Coordinates are required.
        
        const DoubleVector3D& coordinate() const;
        
        void setCoordinate(const DoubleVector3D& coordinate);
        
        // Normals are optional.
                        
        const DoubleVector3D* normal() const;
        
        // Color is optional.
        
        const DoubleColor* color() const;
        
        // The vertex's index within ModelVertices.
        
        const uint32_t index() const
        { return _index; }
        
    protected:
        void setIndex(const uint32_t index)
        { _index = index; }
        
        uint32_t _index;
    };
}

#endif /* ModelVertex_hpp */
