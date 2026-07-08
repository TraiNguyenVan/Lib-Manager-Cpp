#include "api.hpp"
#include <sstream>

Api::Api(Library &Lib) : Lib(Lib)
{
}

string Api::load(const string &command)
{
    istringstream iss(command); //
    string cmd, filename;       //     ---> this 3 lines of code should be made as a function do you agree?
    iss >> cmd >> filename;     //
    if (filename.empty())
        return "Usage: /load <filename>";
    return Lib.loadFromFile(filename) ? "Loaded from: " + filename : "Failed to load from: " + filename;
}

string Api::save(const string &command)
{
    istringstream iss(command);
    string cmd, filename;
    iss >> cmd >> filename;
    if (filename.empty())
        return "Usage: /save <filename>";
    return Lib.saveToFile(filename) ? "Saved to: " + filename : "Failed to save to: " + filename;
}

string Api::list(const string &command)
{
    istringstream iss(command);
    string cmd, arg;
    iss >> cmd >> arg;
    if (arg.empty())
        return "Usage: /list <books>\n";

    if (arg != "books")
        return string("Unknown list target: ") + arg + "\n";

    vector<string> records = Lib.makeRecords();
    if (records.empty())
        return "No books available.\n";

    string res = "Listing available books:\n";
    // rach record is stored as 4 lines: ISBN, title, author, copies
    for (int i = 0; i < records.size(); ++i)
    {
        istringstream rec(records[i]);
        string isbn, title, author, copies;
        getline(rec, isbn);
        getline(rec, title);
        getline(rec, author);
        getline(rec, copies);

        res += to_string(i + 1) + ". ";
        if (!title.empty())
            res += title;
        if (!author.empty())
            res += " — " + author;
        if (!isbn.empty())
            res += " (ISBN: " + isbn + ")";
        if (!copies.empty())
            res += " — copies: " + copies;
        res += "\n";
    }

    return res;
}

string Api::help(const string &command)
{
    istringstream iss(command);
    string cmd, arg;
    iss >> cmd >> arg;
    // handle basic case with /help, anything else like "/help [some function]" will need more code obviously
    if (arg == "")
    {
        string res = "Available commands: \n";
        for (int i = 0; i < commands.size(); ++i)
            res += "/" + commands[i] + "\n";
        return res;
    }
    return "No such option";
}