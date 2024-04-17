//
//  ModelVertices.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/5/23.
//

#include "ModelVertices.hpp"

#include "ModelMesh.hpp"

#include "ModelVertex.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelVertices::Identifier("vertices");
    
    ModelElementPtr ModelVertices::_newModelVertices()
    {
        return std::make_shared<ModelVertices>();
    }
    
    void ModelVertices::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelVertices);

            ModelVertex::initialize();
            
            initialized = true;
        }
    }
    
    ModelVerticesPtr ModelVertices::newModelVertices()
    {
        return std::dynamic_pointer_cast<ModelVertices>(ModelElement::newModelElement(ModelVertices::Identifier));
    }


    ModelElementPtr ModelVertices::addElement(ModelElementPtr modelElement)
    {
        // Vertices are defined to be unique.  If we already have a vertex stored that's
        //  identical to the one being added, then use it.
        
        ModelVertexPtr modelVertex = std::dynamic_pointer_cast<ModelVertex>(modelElement);
        
        if (modelVertex != nullptr)
        {
            if (_modelVertexes.find(modelVertex) == _modelVertexes.end())
            {
                modelVertex->setIndex((uint32_t) _modelVertexes.size());
                _modelVertexes.insert(modelVertex);
            }
            else
            {
                modelElement = modelVertex;
            }
        }
        
        return super::addElement(modelElement);
    }

    void ModelVertices::removeElement(ModelElementPtr modelElement)
    {
#warning Implement this.
        // When we're removing the last reference to a vertex, we also need to remove
        //  it from the vertex set.
        
        super::removeElement(modelElement);
    }
    
    ModelVertexPtr ModelVertices::addVertex(const DoubleVector3D coordinate,
                                            const DoubleVector3D* normal,
                                            const DoubleColor* color)
    {
        auto modelVertex = ModelVertex::newModelVertex(coordinate, normal, color);
        modelVertex = static_pointer_cast<ModelVertex>(modelVertex->setParent(this->sharedModelElementPtr()));
        
        return modelVertex;
    }


    void ModelVertices::fromXML(const XMLElement* xmlElement)
    {
        super::fromXML(xmlElement);
                
        // printf("%s %lu <vertex>\n", __PRETTY_FUNCTION__, this->modelVertexes().size());

        // this->debugShow();
    }
    
    std::vector<ModelVertexPtr> ModelVertices::modelVertexes()
    {
#warning Optimize this.
        std::vector<ModelVertexPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelVertex::Identifier)
                result.push_back(std::dynamic_pointer_cast<ModelVertex>(*i));
        }
        
        return result;
    }
    
    const std::vector<ConstModelVertexPtr> ModelVertices::modelVertexes() const
    {
#warning Optimize this.

        std::vector<ConstModelVertexPtr> result;
        
        for (auto i = _elements.begin(); i != _elements.end(); i++)
        {
            if ((*i)->identifier() == ModelVertex::Identifier)
                result.push_back(std::dynamic_pointer_cast<const ModelVertex>(*i));
        }
        
        return result;
    }
}
