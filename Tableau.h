#pragma once
#include "Formula.h"
#include <vector>
#include <memory>
#include <iostream>

using namespace std;

struct TableauNode 
{
    vector<shared_ptr<Formula>> formulas;
    bool closed = false;

    // ------------------------------------------------------------------------------------------------------------------
    TableauNode(std::initializer_list<std::shared_ptr<Formula>> init) : formulas(init) 
        {}
    
    // ------------------------------------------------------------------------------------------------------------------
    void print() const 
    {
        cout << (closed ? "[CLOSED] " : "[OPEN] ") << "{ ";
        for (auto& f : formulas) 
        {
            cout << f->str() << " ";
        }
        cout << "}" << endl;
    }
};
