// #include <iostream>
// #include <stdio.h>
#include <bits/stdc++.h>
#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Error";
        return 1;
    }
    // 
    // return 0;
    string input = argv[1];   
    cout << input << endl;
    // std::string input;
    // std::cout << "Enter a formula: ";
    // std::getline(std::cin, input);

    try 
    {
        Parser p(input);
        auto f = p.parseAnd();
        std::cout << "Parsed formula: " << f->str() << "\n";
    } 
    catch (const std::exception& e) 
    {
        std::cerr << "Parse error: " << e.what() << "\n";
    }
}