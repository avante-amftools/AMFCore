//
//  AMFCore.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 2/23/23.
//

#ifndef AMFCore_hpp
#define AMFCore_hpp

#include <string>
#include <set>

namespace AMFCore
{
    typedef std::string NodeIdentifier;
    
    void initialize();

    void initializeSTL();

    void assertIsInitialized();
}

#endif /* AMFCore_hpp */
