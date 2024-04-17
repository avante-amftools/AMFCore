//
//  BufferStreambuf.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 11/1/23.
//

#ifndef BufferStreambuf_hpp
#define BufferStreambuf_hpp

#include "BufferPtr.hpp"

#include <streambuf>

namespace AMFCore
{
    struct BufferStreambuf : std::streambuf
    {
        BufferStreambuf(BufferPtr buffer);
        
        BufferStreambuf(const void* buffer, const uint64_t length);
        
        pos_type seekoff(off_type off_, std::ios_base::seekdir way_, std::ios_base::openmode which_);
        
        pos_type seekpos(pos_type sp_, std::ios_base::openmode which_);
    };
}

#endif /* BufferStreambuf_hpp */
