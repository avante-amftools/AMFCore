//
//  SolidParser.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#include "SolidParser.hpp"

#include <iostream>

#include "ModelObject.hpp"

namespace AMFCore
{
    bool SolidParser::parseHeader()
    {
        // std::cout << __PRETTY_FUNCTION__ << " : " << _header << std::endl;
        
        std::vector<std::string> tokens;
        
        if (this->getTokens(tokens) == false)
            return false;
        
        if (tokens.size() < 1)
            return false;
        
        if (tokens[0] != _header)
            return false;
        
        if (tokens.size() >= 2)
        {
            _name = tokens[1];
        }
        
        return true;
    }
    
    bool SolidParser::parseContent()
    {
        _triangles.clear();
        
        std::streampos mark;
        
        bool parsingFacets = true;
        
        while (parsingFacets)
        {
            // Save our mark, so we can rewind the stream when we run out of facets to parse.
            
            mark = _stream.tellg();
            
            parsingFacets = super::parseContent();
            
            if (parsingFacets)
            {
                _triangles.push_back(_facetParser.triangle());
            }
        }
        
        // We stopped when we encountered a token we didn't recognize, so we need to re-parse that token.
        
        _stream.seekg(mark);
        
        // std::cout << __PRETTY_FUNCTION__ << " " << _triangles.size() << " triangles." << std::endl;
        
        return true;
    }
    
    bool SolidParser::parseStream()
    {
        if (this->parseHeader() == false)
            return false;
        
        if (this->parseContent() == false)
            return false;
        
        return this->parseFooter();
    }

}
