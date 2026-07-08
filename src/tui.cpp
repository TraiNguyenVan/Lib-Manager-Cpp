// oh shit i have to ask chatgpt to write this, does it count as vibecoded 🥀
#include "tui.hpp"
#include <library.hpp>

#include <sstream>

TUI::TUI(Library &Lib, Api &api) : Lib(Lib), api(api)
{

    Api api1(Lib);

    input = CatchEvent(input, [&](Event event)
                       { return handle_input_event(event, input_value, log, quit_requested); });
    renderer = Renderer(input, [&]
                        { return BuildUI(log, input); });
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    app = Renderer(renderer, [&]
                   {if (quit_requested) screen.Exit(); return renderer->Render(); });
    screen.Loop(app);
}

// most of the logics live here, anything else just UI components
string TUI::HandleCommand(const string &command)
{
    if (command.empty())
        return "";

    // load library from database.txt
    if (command.rfind("/load ", 0) == 0) // /load <file>
    {
        return api.load(command);
    }
    // save library to file
    if (command.rfind("/save ", 0) == 0) // /save <file>
    {
        return api.save(command);
    }
    if (command == "/clear")
        return "__CLEAR__";
    if (command == "/help")
        return "Available commands: /help, /load, /save /clear, /quit";
    return "You typed: " + command;
}

auto TUI::handle_input_event(Event event, string &input_value, deque<string> &log, bool &quit_requested) -> bool
{
    // check if the key pressed is "enter" key or not so it can either
    // execute the command or just keep waiting for user to finish typing their command
    if (event != Event::Return)
    {
        return false;
    }
    // well, do nothing
    if (input_value.empty())
    {
        return true;
    }
    // at this point we just print the unknow command out
    log.push_back(">" + input_value);
    if (input_value == "/quit" || input_value == "/exit")
    {
        quit_requested = true;
    }
    else
    {
        // make response from coresponse input value
        string response = HandleCommand(input_value);
        if (response == "__CLEAR__")
        {
            log.clear();
        }
        else if (!response.empty())
        {
            log.push_back(response);
        }
    }
    // no condition meets, assume its an "enter" key,
    input_value.clear();
    return true;
};

Element TUI::BuildUI(deque<string> &log, Component &input)
{
    // limit the log size by popping it:)
    while (log.size() > 500)
    {
        log.pop_front();
    }

    Elements lines;
    for (auto &line : log)
    {
        lines.push_back(text(line));
    }

    Element content_pane = vbox(std::move(lines));
    content_pane = frame(content_pane);             // make it scrollable
    content_pane = vscroll_indicator(content_pane); // add the scrollbar
    content_pane = border(content_pane);

    Element input_bar = border(input->Render());

    Element body = vbox({
        flex(content_pane),
        input_bar,
    });

    Element ui = window(text(" Lib_manager "), body);
    return flex(ui);
}
