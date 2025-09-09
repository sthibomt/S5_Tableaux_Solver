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
    bool consumeStr(const std::string &t)
    {
        skip();
        if (s.substr(i, t.size()) == t)
        {
            i += t.size();
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
        if (consume('['))
        { // box
            consume(']');
            return Formula::Box(parseAtom());
        }
        if (consume('<'))
        { // diamond
            consume('>');
            return Formula::Diamond(parseAtom());
        }
        if (consume('('))
        {
            auto f = parseImp();
            consume(')');
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
            }
            else
                break;
        }
        return left;
    }

    // ------------------------------------------------------------------------------------------------------------------
    std::shared_ptr<Formula> parseOr()
    {
        auto left = parseAnd();
        while (true)
        {
            skip();
            if (consume('|'))
            {
                auto right = parseAnd();
                left = Formula::Or(left, right);
            }
            else
                break;
        }
        return left;
    }

    // ------------------------------------------------------------------------------------------------------------------
    std::shared_ptr<Formula> parseImp()
    {
        auto left = parseOr();
        while (true)
        {
            skip();
            if (consumeStr("->"))
            {
                auto right = parseOr();
                left = Formula::Imp(left, right);
            }
            else
                break;
        }
        return left;
    }

    // ------------------------------------------------------------------------------------------------------------------
    // Constructor
public:
    Parser(const std::string &str) : s(str)
    {
    }

    std::shared_ptr<Formula> parse()
    {
        return parseImp();
    }
};