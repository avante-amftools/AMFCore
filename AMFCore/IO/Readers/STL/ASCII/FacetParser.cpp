//
//  FacetParser.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#include "FacetParser.hpp"

#include <iostream>

namespace AMFCore
{
    bool FacetParser::parseHeader()
    {
        // std::cout << __PRETTY_FUNCTION__ << " : " << _header << std::endl;
        
        std::vector<std::string> tokens;
        
        if (this->getTokens(tokens) == false)
            return false;
        
        if (tokens.size() < 1)
            return false;
        
        if (tokens[0] != _header)
            return false;
        
        if (tokens.size() == 1)
            return true;
        
        if (tokens.size() != 5)
            return false;
        
        if (tokens[1] != "normal")
            return false;
        
        try
        {
            for (int i=0; i<3; i++)
                _normal[i] = std::stof(tokens[i+2]);
        }
        catch (...)
        {
            return false;
        }
        
        return true;
    }
}
