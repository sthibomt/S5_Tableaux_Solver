#include <iostream>
#include <string>
#include <unordered_map>
#include "Parser.h"
#include "Tableau.h"

// int main(int argc, char **argv)
int main()
{
    // if (argc < 1)
    // {
    //     cout << "Usage: ./s5_tableau \"<formula>\"" << endl;
    //     return 1;
    // }

    // Join args into single string (so spaces are allowed)
    // string input;
    // for (int i = 1; i < argc; i++)
    // {
        // if (i > 1)
            // input += " ";
        // input += argv[i];
    // }    

    // string input = argv[1];
    std::string input = "p&q";
    std::cout << "Input formula: " << input << std::endl;

    try
    {
        Parser p(input);
        auto f = p.parse();
        std::cout << "Parsed formula: " << f->str() << std::endl;

        // Example evaluation (propositional only, modal nodes throw)
        std::unordered_map<std::string, bool> assignment1 = {{"p", true}, {"q", false}};
        std::unordered_map<std::string, bool> assignment2 = {{"p", true}, {"q", true}};

        std::cout << "Eval under {p=true, q=false}: " << f->eval(assignment1) << std::endl;
        std::cout << "Eval under {p=true, q=true}: " << f->eval(assignment2) << std::endl;

        // Put formula into tableau
        TableauNode root({f});
        root.print();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Parse error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}