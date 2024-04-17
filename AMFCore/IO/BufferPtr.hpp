//
//  BufferPtr.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/19/23.
//

#ifndef BufferPtr_hpp
#define BufferPtr_hpp

#include <memory>

namespace AMFCore
{
    class Buffer;
    
    typedef std::shared_ptr<Buffer> BufferPtr;
    typedef std::shared_ptr<const Buffer> ConstBufferPtr;
}

#endif /* BufferPtr_hpp */
