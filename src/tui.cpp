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
    // Add event handling on the renderer to support scrolling the log pane
    renderer = CatchEvent(renderer, [&](Event event)
                          {
        const float small = 0.02f;
        const float big = 0.20f;
        // keyboard
        if (event == Event::ArrowUp) {
            scroll_y = max(0.f, scroll_y - small);
            return true;
        }
        if (event == Event::ArrowDown) {
            scroll_y = min(1.f, scroll_y + small);
            return true;
        }
        if (event == Event::PageUp) {
            scroll_y = max(0.f, scroll_y - big);
            return true;
        }
        if (event == Event::PageDown) {
            scroll_y = min(1.f, scroll_y + big);
            return true;
        }
        // mouse wheel
        if (event.is_mouse()) {
            using Mouse = ftxui::Mouse;
            if (event.mouse().button == Mouse::WheelUp) {
                scroll_y = max(0.f, scroll_y - small);
                return true;
            }
            if (event.mouse().button == Mouse::WheelDown) {
                scroll_y = min(1.f, scroll_y + small);
                return true;
            }
        }
        // let other handlers (like input) process the event
        return false; });
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
    if (command.rfind("/load ", 0) == 0)
    {
        return api.load(command);
    }
    // save library to file
    if (command.rfind("/save ", 0) == 0)
    {
        return api.save(command);
    }
    // list books, students, whatever
    if (command.rfind("/list ", 0) == 0)
    {
        return api.list(command);
    }
    if (command == "/clear")
        return "__CLEAR__";
    // gonna make this expandable soon
    if (command == "/help")
        return api.help(command);
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
    // while (log.size() > 500)
    // {
    //     log.pop_front();
    // }

    Elements lines;
    // for (auto &line : log)
    // {
    //     lines.push_back(text(line));
    // }

    for (auto &line : log)
    {
        size_t pos = 0;
        while (true)
        {
            auto next = line.find('\n', pos);
            lines.push_back(text(line.substr(pos, next - pos)));
            if (next == string::npos)
                break;
            pos = next + 1;
        }
    }

    Element content_pane = vbox(std::move(lines));
    // apply vertical scroll position so renderer's events control visible slice
    content_pane = content_pane | focusPositionRelative(0.0, scroll_y);
    content_pane = content_pane | vscroll_indicator | frame | border;

    Element input_bar = border(input->Render());

    Element body = vbox({
        flex(content_pane),
        input_bar,
    });

    Element ui = window(text(" Lib_manager "), body);
    return flex(ui);
}
