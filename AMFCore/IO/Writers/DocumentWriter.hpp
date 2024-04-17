//
//  DocumentWriter.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/10/23.
//

#ifndef DocumentWriter_hpp
#define DocumentWriter_hpp

#include <map>

#include "DocumentIO.hpp"
#include "ModelRootPtr.hpp"
#include "DocumentWriterPtr.hpp"
#include "BufferPtr.hpp"

namespace AMFCore
{
    class DocumentWriter
    {
    protected:
        typedef DocumentWriterPtr (*NewDocumentWriterFunction)(ConstModelRootPtr modelRoot);
        
    public:
        static void initialize();
        
        static DocumentWriterPtr newDocumentWriter(ConstModelRootPtr modelRoot,
                                                   const FileType& fileType);
        
        DocumentWriter(ConstModelRootPtr modelRoot) :
        _modelRoot(modelRoot),
        _compressed(true)
        { }
        
        const bool compressed() const
        { return _compressed; }
        
        void setCompressed(bool compressed)
        { _compressed = compressed; }
        
        virtual BufferPtr toDocument();
        
    protected:
        virtual BufferPtr toCompressedDocument() = 0;

        virtual BufferPtr toUncompressedDocument() = 0;

        ConstModelRootPtr _modelRoot;
        bool _compressed;
        
        static std::map<const FileType, NewDocumentWriterFunction> __documentWriters;
    };
}

#endif /* DocumentWriter_hpp */
