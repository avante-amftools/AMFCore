//
//  TextParser.hpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#ifndef TextParser_hpp
#define TextParser_hpp

#include <istream>
#include <string>
#include <vector>

#include "Buffer.hpp"

namespace AMFCore
{
    class TextParser
    {
    public:
        TextParser(std::istream& stream,
                   const std::string& header,
                   TextParser* contentParser = nullptr,
                   const std::string& footer = "") :
        _stream(stream),
        _header(header),
        _contentParser(contentParser),
        _footer(footer)
        { }
        
        virtual bool parseStream();
        
        virtual bool parseHeader();
        
        virtual bool parseContent();
        
        virtual bool parseFooter();
        
    protected:
        bool getTokens(std::vector<std::string>& tokens);
        
        std::string getline();
        
        std::istream& _stream;
        const std::string _header; // Header token.
        TextParser* _contentParser; // Content parser.
        const std::string _footer; // Footer token.
                
    public:
        static void test();
    };
}

#endif /* TextParser_hpp */
