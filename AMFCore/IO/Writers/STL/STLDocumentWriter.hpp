//
//  STLDocumentWriter.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/18/23.
//

#ifndef STLDocumentWriter_hpp
#define STLDocumentWriter_hpp

#include "DocumentWriter.hpp"

namespace AMFCore
{
    class STLDocumentWriter : public DocumentWriter
    {
    private:
        typedef DocumentWriter super;
        
    public:
        static FileType fileType;
        
        static void initialize();
        
        STLDocumentWriter(ConstModelRootPtr modelRoot) :
        super(modelRoot)
        { }
        
    protected:
        virtual BufferPtr toCompressedDocument();
        
        virtual BufferPtr toUncompressedDocument();
        
    private:
        static DocumentWriterPtr newSTLDocumentWriter(ConstModelRootPtr modelRoot);
    };
};

#endif /* STLDocumentWriter_hpp */
