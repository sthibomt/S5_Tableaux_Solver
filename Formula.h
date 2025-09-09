#pragma once
#include <memory>
#include <string>

using namespace std;

enum class Kind { ATOM, NOT, AND, OR, IMP, BOX, DIAMOND };

struct Formula
{
    Kind k;
    string atom; // for ATOM
    shared_ptr<Formula> left, right;

    // ------------------------------------------------------------------------------------------------------------------
    Formula(Kind k) : k(k) 
    {}

    // ------------------------------------------------------------------------------------------------------------------
    static shared_ptr<Formula> Atom(const std::string& a) 
    {
        auto f = std::make_shared<Formula>(Kind::ATOM);
        f->atom = a;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Not(std::shared_ptr<Formula> p) 
    {
        auto f = std::make_shared<Formula>(Kind::NOT);
        f->left = p;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> And(std::shared_ptr<Formula> a, std::shared_ptr<Formula> b) 
    {
        auto f = std::make_shared<Formula>(Kind::AND);
        f->left = a;
        f->right = b;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
     static std::shared_ptr<Formula> Or(std::shared_ptr<Formula> a, std::shared_ptr<Formula> b) 
     {
        auto f = std::make_shared<Formula>(Kind::OR);
        f->left = a;
        f->right = b;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Imp(std::shared_ptr<Formula> a, std::shared_ptr<Formula> b) 
    {
        auto f = std::make_shared<Formula>(Kind::IMP);
        f->left = a;
        f->right = b;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Box(std::shared_ptr<Formula> p) 
    {
        auto f = std::make_shared<Formula>(Kind::BOX);
        f->left = p;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Diamond(std::shared_ptr<Formula> p) 
    {
        auto f = std::make_shared<Formula>(Kind::DIAMOND);
        f->left = p;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    std::string str() const 
    {
        switch (k) 
        {
            case Kind::ATOM: return atom;
            case Kind::NOT:  return "~" + left->str();
            case Kind::AND:  return "(" + left->str() + " & " + right->str() + ")";
            case Kind::OR:      return "(" + left->str() + " | " + right->str() + ")";
            case Kind::IMP:     return "(" + left->str() + " -> " + right->str() + ")";
            case Kind::BOX:     return "[]" + left->str();
            case Kind::DIAMOND: return "<>" + left->str();
        }
        return "?";
    }

};