#ifndef TUI_HPP
#define TUI_HPP

#include <iostream>
#include <string>
#include <deque>

#include "library.hpp"
#include "api.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;
using namespace std;

class TUI
{
public:
    // constructor
    TUI(Library &Lib, Api &api);

private:
    // yes this is what happen when we do a command
    string HandleCommand(const string &command);
    // this clearly read the keyboard for us
    auto handle_input_event(Event event, string &input_value, deque<string> &log, bool &quit_requested) -> bool;
    // yes, yes this does what it does
    Element BuildUI(deque<string> &log, Component &input);

    string input_value;
    deque<string> log;
    bool quit_requested = false;
    Component input = Input(&input_value, "");
    Component renderer;
    
    Component app;
    // honestly i dont really know where to put the actually lib object
    // while keeping it accessible from TUI object and anything other objects in the main function
    // if you come up with any idea that help the library object more universal, let me know
    string database;
    Library Lib;
    Api api;
};

#endif