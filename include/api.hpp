// This file responsible for translate the input from the TUI
// to specific method with the Library

#ifndef API_HPP
#define API_HPP

#include <string>
#include "library.hpp"

using namespace std;

class Api
{
public:
    Api(Library &Lib);
    string load(const string &command);
    string save(const string &command);

private:
    Library Lib;
};

#endif