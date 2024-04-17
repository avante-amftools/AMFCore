//
//  DocumentReader.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#include "DocumentReader.hpp"

#include "AMFDocumentReader.hpp"
#include "ModelNode.hpp"

namespace AMFCore
{
    void DocumentReader::initialize()
    {
        static bool initialized = false;
        
        if (initialized == false)
        {
            AMFDocumentReader::initialize();
            ModelNode::initialize();
            initialized = true;
        }
    }
    
    DocumentReaderPtr DocumentReader::newDocumentReader(const void* buffer,
                                                      const uint64_t bufferLength,
                                                      const FileType& fileType)
    {
        auto i = __documentReaders.find(fileType);
        
        if (i == __documentReaders.end())
            return nullptr;
                
        return i->second(buffer, bufferLength);
    }
    
    std::map<const AMFCore::FileType, DocumentReader::NewDocumentReaderFunction> DocumentReader::__documentReaders;
}
