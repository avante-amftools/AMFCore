//
//  STLDocumentWriter.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/18/23.
//

#include "STLDocumentWriter.hpp"

#include "ModelRoot.hpp"
#include "ModelObject.hpp"
#include "ModelMesh.hpp"
#include "ModelVolume.hpp"
#include "ModelTriangle.hpp"
#include "ModelVertex.hpp"
#include "ModelCoordinate.hpp"

#include "STLPrimitive.hpp"

#include "Buffer.hpp"

#include <assert.h>

namespace AMFCore
{
    FileType STLDocumentWriter::fileType("stl");
    
    void STLDocumentWriter::initialize()
    {
        __documentWriters.emplace(fileType, newSTLDocumentWriter);
    }
    
    BufferPtr STLDocumentWriter::toCompressedDocument()
    {
        // Create a binary STL.
        
        // Compute the triangle count (Sum of the triangles in all volumes).
        
        STL_int32_t triCount(0);
        
        auto modelObjects = _modelRoot->modelObjects();
        
        for (auto i = modelObjects.begin(); i != modelObjects.end(); i++)
        {
            auto modelMesh = (*i)->modelMesh();
            auto modelVolumes = modelMesh->modelVolumes();
            
            for (auto j = modelVolumes.begin(); j != modelVolumes.end(); j++)
            {
                triCount.value += (*j)->triangleCount();
            }
        }
        
        // Compute the size of the file.
        
        // 80 byte header + triangle count + triangles.
        
        size_t bufferLength = 80 + sizeof(triCount) + sizeof(STLTriangle) * triCount.value;
        
        // Allocate the stream.
        
        BufferPtr result = std::make_shared<Buffer>(bufferLength);
        
        // Write the 80 byte header (zeros).
        
        char header[80] = { 0 };
        
        result->write(reinterpret_cast<const char*>(&header), sizeof(header));

        // Write the triangle count (Sum of the triangles in all volumes).
        
        writeBinaryTo(*result, triCount);
        
        // Write the triangles in all volumes.
        
        for (auto i = modelObjects.begin(); i != modelObjects.end(); i++)
        {
            auto modelMesh = (*i)->modelMesh();
            auto modelVolumes = modelMesh->modelVolumes();
            
            for (auto j = modelVolumes.begin(); j != modelVolumes.end(); j++)
            {
                auto modelTriangles = (*j)->modelTriangles();
                
                for (auto k = modelTriangles.begin(); k != modelTriangles.end(); k++)
                {
                    auto modelTriangle = *k;
                    
                    auto normal = modelTriangle->faceNormal();
                    
                    auto vertexes = modelTriangle->modelVertexes();
                    
                    auto c0 = vertexes[0]->modelCoordinate()->valueAsVector3D();
                    auto c1 = vertexes[1]->modelCoordinate()->valueAsVector3D();
                    auto c2 = vertexes[2]->modelCoordinate()->valueAsVector3D();
                    
                    STLTriangle triangle(normal, c0, c1, c2, 0);
                    
                    writeBinaryTo(*result, triangle);
                }
            }
        }

        return result;
    }

    BufferPtr STLDocumentWriter::toUncompressedDocument()
    {
        std::stringstream stream;
        
        auto modelObjects = _modelRoot->modelObjects();

        assert(modelObjects.size() > 0);
        
        auto firstObject = modelObjects[0];
        
        const std::string& name = firstObject->name();
        
        stream << "solid " << name << std::endl;
        
        // Write the triangles.
        
        for (auto i = modelObjects.begin(); i != modelObjects.end(); i++)
        {
            auto modelMesh = (*i)->modelMesh();
            auto modelVolumes = modelMesh->modelVolumes();
            
            for (auto j = modelVolumes.begin(); j != modelVolumes.end(); j++)
            {
                auto modelTriangles = (*j)->modelTriangles();
                
                for (auto k = modelTriangles.begin(); k != modelTriangles.end(); k++)
                {
                    auto modelTriangle = *k;
                    
                    auto normal = modelTriangle->faceNormal();
                    
                    auto vertexes = modelTriangle->modelVertexes();
                    
                    auto c0 = vertexes[0]->modelCoordinate()->valueAsVector3D();
                    auto c1 = vertexes[1]->modelCoordinate()->valueAsVector3D();
                    auto c2 = vertexes[2]->modelCoordinate()->valueAsVector3D();
                    
                    STLTriangle triangle(normal, c0, c1, c2, 0);
                    
                    triangle.writeAsciiTo(stream);
                }
            }
        }

        stream << "endsolid " << name << std::endl;
        
        auto foo = stream.str();
        
        BufferPtr result = std::make_shared<Buffer>(stream.str().size());
        result->write(stream.str().data(), stream.str().size());
        
        return result;
    }

    DocumentWriterPtr STLDocumentWriter::newSTLDocumentWriter(ConstModelRootPtr modelRoot)
    
    {
        return std::make_shared<STLDocumentWriter>(modelRoot);
    }
};
