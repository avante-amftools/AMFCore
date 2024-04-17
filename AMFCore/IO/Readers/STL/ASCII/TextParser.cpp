//
//  TextParser.cpp
//  AMFCore
//
//  Created by Ron Aldrich on 8/26/23.
//

#include "TextParser.hpp"

#include <sstream>
#include <iostream>

namespace AMFCore
{
    bool TextParser::parseStream()
    {
        return (this->parseHeader() &&
                this->parseContent() &&
                this->parseFooter());
    }
    
    bool TextParser::parseHeader()
    {
        // std::cout << __PRETTY_FUNCTION__ << " : " << _header << std::endl;
        
        std::vector<std::string> tokens;
        
        if (this->getTokens(tokens) == false)
            return false;
        
        if (tokens.size() < 1)
            return false;
        
        if (tokens[0] != _header)
            return false;
        
        return true;
    }
    
    bool TextParser::parseContent()
    {
        return (_contentParser ? _contentParser->parseStream() : true);
    }
    
    bool TextParser::parseFooter()
    {
        if (_footer != "")
        {
            // std::cout << __PRETTY_FUNCTION__ << " : " << _footer << std::endl;
            
            std::vector<std::string> tokens;
            
            if (this->getTokens(tokens) == false)
                return false;
            
            if (tokens.size() < 1)
                return false;
            
            if (tokens[0] != _footer)
                return false;
        }
        
        return true;
    }
    
    bool TextParser::getTokens(std::vector<std::string>& tokens)
    {
        tokens.clear();
        
        // Extract a line of text from the stream.
        
        std::string line = this->getline();
        
        // Break the line into tokens (whitespace separated strings).
        
        std::istringstream lineStream(line);
        
        while (lineStream)
        {
            std::string token;
            lineStream >> token;
            
            if (token != "")
            {
                tokens.emplace_back(token);
                
                // std::cout << "token: '" << token << "'" << std::endl;
            }
        }
        
        return true;
    }
    
    std::string TextParser::getline()
    {
        std::string result;
        
        std::istream::sentry se(_stream, true);
        std::streambuf* sb = _stream.rdbuf();
        
        for(;;) {
            int c = sb->sbumpc();
            switch (c) {
                case 0:
                    _stream.setstate(std::ios::failbit);
                    return result;
                case '\n':
                    return result;
                case '\r':
                    if(sb->sgetc() == '\n')
                        sb->sbumpc();
                    return result;
                case std::streambuf::traits_type::eof():
                    // Also handle the case when the last line has no line ending
                    if(result.empty())
                        _stream.setstate(std::ios::eofbit);
                    return result;
                default:
                    result += (char)c;
            }
        }
    }
    
    void TextParser::test()
    {
        std::stringstream stream;
        
        stream.str("Header\nFooter\n");
        
        TextParser parser(stream, "Header", nullptr, "Footer");

        parser.parseStream();
    }

}
