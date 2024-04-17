//
//  DocumentWriterPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/10/23.
//

#ifndef DocumentWriterPtr_hpp
#define DocumentWriterPtr_hpp

#include <memory>

namespace AMFCore
{
    class DocumentWriter;
    
    typedef std::shared_ptr<DocumentWriter> DocumentWriterPtr;
    typedef std::shared_ptr<const DocumentWriter> ConstDocumentWriterPtr;
}

#endif /* DocumentWriterPtr_hpp */
