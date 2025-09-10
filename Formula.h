#pragma once
#include <memory>
#include <string>
#include <unordered_map>

enum class Kind 
{ 
    ATOM, NOT, AND, OR, IMP, BOX, DIAMOND 
};

// ------------------------------------------------------------------------------------------------------------------
struct Formula 
{
    Kind k;
    std::string atom;
    std::shared_ptr<Formula> left, right;

    // ------------------------------------------------------------------------------------------------------------------
    Formula(Kind kk) : k(kk) 
    {}

    // ------------------------------------------------------------------------------------------------------------------
    // Factory methods
    static std::shared_ptr<Formula> Atom(const std::string& a) 
    {
        auto f = std::make_shared<Formula>(Kind::ATOM);
        f->atom = a;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Not(std::shared_ptr<Formula> l) 
    {
        auto f = std::make_shared<Formula>(Kind::NOT);
        f->left = l;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> And(std::shared_ptr<Formula> l, std::shared_ptr<Formula> r) 
    {
        auto f = std::make_shared<Formula>(Kind::AND);
        f->left = l;
        f->right = r;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Or(std::shared_ptr<Formula> l, std::shared_ptr<Formula> r) 
    {
        auto f = std::make_shared<Formula>(Kind::OR);
        f->left = l;
        f->right = r;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Imp(std::shared_ptr<Formula> l, std::shared_ptr<Formula> r) 
    {
        auto f = std::make_shared<Formula>(Kind::IMP);
        f->left = l;
        f->right = r;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Box(std::shared_ptr<Formula> l) 
    {
        auto f = std::make_shared<Formula>(Kind::BOX);
        f->left = l;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    static std::shared_ptr<Formula> Diamond(std::shared_ptr<Formula> l) 
    {
        auto f = std::make_shared<Formula>(Kind::DIAMOND);
        f->left = l;
        return f;
    }

    // ------------------------------------------------------------------------------------------------------------------
    // Pretty-printer
    std::string str() const 
    {
        switch (k) 
        {
            case Kind::ATOM:    return atom;
            case Kind::NOT:     return "~" + left->str();
            case Kind::AND:     return "(" + left->str() + " & " + right->str() + ")";
            case Kind::OR:      return "(" + left->str() + " | " + right->str() + ")";
            case Kind::IMP:     return "(" + left->str() + " -> " + right->str() + ")";
            case Kind::BOX:     return "[]" + left->str();
            case Kind::DIAMOND: return "<>" + left->str();
        }
        return "?"; // fallback
    }

    // ------------------------------------------------------------------------------------------------------------------
    // Evaluation under assignment (ignores modal ops for now)
    bool eval(const std::unordered_map<std::string, bool>& assignment) const 
    {
        switch (k) 
        {
            case Kind::ATOM:
                return assignment.at(atom);
            case Kind::NOT:
                return !left->eval(assignment);
            case Kind::AND:
                return left->eval(assignment) && right->eval(assignment);
            case Kind::OR:
                return left->eval(assignment) || right->eval(assignment);
            case Kind::IMP:
                return !left->eval(assignment) || right->eval(assignment);
            case Kind::BOX:     // TODO: modal eval later
            case Kind::DIAMOND: // TODO: modal eval later
                throw std::logic_error("Modal evaluation not yet implemented");
        }
        return false;
    }
};