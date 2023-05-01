#include "warcraft.h"
#include "iostream"

int main()
{
    int t;
    std::cin>>t;
    while(t--)
    {
        init();
        game();
    }
    return 0;
}