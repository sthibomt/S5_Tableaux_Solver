#pragma once
#include "Formula.h"
#include <vector>
#include <memory>
#include <iostream>

struct TableauNode 
{
    std::vector<std::shared_ptr<Formula>> formulas;
    bool closed = false;

    // ------------------------------------------------------------------------------------------------------------------
    TableauNode() = default;
    explicit TableauNode(std::initializer_list<std::shared_ptr<Formula>> init) : formulas(init)
    {}
    
    // ------------------------------------------------------------------------------------------------------------------
    void print() const 
    {
        std::cout << (closed ? "[CLOSED] " : "[OPEN] ") << "{ ";
        for (auto& f : formulas) 
        {
            std::cout << f->str() << " ";
        }
        std::cout << "}" << std::endl;
    }
};
