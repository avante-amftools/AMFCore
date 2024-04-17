//
//  SolidParser.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#ifndef SolidParser_hpp
#define SolidParser_hpp

#include "TextParser.hpp"
#include "FacetParser.hpp"
#include "STLPrimitive.hpp"

#include <vector>

namespace AMFCore
{
    class SolidParser : public TextParser
    {
    private:
        typedef TextParser super;
        
    public:
        SolidParser(std::istream& stream) :
        super(stream, "solid", &_facetParser, "endsolid"),
        _facetParser(stream)
        { }
        
        const std::string& name() const
        { return _name; }
        
        const std::vector<STLTriangle>& triangles() const
        { return _triangles; }
        
        virtual bool parseHeader();
        
        virtual bool parseContent();
        
        virtual bool parseStream();

    protected:
        std::string _name;
        std::vector<STLTriangle> _triangles;
        FacetParser _facetParser;
    };
}

#endif /* SolidParser_hpp */
