#include "algorithm"
#include "cstdio"
#include "iostream"
#include "pos.h"
#include "warrior.h"

int CurHour = 0;
int M, N, K, T;
std::vector<City> citys;
static std::vector<warrior *> AllWarrior;
static std::vector<Lion *> AllLion;
Command CmdRed, CmdBlue;
bool gameend = false;
int cnt = 0;
extern int InitHealth[5];
extern int InitATK[5];

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
                x->died();
            }
}

inline void sortwarrior()
{
    std::sort(AllWarrior.begin() + 1, AllWarrior.end(), cmp);
}

void march()
{
    for (auto x: AllWarrior)
        if (x->vis())
            x->march();
    sortwarrior();
    for (auto x: AllWarrior)
        if (x->vis())
            x->report_march();
    for (auto x: AllLion)
        if (x->vis())
            x->check();
}

void create()
{
    warrior *nw = CmdRed.create();
    if (nw != nullptr)
    {
        AllWarrior.push_back(nw);
        if (AllWarrior[AllWarrior.size() - 1]->gettype() == lion)
            AllLion.push_back(dynamic_cast<Lion *>(AllWarrior[AllWarrior.size() - 1]));
    }
    nw = CmdBlue.create();
    if (nw != nullptr)
    {
        AllWarrior.push_back(nw);
        if (AllWarrior[AllWarrior.size() - 1]->gettype() == lion)
            AllLion.push_back(dynamic_cast<Lion *>(AllWarrior[AllWarrior.size() - 1]));
    }
    sortwarrior();
}

void fight()
{
    for (auto x: citys)
    {
        if (x.redid() * x.blueid() == 0)
            continue;
        if (x.getid() % 2 == 0)
            AllWarrior[x.redid()]->fight(*AllWarrior[x.blueid()]);
        else
            AllWarrior[x.blueid()]->fight(*AllWarrior[x.redid()]);
    }
}

void wolf_loot()
{
    for (auto x: AllWarrior)
        if (x->vis() && x->gettype() == wolf)
        {
            Wolf *pw = dynamic_cast<Wolf *>(x);
            warrior *po;
            if (pw->getcamp() == BLUE)
                po = AllWarrior[citys[pw->getpos()].redid()];
            else
                po = AllWarrior[citys[pw->getpos()].blueid()];
            if (po->gettype() == nulwar)
                continue;
            else
                pw->loot(po);
        }
}

inline void rpt_bio()
{
    CmdRed.report_bio();
    CmdBlue.report_bio();
}

inline void rpt_weapon()
{
    for (auto x: AllWarrior)
        if (x->vis())
            x->report_weapon();
}

inline bool checktime(int minu)
{
    int hour = T / 60;
    int minute = T % 60;
    if (CurHour < hour)
        return false;
    if (CurHour > hour || minu > minute)
    {
        gameend = true;
        return true;
    }
}

void game()
{
    while (!gameend)
    {
        create();
        if (checktime(0))
            break;
        delete_lion();
        if (checktime(5))
            break;
        march();
        if (checktime(10))
            break;
        if (gameend)
            break;
        wolf_loot();
        if (checktime(35))
            break;
        fight();
        if (checktime(40))
            break;
        rpt_bio();
        if (checktime(50))
            break;
        rpt_weapon();
        if (checktime(55))
            break;
        ++CurHour;
    }
}

void init()
{
    citys.clear();
    for (auto x: AllWarrior)
        delete x;
    AllWarrior.clear();
    AllLion.clear();
    gameend = false;
    std::cin >> M >> N >> K >> T;
    for (int i = 0; i < 5; ++i)
        std::cin >> InitHealth[i];
    for (int i = 0; i < 5; ++i)
        std::cin >> InitATK[i];
    CmdRed.init(RED);
    CmdBlue.init(BLUE);
    CurHour = 0;
    citys.push_back(City(0));
    for (int i = 1; i <= N; ++i)
        citys.push_back(City(i));
    citys.push_back(City(N + 1));
    printf("Case %d:\n", ++cnt);
}