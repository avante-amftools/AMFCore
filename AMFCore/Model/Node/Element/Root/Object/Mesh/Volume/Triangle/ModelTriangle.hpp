//
//  ModelTriangle.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/4/23.
//

#ifndef ModelTriangle_hpp
#define ModelTriangle_hpp

#include "ModelElement.hpp"

#include "ModelTrianglePtr.hpp"

#include "ModelVolumePtr.hpp"
#include "ModelVertexPtr.hpp"
#include "ModelMeshPtr.hpp"

#include "Vector3D.hpp"
#include "SceneVertex.hpp"

#include "ModelColorPtr.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelTriangle : public ModelElement
    {
        //  <triangle>
        //      <v1>        integer
        //      <v2>        integer
        //      <v3>        integer
        //      <color>     ModelColor
        //      <texmap>    ModelTexmap

    private:
        typedef ModelElement super;
                        
        static ModelElementPtr _newModelTriangle();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        static ModelTrianglePtr newModelTriangle();
        
        ModelTriangle() : super(Identifier)
        { }
        
        virtual void fromXML(const XMLElement* xmlElement);
        
        virtual void childrenToXML(XMLElement* thisElement) const;

        const UInt32Vector3D& valueAsVector3D() const
        { return _vertexIndices; }
        
        void setValueAsVector3D(UInt32Vector3D value);
        
        // Convenience accessor for a list of vertexes used by this triangle.
        //  Triangles do not own ModelVertex objects.  Those are owned by
        //  ModelMesh.
        
        std::vector<ConstModelVertexPtr> modelVertexes() const;
        
        ModelColorPtr color();
        
        ConstModelColorPtr color() const;
        
        const DoubleColor* faceColor() const;
        
        void setFaceColor(const DoubleColor* faceColor);
                
        const DoubleColor* vertexColor(Axis cornerIndex) const;
        
        const DoubleColor* volumeColor() const;
        
        const DoubleColor* objectColor() const;
        
        const DoubleColor* materialColor() const;
        
        const DoubleColor* defaultColor() const;

        const SceneVertex sceneVertex(Axis cornerIndex) const;
        
        // Compute a face normal to use if vertex normals
        //  are not provided.
        
        const DoubleVector3D faceNormal() const;
        
        virtual void debugShow(std::string indent = "");

    protected:

        ModelVolumePtr parentModelVolume();

        ConstModelVolumePtr parentModelVolume() const;

        ModelMeshPtr parentModelMesh();
        
        ConstModelMeshPtr parentModelMesh() const;

        static DoubleColor __defaultColor;
        
        UInt32Vector3D _vertexIndices;
    };
}

#endif /* ModelTriangle_hpp */
