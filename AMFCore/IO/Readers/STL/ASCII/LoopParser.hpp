//
//  LoopParser.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#ifndef LoopParser_hpp
#define LoopParser_hpp

#include "TextParser.hpp"
#include "VertexParser.hpp"
#include "STLPrimitive.hpp"

namespace AMFCore
{
    class LoopParser : public TextParser
    {
    private:
        typedef TextParser super;
        
    public:
        LoopParser(std::istream& stream) :
        super(stream, "outer", nullptr, "endloop"),
        _vertexParser(stream)
        { }
        
        virtual bool parseContent();
        
        const STLTriangle& triangle() const
        { return _triangle; }
        
    protected:
        VertexParser _vertexParser;
        
        STLTriangle _triangle;
    };
}

#endif /* LoopParser_hpp */
