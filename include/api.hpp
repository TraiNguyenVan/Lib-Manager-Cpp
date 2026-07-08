// This file responsible for translate the input from the TUI
// to specific method with the Library

#ifndef API_HPP
#define API_HPP

#include <string>
#include "library.hpp"

using namespace std;

inline vector<string> commands = {
    "help", "load [filename]", "save [filename]", "list [option]", "clear", "quit"};

class Api
{
public:
    Api(Library &Lib);
    string load(const string &command);
    string save(const string &command);
    string list(const string &command);
    string help(const string &command);

private:
    Library Lib;
};

#endif