//
//  ModelTriangle.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 3/4/23.
//

#include "ModelTriangle.hpp"

#include "tinyxml2.h"

#include "ModelVolume.hpp"
#include "ModelMesh.hpp"
#include "ModelVertices.hpp"
#include "ModelVertex.hpp"
#include "ModelCoordinate.hpp"
#include "ModelNormal.hpp"
#include "ModelColor.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelTriangle::Identifier("triangle");
    
    ModelElementPtr ModelTriangle::_newModelTriangle()
    {
        return std::make_shared<ModelTriangle>();
    }
    
    void ModelTriangle::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            __newModelElementFunctions.emplace(Identifier, _newModelTriangle);

            initialized = true;
        }
    }
    
    ModelTrianglePtr ModelTriangle::newModelTriangle()
    {
        return std::dynamic_pointer_cast<ModelTriangle>(ModelElement::newModelElement(ModelTriangle::Identifier));
    }
    
    void ModelTriangle::fromXML(const XMLElement* xmlElement)
    {
        //  <triangle>
        //      <v1>        integer         * optimized
        //      <v2>        integer         * optimized
        //      <v3>        integer         * optimized
        //      <color>     ModelColor
        //      <texmap>    ModelTexmap
        
        static const NodeIdentifier labels[3] = { "v1", "v2", "v3" };
        
        super::fromXML(xmlElement);
    
        // Copy the v1, v2 and v3 values to _vertexIndex,
        //  and remove those elements from _elements.
        
        for (auto i = V0; i <= V2; i++)
        {
            auto element = this->elementWithIdentifier(labels[i]);
            
            if (element == nullptr)
                throw(std::runtime_error("<triangle> could not locate required <" + labels[i] + "> element"));
            
            _vertexIndices[i] = element->valueAsInt32();
            
            element->setParent(nullptr);
        }
    }
    
    void ModelTriangle::childrenToXML(XMLElement* thisElement) const
    {
        // The v1, v2 and v3 values are optimized, and
        //  therefore are not present in the object graph,
        //  so we need to synthesize them for the XML document.
        
        for (Axis i = V0; i <= V2; i++)
        {
            static const char* __labels[3] = { "v1", "v2", "v3" };
            
            auto vertexIndex = _vertexIndices[i];
            
            XMLElement* vertexElement = thisElement->InsertEndChild(thisElement->GetDocument()->NewElement(__labels[i]))->ToElement();
            
            vertexElement->SetText(std::to_string(vertexIndex).c_str());
        }
        
        super::childrenToXML(thisElement);
    }

    
    void ModelTriangle::setValueAsVector3D(UInt32Vector3D value)
    {
        static const NodeIdentifier labels[3] = { "v1", "v2", "v3" };

        _vertexIndices = value;
        
        /*
        // Create default vertices if needed.
        
        for (auto i = V0; i <= V2; i++)
        {
            auto element = this->elementWithIdentifier(labels[i]);
            
            if (element == nullptr)
            {
                element = ModelElement::newModelElement(labels[i]);
            }
            
            element->setValueAsInt32(value[i]);
        }
         */
    };

    std::vector<ConstModelVertexPtr> ModelTriangle::modelVertexes() const
    {
        std::vector<ConstModelVertexPtr> result;
        result.reserve(3);
        
        auto modelVertexes = this->parentModelMesh()->modelVertices()->modelVertexes();
        
        for (auto i = V0; i <= V2; i++)
        {
            auto modelVertex = modelVertexes[_vertexIndices[i]];
            
            result.push_back(modelVertex);
        }
        
        return result;
    }

    
    ModelColorPtr ModelTriangle::color()
    {
        return std::dynamic_pointer_cast<ModelColor>(this->elementWithIdentifier(ModelColor::Identifier));
    }
    
    ConstModelColorPtr ModelTriangle::color() const
    {
        return std::dynamic_pointer_cast<const ModelColor>(this->elementWithIdentifier(ModelColor::Identifier));
    }
    
    const DoubleColor* ModelTriangle::faceColor() const
    {
        auto modelColor = this->color();
        return (modelColor) ? &modelColor->valueAsColor() : nullptr;
    }
    
    void ModelTriangle::setFaceColor(const DoubleColor* faceColor)
    {
    }

    
    const DoubleColor* ModelTriangle::vertexColor(Axis cornerIndex) const
    {
        auto vertices = this->parentModelMesh()->modelVertices()->modelVertexes();
        
        auto vertex = vertices[_vertexIndices[cornerIndex]];
        
        auto vertexColor = vertex->modelColor();
        
        return (vertexColor) ? &vertexColor->valueAsColor() : nullptr;
    }
    
    const DoubleColor* ModelTriangle::volumeColor() const
    {
#warning implement this.
        return nullptr;
        
        /*
        auto volume = this->parentVolume();
        
        auto volumeColor = volume->color();
        
        return (volumeColor) ? &volumeColor->valueAsColor() : nullptr;
         */
    }
    
    const DoubleColor* ModelTriangle::objectColor() const
    {
#warning implement this.
        return nullptr;
    }
    
    const DoubleColor* ModelTriangle::materialColor() const
    {
#warning implement this.
        return nullptr;
    }
    
    const DoubleColor* ModelTriangle::defaultColor() const
    {
        return &__defaultColor;
    }

    const SceneVertex ModelTriangle::sceneVertex(Axis cornerIndex) const
    {
        auto vertices = this->parentModelMesh()->modelVertices()->modelVertexes();
        
        auto vertex = vertices[_vertexIndices[cornerIndex]];
        
        DoubleVector3D coordinates = vertex->modelCoordinate()->valueAsVector3D();
        
        DoubleVector3D normal;
        
        if (auto vertexNormal = vertex->modelNormal())
        {
            normal = vertexNormal->valueAsVector3D();
        }
        else
        {
            normal = this->faceNormal();
        }
        
        // Color priority:  face color
        //                  vertex color
        //                  volume color
        //                  object color
        //                  material color
        //                  default color

        const DoubleColor* color = this->faceColor();
        
        if (!color)
            color = this->vertexColor(cornerIndex);
        
        if (!color)
            color = this->objectColor();
        
        if (!color)
            color = this->volumeColor();
        
        if (!color)
            color = this->materialColor();
        
        if (!color)
            color = this->defaultColor();
                    
        SceneVertex result = { coordinates, normal, *color };
        
        return result;
    }
                       
    const DoubleVector3D ModelTriangle::faceNormal() const
    {
        auto vertices = this->parentModelMesh()->modelVertices()->modelVertexes();
        
        auto v0 = vertices[_vertexIndices[V0]];
        auto v1 = vertices[_vertexIndices[V1]];
        auto v2 = vertices[_vertexIndices[V2]];

        auto a = v0->modelCoordinate()->valueAsVector3D() - v1->modelCoordinate()->valueAsVector3D();
        
        auto b = v1->modelCoordinate()->valueAsVector3D() - v2->modelCoordinate()->valueAsVector3D();
        auto vD = a.crossProduct(b);
                
        double vL = vD.length();
        
        return (vL == 0 ? DoubleVector3D() : vD / vL);
    }
    
    
    void ModelTriangle::debugShow(std::string indent)
    {
        const char* identifier = this->identifier().c_str();
        
        printf("%s%s %s [%d %d %d]\n", indent.c_str(), identifier, this->valueAsString().c_str(),
               _vertexIndices[X],
               _vertexIndices[Y],
               _vertexIndices[Z]);
    }

    
    ModelVolumePtr ModelTriangle::parentModelVolume()
    {
        return std::dynamic_pointer_cast<ModelVolume>(this->parent());
    }

    ConstModelVolumePtr ModelTriangle::parentModelVolume() const
    {
        return std::dynamic_pointer_cast<const ModelVolume>(this->parent());
    }

    ModelMeshPtr ModelTriangle::parentModelMesh()
    {
        return this->parentModelVolume()->parentModelMesh();
    }
    
    ConstModelMeshPtr ModelTriangle::parentModelMesh() const
    {
        return this->parentModelVolume()->parentModelMesh();
    }

    DoubleColor ModelTriangle::__defaultColor(1.0, 1.0, 1.0, 1.0);
}
