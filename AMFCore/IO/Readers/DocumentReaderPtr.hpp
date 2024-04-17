//
//  DocumentReaderPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/28/23.
//

#ifndef DocumentReaderPtr_h
#define DocumentReaderPtr_h

#include <memory>

namespace AMFCore
{
    class DocumentReader;
    
    typedef std::shared_ptr<DocumentReader> DocumentReaderPtr;
    typedef std::shared_ptr<const DocumentReader> ConstDocumentReaderPtr;
}

#endif /* DocumentReaderPtr_h */
