//
//  Buffer.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/18/23.
//
//  A general purpose RAM buffer, which can either represent a read-only
//  buffer where the RAM is owned by client code, or a read/write buffer
//  where the RAM is owned by the Buffer object.
//
//  This allows better integration with client code written in
//  environments such as Swift, that need to handle their own memory
//  management.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <vector>

namespace AMFCore
{
    struct Buffer
    {
        // Create a writable, resizable buffer.
        
        Buffer(const size_t reserve = 0) :
        _mark(0)
        {
            _buffer.reserve(reserve);
            _data = &_buffer[0];
            _length = _buffer.size();
        }
        
        // Create a read-only buffer.
        
        Buffer(const char* data,
               const size_t length) :
        _data(const_cast<char*>(data)),
        _length(length),
        _mark(0)
        { }
        
        // Convenience constructor for a read-only buffer.
        
        Buffer(const void* data,
               const size_t length) :
        Buffer(reinterpret_cast<const char*>(data), length)
        { }
        
        const size_t mark() const
        {
            return _mark;
        }
        
        const size_t setMark(const size_t mark)
        {
            // You cannot position the mark past the end of the buffer.
            
            if (mark > _length)
                throw(std::logic_error("mark > buffer's length"));
            
            _mark = mark;
            return _mark;
        }
        
        const size_t read(char* reqData,
                          const size_t reqBytes) const
        {
            auto actBytes = _length - _mark;
            if (actBytes > reqBytes)
                actBytes = reqBytes;
            
            char* srcData = _data + _mark;
            
            memcpy(reqData, srcData, actBytes);
            
            return actBytes;
        }
        
        const size_t write(const char* srcData,
                           const size_t srcLength)
        {
            // Don't allow writes unless we own the buffer.
            
            if (_data != &_buffer[0])
                throw(std::logic_error("Buffer is read-only."));
            
            auto newSize = _mark + srcLength;
            
            if (_buffer.size() < newSize)
            {
                _buffer.resize(newSize);
                
                _data = &_buffer[0];
                _length = newSize;
            }
            
            memcpy(&_data[_mark], srcData, srcLength);
            
            _mark += srcLength;
            
            return srcLength;
        }
        
        const char* data() const
        {
            return _data;
        }
        
        const size_t length() const
        {
            return _length;
        }
        
        inline void debugShow()
        {
            for (int index = 0; index < length(); index++)
            {
                printf("%02X ", (unsigned char)data()[index]);
                if (index % 16 == 15)
                    printf("\n");
            }
            printf("\n");
        }

    private:
        // Owned RAM.  This vector will be empty if we don't own the RAM.
        
        std::vector<char> _buffer;
        
        // (Possibly) Unowned RAM.  _data will point to _buffer if we
        //  own the RAM.
        
        char* _data;
        size_t _length;
        
        // Read/Write mark.
        
        size_t _mark;
    };
    
    template <class T>
    inline void readBinaryFrom(Buffer& buffer, T& data)
    {
        if (buffer.read(reinterpret_cast<char*>(&data), sizeof(data)) < sizeof(data))
        {
            throw(std::runtime_error("End of file reached unexpectedly"));
        }
        
        data.toNativeEndian();
    }
        
    template <class T>
    inline void writeBinaryTo(Buffer& buffer, T& data)
    {
        data.toStreamEndian();
        
        buffer.write(reinterpret_cast<const char*>(&data), sizeof(data));
        
        data.toNativeEndian();
    }
}

#endif /* Buffer_hpp */
