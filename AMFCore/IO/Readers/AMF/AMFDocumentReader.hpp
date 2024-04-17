//
//  AMFDocumentReader.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef AMFDocumentReader_hpp
#define AMFDocumentReader_hpp

#include "DocumentReader.hpp"

namespace tinyxml2
{
    class XMLDocument;
};

namespace AMFCore
{
    using namespace tinyxml2;
    
    class AMFDocumentReader : public DocumentReader
    {
    private:
        typedef DocumentReader super;
        
    public:
        static FileType fileType;
        
        static void initialize();
        
        AMFDocumentReader(const void* buffer,
                          const uint64_t bufferLength) :
        super(buffer, bufferLength)
        { }
        
        virtual ModelRootPtr fromDocument();
        
        ModelRootPtr fromCompressedDocument();
        
        ModelRootPtr fromUncompressedDocument();
        
        ModelRootPtr fromXMLDocument(XMLDocument& document);
        
    private:
        static DocumentReaderPtr newAMFDocumentReader(const void* buffer,
                                                      const uint64_t bufferLength);
    };
}

#endif /* AMFDocumentReader_hpp */
