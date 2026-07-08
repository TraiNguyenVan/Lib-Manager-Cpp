#include "library.hpp"
#include "tui.hpp"

using namespace std;

int main()
{
    Library Lib1{1, "Library"};

    TUI tui1(Lib1);
    return 0;
}