//
//  ModelMesh.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelMesh_hpp
#define ModelMesh_hpp

#include "ModelElement.hpp"

#include "ModelMeshPtr.hpp"
#include "ModelObjectPtr.hpp"
#include "ModelVolumePtr.hpp"
#include "ModelVerticesPtr.hpp"
#include "ModelVertexPtr.hpp"
#include "ModelTrianglePtr.hpp"

#include "Vector3D.hpp"
#include "Color.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    class ModelMesh : public ModelElement
    {
    private:
        typedef ModelElement super;
        
        static ModelElementPtr _newModelMesh();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        static ModelMeshPtr newModelMesh();

        ModelMesh() : super(Identifier)
        { }
        
        ModelVolumePtr defaultModelVolume();
        
        ModelVolumePtr newModelVolume();
        
        std::vector<ModelVolumePtr> modelVolumes();
 
        const std::vector<ConstModelVolumePtr> modelVolumes() const;
        
        ModelVerticesPtr defaultModelVertices();
        
        ModelVerticesPtr modelVertices();
        
        ConstModelVerticesPtr modelVertices() const;
                
        ModelTrianglePtr addTriangle(const DoubleVector3DTrio vertices,
                                     const DoubleVector3DTrio* normals,
                                     const DoubleColorTrio* colors,
                                     const DoubleColor* faceColor);
    };
}

#endif /* ModelMesh_hpp */
