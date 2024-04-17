//
//  STLDocumentReader.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/25/23.
//

#include "STLDocumentReader.hpp"

#include "ModelRoot.hpp"

#include "ModelObject.hpp"
#include "ModelMesh.hpp"
#include "ModelVertices.hpp"
#include "ModelVertex.hpp"
#include "ModelCoordinate.hpp"
#include "ModelVolume.hpp"

#include "DocumentReaderPtr.hpp"

#include "Buffer.hpp"
#include "BufferStreambuf.hpp"
#include "STLPrimitive.hpp"
#include "SolidParser.hpp"

namespace AMFCore
{
    
    FileType STLDocumentReader::fileType("stl");
    
    void STLDocumentReader::initialize()
    {
        TextParser::test();
        
        __documentReaders.emplace(fileType, newSTLDocumentReader);
    }
    
    STLDocumentReader::STLDocumentReader(const void* buffer,
                      const uint64_t bufferLength) :
    super(buffer, bufferLength)
    {
    }

    ModelRootPtr STLDocumentReader::fromDocument()
    {
        ModelRootPtr result;
        
        if ((result = this->fromTextDocument()) == nullptr)
        {
            result = this->fromBinaryDocument();
        }
        
        // result->debugShow();
        
        return result;
    }
    
    /*
    struct membuf : std::streambuf
    {
        membuf(char* begin, char* end) {
            this->setg(begin, begin, end);
        }
    };
     */

    ModelRootPtr STLDocumentReader::fromBinaryDocument()
    {
        Buffer buffer(_buffer, _bufferLength);
        
        // Skip the 80 byte header.
        
        buffer.setMark(80);
        
        STL_int32_t triCount(buffer);
        
        // Read the vertices.
        
        auto modelVolume = this->modelRoot()->defaultModelVolume();
        
        for  (int32_t triIndex = 0; triIndex < triCount.value; triIndex++)
        {
            STLTriangle triangle(buffer);
            
            auto normal = triangle.normal.asVector3D();
            
            const DoubleVector3DTrio normals = { normal, normal, normal };
            
            const DoubleVector3DTrio vertices = { triangle.v1.asVector3D(),
                triangle.v2.asVector3D(),
                triangle.v3.asVector3D() };
            
            modelVolume->addTriangle(vertices, &normals, nullptr, nullptr);
        }
        
        return this->modelRoot();
    }


    ModelRootPtr STLDocumentReader::fromTextDocument()
    {
        BufferStreambuf bufferStreambuf (_buffer, _bufferLength);
        
        std::istream stream(&bufferStreambuf);
        
        SolidParser parser(stream);
        
        bool result = parser.parseStream();
        
        if (result)
        {
            auto modelRoot = this->modelRoot();
            
            auto modelVolume = modelRoot->defaultModelVolume();

            for (auto i = parser.triangles().begin();
                 i != parser.triangles().end();
                 i++)
            {
                /// Add the triangle to the volume.

                auto normal = i->normal.asVector3D();
                
                const DoubleVector3DTrio vertices = { i->v1.asVector3D(),
                    i->v2.asVector3D(),
                    i->v3.asVector3D()
                };
                
                
                const DoubleVector3DTrio normals = { normal, normal, normal };
                
                modelVolume->addTriangle(vertices, &normals, nullptr, nullptr);
            }
            
            modelRoot->setCompressed(false);
            
            return modelRoot;
        }

        // otherwise return nullptr.
        
        return nullptr;
    }
    
    DocumentReaderPtr STLDocumentReader::newSTLDocumentReader(const void* buffer,
                                                              const uint64_t bufferLength)
    {
        return std::make_shared<STLDocumentReader>(buffer, bufferLength);
    }

    ModelRootPtr STLDocumentReader::modelRoot()
    {
        // Lazy creation of modelRoot.
        
        if (_modelRoot == nullptr)
        {
            _modelRoot = ModelRoot::newModelRoot();
        }
        
        return _modelRoot;
    }
}
