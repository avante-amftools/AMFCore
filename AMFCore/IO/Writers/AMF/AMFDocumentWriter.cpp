//
//  AMFDocumentWriter.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/13/23.
//

#include "AMFDocumentWriter.hpp"

#include "tinyxml2.h"
#include "zip.hpp"
#include "ModelRoot.hpp"
#include "Buffer.hpp"

namespace AMFCore
{
    FileType AMFDocumentWriter::fileType("amf");
    
    void AMFDocumentWriter::initialize()
    {
        __documentWriters.emplace(fileType, newAMFDocumentWriter);
    }
    
    BufferPtr AMFDocumentWriter::toCompressedDocument()
    {
        auto uncompressedBuffer = this->toUncompressedDocument();
        
        // Zip the uncompressed buffer.
        
        return uncompressedBuffer;
    }
    
    BufferPtr AMFDocumentWriter::toUncompressedDocument()
    {
        auto xmlDocument = _modelRoot->toXMLDocument();
        
        // Convert the xml document to a text buffer.
        
        XMLPrinter printer;
        xmlDocument->Print(&printer);
        
        auto result = std::make_shared<Buffer>();
        
        result->write(printer.CStr(),
                      printer.CStrSize());
        
        return result;
    }
    
    std::unique_ptr<XMLDocument> AMFDocumentWriter::toXMLDocument()
    {
        return _modelRoot->toXMLDocument();
    }
    
    DocumentWriterPtr AMFDocumentWriter::newAMFDocumentWriter(ConstModelRootPtr modelRoot)
    
    {
        return std::make_shared<AMFDocumentWriter>(modelRoot);
    }
    
}
