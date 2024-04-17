//
//  VertexParser.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#include "VertexParser.hpp"

#include <iostream>

namespace AMFCore
{
    bool VertexParser::parseHeader()
    {
        // std::cout << __PRETTY_FUNCTION__ << " : " << _header << std::endl;
        
        std::vector<std::string> tokens;
        
        if (this->getTokens(tokens) == false)
            return false;
        
        if (tokens.size() < 4)
            return false;
        
        if (tokens[0] != _header)
            return false;
        
        try
        {
            for (int i=0; i<3; i++)
                _vertex[i] = std::stof(tokens[i+1]);
        }
        catch (...)
        {
            return false;
        }
        
        return true;
    }
}
