#include "iostream"
#include "warcraft.h"
#include "cstdio"

int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        init();
        game();
    }
    return 0;
}