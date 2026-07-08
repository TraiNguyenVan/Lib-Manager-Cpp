#include "api.hpp"
#include <sstream>

Api::Api(Library &Lib) : Lib(Lib)
{
}

string Api::load(const string &command)
{
    istringstream iss(command);
    string cmd, filename;
    iss >> cmd >> filename;
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