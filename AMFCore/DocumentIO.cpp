//
//  DocumentIO.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 10/10/23.
//

#include "DocumentIO.hpp"

#include "DocumentReader.hpp"
#include "DocumentWriter.hpp"

namespace AMFCore
{
    void DocumentIO::initialize()
    {
        static bool initialized = false;
        
        if (initialized == false)
        {
            DocumentReader::initialize();
            DocumentWriter::initialize();
            initialized = true;
        }
    }
}
