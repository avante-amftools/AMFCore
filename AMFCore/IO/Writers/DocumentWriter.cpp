//
//  DocumentWriter.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/10/23.
//

#include "DocumentWriter.hpp"

#include "AMFDocumentWriter.hpp"
#include "ModelNode.hpp"

namespace AMFCore
{
    void DocumentWriter::initialize()
    {
        static bool initialized = false;
        
        if (initialized == false)
        {
            AMFDocumentWriter::initialize();
            ModelNode::initialize();
            initialized = true;
        }
    }
    
    BufferPtr DocumentWriter::toDocument()
    {
        if (this->compressed())
            return this->toCompressedDocument();
        else
            return this->toUncompressedDocument();
    }
    
    DocumentWriterPtr DocumentWriter::newDocumentWriter(ConstModelRootPtr modelRoot,
                                                        const FileType &fileType)
    {
        auto i = __documentWriters.find(fileType);
        if (i == __documentWriters.end())
            return nullptr;
        
        return i->second(modelRoot);
    }
    
    std::map<const AMFCore::FileType, DocumentWriter::NewDocumentWriterFunction> DocumentWriter::__documentWriters;
}
