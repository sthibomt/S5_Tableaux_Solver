// #include <stdio.h>
// #include <bits/stdc++.h>
#include <iostream>
#include "Parser.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "Error";
        return 1;
    }    
    
    string input = argv[1];   
    cout << input << endl;
  try 
    {
        Parser p(input);
        // auto f = p.parseAnd();
        auto f = p.parse();
        cout << "Parsed formula: " << f->str() << "\n";
    } 
    catch (const std::exception& e) 
    {
        cerr << "Parse error: " << e.what() << "\n";
    }
}