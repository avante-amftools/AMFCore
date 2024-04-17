//
//  FacetParser.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#ifndef FacetParser_hpp
#define FacetParser_hpp

#include "TextParser.hpp"
#include "LoopParser.hpp"
#include "STLPrimitive.hpp"

namespace AMFCore
{
    class FacetParser : public TextParser
    {
    private:
        typedef TextParser super;
        
    public:
        FacetParser(std::istream& stream) :
        super(stream, "facet", &_loopParser, "endfacet"),
        _loopParser(stream)
        { }
        
        virtual bool parseHeader();
        
        const STLTriangle triangle() const
        {
            STLTriangle result = _loopParser.triangle();
            result.normal = _normal;
            result.attributeBytes = 0;
            
            return result;
        }
        
    protected:
        STLVec3 _normal;
        LoopParser _loopParser;
    };
}

#endif /* FacetParser_hpp */
