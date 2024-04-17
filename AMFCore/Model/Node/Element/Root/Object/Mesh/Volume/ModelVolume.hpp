//
//  ModelVolume.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef ModelVolume_hpp
#define ModelVolume_hpp

#include "ModelElement.hpp"

#include "ModelVolumePtr.hpp"
#include "ModelMeshPtr.hpp"
#include "ModelMesh.hpp"
#include "ModelTrianglePtr.hpp"
#include "ModelVertexPtr.hpp"

#include "SceneVertex.hpp"

#include <assert.h>

namespace AMFCore
{
    using namespace tinyxml2;
        
    class SceneTriangles : public std::vector<uint32_t>
    {
    private:
        typedef std::vector<uint32_t> super;

    public:
        SceneTriangles() : super() { }

        SceneTriangles(const SceneTriangles& other) : super(other)
        {
            assert(!"SceneTriangles copy constructor should not be called. Avoid using auto when declaring SceneTriangles& (reference) variables.");
        }
    };
    
    class ModelVolume : public ModelElement
    {
    private:
        typedef ModelElement super;
                
        static ModelElementPtr _newModelVolume();
        
    public:
        static NodeIdentifier Identifier;

        static void initialize();
        
        static ModelVolumePtr newModelVolume();
        
        ModelVolume() : super(Identifier)
        {
            // printf("%s\n", __PRETTY_FUNCTION__);
        }
        
        virtual ~ModelVolume()
        {
            // printf("%s\n", __PRETTY_FUNCTION__);
        }
        
        ModelVolumePtr sharedModelVolumePtr()
        { return std::static_pointer_cast<ModelVolume>(shared_from_this()); }
        
        ModelMeshPtr parentModelMesh();
        
        ConstModelMeshPtr parentModelMesh() const;
        
        ModelTrianglePtr newModelTriangle();

        std::vector<ModelTrianglePtr> modelTriangles();
        
        const std::vector<ConstModelTrianglePtr> modelTriangles() const;
        
        const size_t triangleCount() const;
                
        ModelTrianglePtr addTriangle(const DoubleVector3DTrio vertices,
                                     const DoubleVector3DTrio* normals,
                                     const DoubleColorTrio* colors,
                                     const DoubleColor* faceColor);

#if false        
        const std::vector<DoubleVector3D>& sceneVertexCoordinates() const;
        
        const std::vector<DoubleVector3D>& sceneVertexNormals() const;
        
        const std::vector<SingleColor>& sceneVertexColors() const;
        
        const SceneTriangles& sceneTriangles() const;
        
    protected:
        
        const void updateSceneData() const
        {
            if (_sceneVertexCoordinates.size() == 0)
                this->buildSceneData();
        }
        
        const void buildSceneData() const
        {
            // Scene data accessors are cached, so we need to un-const the operation.
            
            const_cast<ModelVolume*>(this)->buildSceneData();
        }

        void buildSceneData();
        
        //  Discrete vertex data for 3D rendering.
        
        std::vector<DoubleVector3D> _sceneVertexCoordinates;
        std::vector<DoubleVector3D> _sceneVertexNormals;
        std::vector<SingleColor> _sceneVertexColors;

        //  Vertex indices for 3D rendering.
        SceneTriangles _sceneTriangles;
        
#endif
        
    };
}

#endif /* ModelVolume_hpp */
