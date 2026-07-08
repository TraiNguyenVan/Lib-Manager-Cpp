#include <iostream>
#include "library.hpp"
#include <string>
#include <deque>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

string HandleCommand(const string &command)
{
  if (command.empty())
    return "";
  if (command == "/clear")
    return "__CLEAR__";
  if (command == "/help")
    return "Available commands: /help, /clear, /quit";
  return "You typed: " + command;
}