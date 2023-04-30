#include "algorithm"
#include "cstdio"
#include "pos.h"
#include "warrior.h"

int CurHour = 0;
City *citys;
static std::vector<warrior *> AllWarrior;
static std::vector<Lion *> AllLion;
static std::vector<Wolf *> AllWolf;

bool cmp(warrior *a, warrior *b)
{
    if (b->vis() == 0)
        return true;
    if (a->vis() == 0)
        return false;
    return a->getpos() < b->getpos();
}

void delete_lion()
{
    for (auto x: AllLion)
        if (x->vis())
            if (x->isrun())
            {
                printf("%03d:05 %s lion %d ran away\n", CurHour, (x->getcamp() == RED ? "red" : "blue"), x->getid());
                x->vis() = false;
            }
}

void march()
{
    for (auto x: AllWarrior)
        if (x->vis())
            x->march();
}

void create()
{

}

void game()
{
}
