//
//  ModelMesh.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#include "ModelMesh.hpp"

#include "ModelObject.hpp"
#include "ModelVolume.hpp"
#include "ModelVertices.hpp"
#include "ModelVertex.hpp"
#include "ModelTriangle.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelMesh::Identifier("mesh");
    
    ModelElementPtr ModelMesh::_newModelMesh()
    {
        return std::make_shared<ModelMesh>();
    }
    
    void ModelMesh::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelMesh);
            
            ModelVolume::initialize();
            ModelVertices::initialize();
            
            initialized = true;
        }
    }
    
    ModelMeshPtr ModelMesh::newModelMesh()
    {
        auto modelElement = ModelElement::newModelElement(ModelMesh::Identifier);
        return std::dynamic_pointer_cast<ModelMesh>(modelElement);
    }

    ModelVolumePtr ModelMesh::defaultModelVolume()
    {
        // Default is the first one added (There can be more than one).
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelVolume::Identifier)
                return std::dynamic_pointer_cast<ModelVolume>(*i);
        }
        
        // No volumes exist yet. Make one.
        
        auto result = this->newModelVolume();
        result->setParent(this->sharedModelElementPtr());
        return result;
    }

    ModelVolumePtr ModelMesh::newModelVolume()
    {
        auto modelElement = ModelElement::newModelElement(ModelVolume::Identifier);
        return std::dynamic_pointer_cast<ModelVolume>(modelElement);
    }

    std::vector<ModelVolumePtr> ModelMesh::modelVolumes()
    {
#warning Optimize this.
        
        std::vector<ModelVolumePtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelVolume::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelVolume>(*i));
        }
        
        return result;
    }
    
    const std::vector<ConstModelVolumePtr> ModelMesh::modelVolumes() const
    {
#warning Optimize this.
        
        std::vector<ConstModelVolumePtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelVolume::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelVolume>(*i));
        }
        
        return result;
    }

    ModelVerticesPtr ModelMesh::defaultModelVertices()
    {
        // There can be only one.
        
        auto result = this->modelVertices();
        
        if (result == nullptr)
        {
            result = std::dynamic_pointer_cast<ModelVertices>(ModelElement::newModelElement(ModelVertices::Identifier));
            
            result->setParent(sharedModelElementPtr());
        }
        
        return result;
    }
    
    ModelVerticesPtr ModelMesh::modelVertices()
    {
#warning optimize this.
        auto result = std::dynamic_pointer_cast<ModelVertices>(this->elementWithIdentifier(ModelVertices::Identifier));
        
        // printf("%09lX ModelMesh::modelVertices : %09lX\n", (long) this, (long) result.get());
        
        return result;
    }
    
    ConstModelVerticesPtr ModelMesh::modelVertices() const
    {
#warning optimize this.
        return std::dynamic_pointer_cast<const ModelVertices>(this->elementWithIdentifier(ModelVertices::Identifier));
    }
    
    ModelTrianglePtr ModelMesh::addTriangle(const DoubleVector3DTrio vertices,
                                            const DoubleVector3DTrio* normals,
                                            const DoubleColorTrio* colors,
                                            const DoubleColor* faceColor)
    {
        auto modelVertices = this->defaultModelVertices();
        
        // Create the vertices that the triangle will need, and insert them into
        //  our vertex array.
        
        ModelVertexPtr modelVertexTrio[3];
        
        for (int i = 0; i < 3; i++)
        {
            const DoubleVector3D vertex = vertices[i];
            const DoubleVector3D* normal = (normals == nullptr) ? nullptr : &(*normals)[i];
            const DoubleColor* color = (colors == nullptr) ? nullptr : &(*colors)[i];
            
            ModelNodePtr modelNode = ModelVertex::newModelVertex(vertex,
                                                                 normal,
                                                                 color)->setParent(modelVertices);
            
            modelVertexTrio[i] = std::static_pointer_cast<ModelVertex>(modelNode);
        }
        
        auto result = ModelTriangle::newModelTriangle();

        return result;
    }
}
