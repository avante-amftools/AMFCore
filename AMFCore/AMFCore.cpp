//
//  AMFCore.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/23/23.
//

#include "AMFCore.hpp"

#include "DocumentReader.hpp"
#include "STLDocumentReader.hpp"
#include "STLDocumentWriter.hpp"

#include "ModelRoot.hpp"

#include <assert.h>

namespace AMFCore
{
    static bool __initialized = false;
    static bool __initializedSTL = false;
    
    void initialize()
    {
        if (__initialized == false)
        {
            DocumentReader::initialize();
            DocumentWriter::initialize();
            ModelRoot::initialize();
            __initialized = true;
        }
    }
    
    void initializeSTL()
    {
        if (__initializedSTL == false)
        {
            STLDocumentReader::initialize();
            STLDocumentWriter::initialize();
            __initializedSTL = true;
        }
    }

    
    void assertInitialized()
    {
        assert(__initialized == true);
    }
}
