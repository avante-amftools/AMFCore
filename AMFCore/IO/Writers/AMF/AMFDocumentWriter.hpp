//
//  AMFDocumentWriter.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/13/23.
//

#ifndef AMFDocumentWriter_hpp
#define AMFDocumentWriter_hpp

#include "DocumentWriter.hpp"

namespace tinyxml2
{
    class XMLDocument;
};

namespace AMFCore
{
    using namespace tinyxml2;
    
    class AMFDocumentWriter : public DocumentWriter
    {
    private:
        typedef DocumentWriter super;
        
    public:
        static FileType fileType;
        
        static void initialize();
        
        AMFDocumentWriter(ConstModelRootPtr modelRoot) :
        super(modelRoot)
        { }
        
    protected:
        virtual BufferPtr toCompressedDocument();
        
        virtual BufferPtr toUncompressedDocument();

        std::unique_ptr<XMLDocument> toXMLDocument();

    private:
        static DocumentWriterPtr newAMFDocumentWriter(ConstModelRootPtr modelRoot);
    };
};

#endif /* AMFDocumentWriter_hpp */
