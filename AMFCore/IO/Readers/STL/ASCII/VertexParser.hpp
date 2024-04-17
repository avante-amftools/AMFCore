//
//  VertexParser.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#ifndef VertexParser_hpp
#define VertexParser_hpp

#include "TextParser.hpp"

#include "STLPrimitive.hpp"

namespace AMFCore
{
    
    class ModelObject;
    
    class VertexParser : public TextParser
    {
    private:
        typedef TextParser super;
        
    public:
        VertexParser(std::istream& stream) :
        super(stream, "vertex")
        { }
        
        virtual bool parseHeader();
        
        const STLVec3& vertex() const
        { return _vertex; }
        
    protected:
        STLVec3 _vertex;
    };
}

#endif /* VertexParser_hpp */
