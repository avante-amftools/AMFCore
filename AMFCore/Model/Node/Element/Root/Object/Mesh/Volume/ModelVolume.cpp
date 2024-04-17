//
//  ModelVolume.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#include "ModelVolume.hpp"

#include "ModelMesh.hpp"
#include "ModelTriangle.hpp"
#include "ModelVertices.hpp"
#include "ModelVertex.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelVolume::Identifier("volume");
    
    ModelElementPtr ModelVolume::_newModelVolume()
    {
        return std::make_shared<ModelVolume>();
    }
    
    void ModelVolume::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelVolume);
            
            ModelTriangle::initialize();
            
            initialized = true;
        }
    }
    
    ModelVolumePtr ModelVolume::newModelVolume()
    {
        return std::dynamic_pointer_cast<ModelVolume>(ModelElement::newModelElement(ModelVolume::Identifier));
    }
    
    ModelMeshPtr ModelVolume::parentModelMesh()
    {
        return std::dynamic_pointer_cast<ModelMesh>(this->parent());
    }
    
    ConstModelMeshPtr ModelVolume::parentModelMesh() const
    {
        return std::dynamic_pointer_cast<const ModelMesh>(this->parent());
    }
    
    ModelTrianglePtr ModelVolume::newModelTriangle()
    {
        return std::dynamic_pointer_cast<ModelTriangle>(ModelElement::newModelElement(ModelTriangle::Identifier));

    }
    
    std::vector<ModelTrianglePtr> ModelVolume::modelTriangles()
    {
#warning Optimize this.
        
        std::vector<ModelTrianglePtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelTriangle::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelTriangle>(*i));
        }
        
        return result;
    }
    
    const std::vector<ConstModelTrianglePtr> ModelVolume::modelTriangles() const
    {
#warning Optimize this.
        
        std::vector<ConstModelTrianglePtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelTriangle::Identifier)
                result.push_back(std::dynamic_pointer_cast<const ModelTriangle>(*i));
        }
        
        return result;
    }
    
    const size_t ModelVolume::triangleCount() const
    {
#warning Optimize this.
        return this->modelTriangles().size();
    }

        
    ModelTrianglePtr ModelVolume::addTriangle(const DoubleVector3DTrio coordinates,
                                              const DoubleVector3DTrio* normals,
                                              const DoubleColorTrio* colors,
                                              const DoubleColor* faceColor)
    {
        auto modelVertices = this->parentModelMesh()->defaultModelVertices();
        
        // Create the vertices that the triangle will need, and insert them into
        //  our vertex array.
        
        ModelVertexPtr modelVertexTrio[3];
        
        for (int i = 0; i < 3; i++)
        {
            const DoubleVector3D coordinate = coordinates[i];
            const DoubleVector3D* normal = (normals == nullptr) ? nullptr : &(*normals)[i];
            const DoubleColor* color = (colors == nullptr) ? nullptr : &(*colors)[i];
            
            modelVertexTrio[i] = modelVertices->addVertex(coordinate, normal, color);
        }
        
        UInt32Vector3D vertexIndices(
            modelVertexTrio[0]->index(),
            modelVertexTrio[1]->index(),
            modelVertexTrio[2]->index());

        
        auto result = ModelTriangle::newModelTriangle();
        
        result->setValueAsVector3D(vertexIndices);
        
        result->setFaceColor(faceColor);
        
        result->setParent(this->sharedModelElementPtr());
        
        return result;
    }
        
#if false
    const std::vector<DoubleVector3D>& ModelVolume::sceneVertexCoordinates() const
    {
        this->updateSceneData();

        return _sceneVertexCoordinates;
    }
    
    const std::vector<DoubleVector3D>& ModelVolume::sceneVertexNormals() const
    {
        this->updateSceneData();

        return _sceneVertexNormals;
    }
    
    const std::vector<SingleColor>& ModelVolume::sceneVertexColors() const
    {
        this->updateSceneData();

        return _sceneVertexColors;
    }

    const SceneTriangles& ModelVolume::sceneTriangles() const
    {
        this->updateSceneData();

        return _sceneTriangles;
    }
        
    void ModelVolume::buildSceneData()
    {
        _sceneVertexCoordinates.erase(_sceneVertexCoordinates.begin(), _sceneVertexCoordinates.end());
        _sceneVertexNormals.erase(_sceneVertexNormals.begin(), _sceneVertexNormals.end());
        _sceneVertexColors.erase(_sceneVertexColors.begin(), _sceneVertexColors.end());
        
        _sceneTriangles.erase(_sceneTriangles.begin(), _sceneTriangles.end());
        
        std::map<SceneVertex, uint32_t> vertexMap;
        
        auto triangles = this->modelTriangles();
        
        uint32_t nextIndex = 0;
        
        for (auto i = triangles.begin(); i != triangles.end(); i++)
        {
            for (auto axis = V0; axis <= V2; axis++)
            {
                uint32_t vertexIndex;
                
                auto vertex = (*i)->sceneVertex(axis);
                
                auto j = vertexMap.find(vertex);
                
                if (j == vertexMap.end())
                {
                    _sceneVertexCoordinates.push_back(vertex.coordinates);
                    _sceneVertexNormals.push_back(vertex.normal);
                    _sceneVertexColors.push_back(vertex.color);

                    vertexMap[vertex] = nextIndex;
                    vertexIndex = nextIndex++;
                }
                else
                {
                    vertexIndex = j->second;
                }
                
                _sceneTriangles.push_back(vertexIndex);
            }
        }

    }
#endif

    /*

    void ModelVolume::buildSceneData()
    {
        printf("%s\n", __PRETTY_FUNCTION__);
        
        _sceneVertices.erase(_sceneVertices.begin(), _sceneVertices.end());
        _sceneTriangles.erase(_sceneTriangles.begin(), _sceneTriangles.end());

        std::map<SceneVertex, uint32_t> vertexMap;
        
        auto triangles = this->modelTriangles();
        
        uint32_t nextIndex = 0;
        
        for (auto i = triangles.begin(); i != triangles.end(); i++)
        {
            for (auto axis = V0; axis <= V2; axis++)
            {
                uint32_t vertexIndex;
                
                auto vertex = (*i)->sceneVertex(axis);
                
                auto j = vertexMap.find(vertex);
                
                if (j == vertexMap.end())
                {
                    _sceneVertices.push_back(vertex);
                    vertexMap[vertex] = nextIndex;
                    vertexIndex = nextIndex++;
                }
                else
                {
                    vertexIndex = j->second;
                }
                
                _sceneTriangles.push_back(vertexIndex);
            }
        }
        
#if 0
        uint32_t index = 0;
        
        printf("_sceneVertices: %lu elements, %lu bytesPerElement, %ld bytes\n", _sceneVertices.size(), sizeof(SceneVertex), sceneVertices().size() * sizeof(SceneVertex));
        
        for (auto i = _sceneVertices.begin(); i != _sceneVertices.end(); i++)
        {
            i->debugShow(index++);
        }
        
        index = 0;
        
        printf("_sceneTriangles: %lu elements, %lu bytesPerElement, %ld bytes\n", _sceneTriangles.size(), sizeof(uint32_t), _sceneTriangles.size() * sizeof(uint32_t));
        
        for (auto i = _sceneTriangles.begin(); i != _sceneTriangles.end(); i++)
        {
            printf("%d %d\n", index++, *i);
        }
#endif
    }
     
     */
}
