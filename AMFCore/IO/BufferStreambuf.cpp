//
//  BufferStreambuf.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 11/1/23.
//

#include "BufferStreambuf.hpp"

#include "Buffer.hpp"

namespace AMFCore
{
    BufferStreambuf::BufferStreambuf(BufferPtr buffer) :
    BufferStreambuf(buffer->data(), buffer->length())
    {
    }

    BufferStreambuf::BufferStreambuf(const void* buffer, const uint64_t length)
    {
        this->setg((char*) buffer, (char*) buffer, (char*) buffer + length);
    }
    
    BufferStreambuf::pos_type BufferStreambuf::seekoff(off_type off_, std::ios_base::seekdir way_, std::ios_base::openmode which_)
    {
        // This class is only ever used with std::istream, so we ignore which_
        
        char* mark;
        
        switch (way_)
        {
            case std::ios_base::beg:
                mark = eback();
                break;
            case std::ios_base::cur:
                mark = gptr();
                break;
            case std::ios_base::end:
                mark = egptr();
                break;
        }
        
        mark += off_;
        
        if (mark < eback() || mark > egptr())
            return -1;
        
        setg(eback(), mark, egptr());
        
        return mark-eback();
    }
    
    BufferStreambuf::pos_type BufferStreambuf::seekpos(pos_type sp_, std::ios_base::openmode which_)
    {
        return seekoff(off_type(sp_), std::ios_base::beg, which_);
    }
}

