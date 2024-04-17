//
//  DocumentReader.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/27/23.
//

#ifndef DocumentReader_hpp
#define DocumentReader_hpp

#include <map>

#include "DocumentIO.hpp"
#include "ModelRootPtr.hpp"
#include "DocumentReaderPtr.hpp"

namespace AMFCore
{
    // Refactor this to use the Buffer class.
    
    class DocumentReader
    {
    protected:
        typedef DocumentReaderPtr (*NewDocumentReaderFunction)(const void* buffer,
                                                             const uint64_t bufferLength);
        
    public:
        static void initialize();
        
        static DocumentReaderPtr newDocumentReader(const void* buffer,
                                                 const uint64_t bufferLength,
                                                 const FileType& fileType);
        DocumentReader(const void* buffer,
                       const uint64_t bufferLength) :
        _buffer(buffer),
        _bufferLength(bufferLength)
        { }
        
        virtual ModelRootPtr fromDocument() = 0;
        
    protected:
        const void* _buffer;
        const uint64_t _bufferLength;

        static std::map<const FileType, NewDocumentReaderFunction> __documentReaders;
    };
}
        

#endif /* DocumentReader_hpp */
