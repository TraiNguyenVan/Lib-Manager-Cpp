#include "library.hpp"
#include "tui.hpp"
#include "api.hpp"

using namespace std;

int main()
{
    Library Lib1{1, "Library"};
    Api api1(Lib1);
    TUI tui1(Lib1, api1);

    return 0;
}