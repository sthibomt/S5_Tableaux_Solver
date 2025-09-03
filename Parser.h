#pragma once
#include "Formula.h"
#include <cctype>
#include <stdexcept>
#include <string>


using namespace std;

class Parser 
{
    string s;
    size_t i = 0;

    // ------------------------------------------------------------------------------------------------------------------
    void skip() 
    { 
        while (i < s.size() && isspace(s[i])) 
        ++i;
    }

    // ------------------------------------------------------------------------------------------------------------------
    bool consume(char c) 
    {
        skip();
        if (i < s.size() && s[i] == c) 
        { 
            ++i; 
            return true; 
        }
        return false;
    }

    // ------------------------------------------------------------------------------------------------------------------
    shared_ptr<Formula> parseAtom() 
    {
        skip();
        if (consume('~')) 
        {
            return Formula::Not(parseAtom());
        }
        if (consume('(')) 
        {
            auto f = parseAnd();
            consume(')'); // assume well-formed
            return f;
        }
        if (i < s.size() && isalpha(s[i])) 
        {
            std::string id(1, s[i]);
            ++i;
            return Formula::Atom(id);
        }
        throw std::runtime_error("Unexpected symbol in formula");
    }

    // ------------------------------------------------------------------------------------------------------------------
public:
    Parser(const std::string& str) : s(str) 
    {}

    // ------------------------------------------------------------------------------------------------------------------
    shared_ptr<Formula> parseAnd() 
    {
        auto left = parseAtom();
        while (true) 
        {
            skip();
            if (consume('&')) 
            {
                auto right = parseAtom();
                left = Formula::And(left, right);
            } else break;
        }
        return left;
    }

};