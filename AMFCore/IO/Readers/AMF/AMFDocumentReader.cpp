//
//  AMFDocumentReader.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#include "AMFDocumentReader.hpp"

#include "tinyxml2.h"
#include "unzip.hpp"

#include "ModelRoot.hpp"

#include "DocumentReaderPtr.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    FileType AMFDocumentReader::fileType("amf");
    
    void AMFDocumentReader::initialize()
    {
        __documentReaders.emplace(fileType, newAMFDocumentReader);
    }
    
    ModelRootPtr AMFDocumentReader::fromDocument()
    {
        ModelRootPtr result;
        
        if ((result = this->fromCompressedDocument()) == nullptr)
        {
            result = this->fromUncompressedDocument();
        }
        
        // result->debugShow();
        
        return result;
    }
    
    ModelRootPtr AMFDocumentReader::fromCompressedDocument()
    {
        zipwrapped::unzip unzip;
        
        if (!unzip.open((const char*) _buffer, _bufferLength))
            return NULL;
        
        // Search for a file within the archive, which has the same name as the archive.
        // Failing that, search for the first .amf within the archive.
        
        // if (unzip.seekFileEntryWithName(pathComponents(filePath).back()) == false)
        if (unzip.seekFileEntryWithExtension("amf") == false)
            return NULL;
        
        auto uncompressedSize = unzip.uncompressedSize();
        
        XMLDocument document;
        
        {   // Insure that the buffer gets disposed after we parse
            //  it into an XMLDocument, and before we turn that
            //  document into a model.
            
            std::unique_ptr<char[]> buffer(new char[uncompressedSize]);
            int64_t result = unzip.unzipCurrentEntry(buffer.get(), uncompressedSize);
            if (result != uncompressedSize)
                throw(std::runtime_error("could not decompress AMF archive"));
            
            if (document.Parse(buffer.get(), unzip.uncompressedSize()) != XML_SUCCESS)
                throw(std::runtime_error("could not parse AMF document"));
        }
        
        auto result = this->fromXMLDocument(document);
        
        if (result != nullptr)
        {
            result->setCompressed(true);
        }
        
        return result;
    }
    
    ModelRootPtr AMFDocumentReader::fromUncompressedDocument()
    {
        XMLDocument document;
        
        if (document.Parse((const char*) _buffer, _bufferLength) != XML_SUCCESS)
            return NULL;
        
        auto result = this->fromXMLDocument(document);
        
        if (result != nullptr)
        {
            result->setCompressed(false);
        }
        
        return result;
    }
    
    ModelRootPtr AMFDocumentReader::fromXMLDocument(XMLDocument& document)
    {
        // printf("entered %s\n", __PRETTY_FUNCTION__);
        
        XMLElement* rootElement = document.FirstChildElement("amf");
        
        if (rootElement == nullptr)
            throw(std::runtime_error("could not locate required <amf> element"));
        
        ModelRootPtr modelRoot = std::dynamic_pointer_cast<ModelRoot>(ModelElement::newModelElement(ModelRoot::Identifier));
        
        modelRoot->fromXML(rootElement);
        
        modelRoot->debugShow();
        
        return modelRoot;
    }
    
    DocumentReaderPtr AMFDocumentReader::newAMFDocumentReader(const void* buffer,
                                         const uint64_t bufferLength)
    {
        return std::make_shared<AMFDocumentReader>(buffer, bufferLength);
    }
}
