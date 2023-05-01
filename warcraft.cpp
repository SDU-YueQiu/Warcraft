#include "algorithm"
#include "cstdio"
#include "pos.h"
#include "warrior.h"

int CurHour = 0;
int K;
City *citys;
static std::vector<warrior *> AllWarrior;
static std::vector<Lion *> AllLion;
Command CmdRed, CmdBlue;

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
    std::sort(AllWarrior.begin(), AllWarrior.end(), cmp);
    for (auto x: AllWarrior)
        if (x->vis())
            x->report_march();
}

void create()
{
    AllWarrior.push_back(CmdRed.create());
    if (AllWarrior[AllWarrior.size() - 1]->getcamp() == lion)
        AllLion.push_back(dynamic_cast<Lion *>(AllWarrior[AllWarrior.size() - 1]));
    AllWarrior.push_back(CmdBlue.create());
    if (AllWarrior[AllWarrior.size() - 1]->getcamp() == lion)
        AllLion.push_back(dynamic_cast<Lion *>(AllWarrior[AllWarrior.size() - 1]));
}

void game()
{

}
