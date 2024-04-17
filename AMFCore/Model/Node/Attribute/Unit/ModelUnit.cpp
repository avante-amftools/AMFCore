//
//  ModelUnit.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/15/23.
//

#include "ModelUnit.hpp"

namespace AMFCore
{
    using namespace tinyxml2;
    
    NodeIdentifier ModelUnit::Identifier("unit");
    
    ModelAttributePtr ModelUnit::_newModelUnit()
    {
        return std::make_shared<ModelUnit>();
    }
    
    void ModelUnit::initialize()
    {
        static bool initialized = false;
        
        if (!initialized)
        {
            newModelAttributeFunctions().emplace(Identifier, _newModelUnit);

            initialized = true;
        }
    }
}
