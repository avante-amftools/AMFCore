//
//  ModelVertex.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/3/23.
//

#include "ModelVertex.hpp"

#include "tinyxml2.h"

#include "ModelVertices.hpp"
#include "ModelCoordinate.hpp"
#include "ModelNormal.hpp"
#include "ModelColor.hpp"
#include "ModelMesh.hpp"

#include <assert.h>

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelVertex::Identifier("vertex");
    
    const NodeIdentifier ModelVertex::CoordinatesIdentifier("coordinates");
    const NodeIdentifier ModelVertex::NormalIdentifier("normal");

    ModelElementPtr ModelVertex::_newModelVertex()
    {
        auto foo = new ModelVertex();
        
        return std::make_shared<ModelVertex>();
    }
    
    void ModelVertex::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelVertex);
            
            ModelCoordinate::initialize();
            ModelNormal::initialize();
            ModelColor::initialize();

            initialized = true;
        }
    }
    
    ModelVertexPtr ModelVertex::newModelVertex()
    {
        return std::dynamic_pointer_cast<ModelVertex>(ModelElement::newModelElement(ModelVertex::Identifier));
    }
    
    ModelVertexPtr ModelVertex::newModelVertex(const DoubleVector3D coordinate,
                                               const DoubleVector3D* normal,
                                               const DoubleColor* color)
    {
        auto result = ModelVertex::newModelVertex();
        
        auto modelCoordinate = ModelCoordinate::newModelCoordinate(coordinate);
        modelCoordinate->setParent(result);
        
        if (normal)
        {
            auto modelNormal = ModelNormal::newModelNormal(*normal);
            modelNormal->setParent(result);
        }
        
        if (color)
        {
            auto modelColor = ModelColor::newModelColor(*color);
            modelColor->setParent(result);
        }
        
        return result;
    }
        
    void ModelVertex::fromXML(const XMLElement* xmlElement)
    {
#warning Optimize this.
        
        // To Do: Cache pointers for <coordinates>, <normal> and <color>
        
        // <vertex>
        //      <coordinates>   Singular, Required.
        //      <normal>        Singular, Optional.
        //      <color>         Singular, Optional.

        static const NodeIdentifier coordinateLabels[3] = { "x", "y", "z" };
        static const NodeIdentifier normalLabels[3] = { "nx", "ny", "nz" };

        // Load everything we don't handle here.
        
        super::fromXML(xmlElement);
        
        // Cache <coordinates>
        
        // Cache <normal>
        
        // Cache <color>
    }

    ModelCoordinatePtr ModelVertex::modelCoordinate()
    {
#warning Optimize this.

        return std::dynamic_pointer_cast<ModelCoordinate>(this->elementWithIdentifier(ModelCoordinate::Identifier));
    }
    
    ConstModelCoordinatePtr ModelVertex::modelCoordinate() const
    {
#warning Optimize this.
        
        auto modelElementPtr = this->elementWithIdentifier(ModelCoordinate::Identifier);
        
        auto result = std::dynamic_pointer_cast<const ModelCoordinate>(modelElementPtr);

        return result;
    }
    
    ModelNormalPtr ModelVertex::modelNormal()
    {
#warning Optimize this.
        
        return std::dynamic_pointer_cast<ModelNormal>(this->elementWithIdentifier(ModelNormal::Identifier));
    }
    
    ConstModelNormalPtr ModelVertex::modelNormal() const
    {
#warning Optimize this.
        return std::dynamic_pointer_cast<const ModelNormal>(this->elementWithIdentifier(ModelNormal::Identifier));
    }

    ModelColorPtr ModelVertex::modelColor()
    {
#warning Optimize this.

        return std::dynamic_pointer_cast<ModelColor>(this->elementWithIdentifier(ModelColor::Identifier));
    }
    
    ConstModelColorPtr ModelVertex::modelColor() const
    {
#warning Optimize this.

        return std::dynamic_pointer_cast<const ModelColor>(this->elementWithIdentifier(ModelColor::Identifier));
    }
    
    const DoubleVector3D& ModelVertex::coordinate() const
    {
        auto modelCoordinates = this->modelCoordinate();
        
        // Coordinates are required.
        
        assert(modelCoordinates != nullptr);
        
        return modelCoordinates->valueAsVector3D();
    }

    void ModelVertex::setCoordinate(const DoubleVector3D& coordinate)
    {
        auto modelCoordinate = this->modelCoordinate();
        
        if (modelCoordinate == nullptr)
        {
            modelCoordinate = ModelCoordinate::newModelCoordinate(coordinate);
            modelCoordinate = std::static_pointer_cast<ModelCoordinate>(modelCoordinate->setParent(sharedModelElementPtr()));
        }
        
        modelCoordinate->setValueAsVector3D(coordinate);
    }

        
    // Normals are optional.
        
    const DoubleVector3D* ModelVertex::normal() const
    {
        auto modelNormal = this->modelNormal();
                
        if (modelNormal != nullptr)
            return &(modelNormal->valueAsVector3D());
        
        return nullptr;
    }

    // Color is optional.
        
    const DoubleColor* ModelVertex::color() const
    {
        auto modelColor = this->modelColor();
        
        // Will crash if hasColor will return false.

        if (modelColor != nullptr)
            return &(modelColor->valueAsColor());
        
        return nullptr;
    }

    /*
    const SceneGeometry ModelVertex::vertexGeometry() const
    {
        auto coordinates = this->coordinates();
        auto normal = this->normal();
        auto color = this->color();
        
        assert(coordinates);
        
        SceneGeometry result(coordinates->valueAsVector3D(),
                              (normal ? normal->valueAsVector3D() : DoubleVector3D()),
                              (color ? color->valueAsColor() : DoubleColor::White));
        
        return result;
    }
     */

}
