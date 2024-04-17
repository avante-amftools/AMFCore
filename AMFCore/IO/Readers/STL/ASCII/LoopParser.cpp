//
//  LoopParser.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#include "LoopParser.hpp"

namespace AMFCore
{
    bool LoopParser::parseContent()
    {
        for (int i=0; i<3; i++)
        {
            if (_vertexParser.parseStream() == false)
                return false;
            
            _triangle[i] = _vertexParser.vertex();
        }
        
        return true;
    }
}
