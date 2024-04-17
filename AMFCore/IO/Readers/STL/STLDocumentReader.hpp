//
//  STLDocumentReader.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/25/23.
//

#ifndef STLDocumentReader_hpp
#define STLDocumentReader_hpp

#include "DocumentReader.hpp"

#include "ModelObjectPtr.hpp"
#include "ModelMeshPtr.hpp"
#include "ModelVerticesPtr.hpp"
#include "ModelVolumePtr.hpp"

namespace AMFCore
{
    class STLDocumentReader : public DocumentReader
    {
    private:
        typedef DocumentReader super;
        
    public:
        static FileType fileType;
        
        static void initialize();
        
        STLDocumentReader(const void* buffer,
                          const uint64_t bufferLength);
        
        virtual ModelRootPtr fromDocument();
        
        ModelRootPtr fromBinaryDocument();
        
        ModelRootPtr fromTextDocument();
        
    private:
        static DocumentReaderPtr newSTLDocumentReader(const void* buffer,
                                                      const uint64_t bufferLength);
        
        ModelRootPtr modelRoot();
        ModelRootPtr _modelRoot;
    };
}

#endif /* STLDocumentReader_hpp */
