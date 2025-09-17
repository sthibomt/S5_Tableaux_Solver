#include <iostream>
#include <string>
#include <unordered_map>
#include "Parser.h"
#include "Tableau.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: ./s5_tableau \"<formula>\"" << endl;
        return 1;
    }

    // Join args into single string (so spaces are allowed)
    // string input;
    // for (int i = 1; i < argc; i++)
    // {
        // if (i > 1)
            // input += " ";
        // input += argv[i];
    // }

    string input = argv[1];
    cout << "Input formula: " << input << endl;

    try
    {
        Parser p(input);
        auto f = p.parse();
        cout << "Parsed formula: " << f->str() << endl;

        // Example evaluation (propositional only, modal nodes throw)
        unordered_map<string, bool> assignment1 = {{"p", true}, {"q", false}};
        unordered_map<string, bool> assignment2 = {{"p", true}, {"q", true}};

        cout << "Eval under {p=true, q=false}: " << f->eval(assignment1) << endl;
        cout << "Eval under {p=true, q=true}: " << f->eval(assignment2) << endl;

        // Put formula into tableau
        TableauNode root({f});
        root.print();
    }
    catch (const exception &e)
    {
        cerr << "Parse error: " << e.what() << endl;
        return 1;
    }

    return 0;
}