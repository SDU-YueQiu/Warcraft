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
bool isGameEnd = false;
int cnt = 0;
extern int InitHealth[5];
extern int InitATK[5];

bool cmp(warrior *a, warrior *b);
void delete_lion();
void sortwarrior();
void march();
void create();
void fight();
void wolf_loot();
void rpt_bio();
void rpt_weapon();
bool checktime(int minu);

void init()
{
    citys.clear();
    for (auto x: AllWarrior)
        delete x;
    AllWarrior.clear();
    AllLion.clear();
    isGameEnd = false;
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

void game()
{
    while (!isGameEnd)
    {
        if (checktime(0))
            break;
        create();
        if (checktime(5))
            break;
        delete_lion();
        if (checktime(10))
            break;
        march();
        if (isGameEnd)
            break;
        if (checktime(35))
            break;
        wolf_loot();
        if (checktime(40))
            break;
        fight();
        if (checktime(50))
            break;
        rpt_bio();
        if (checktime(55))
            break;
        rpt_weapon();
        ++CurHour;
    }
}

bool cmp(warrior *a, warrior *b)
{
    if (b->vis() == 0)
        return true;
    if (a->vis() == 0)
        return false;
    if (a->getpos() != b->getpos())
        return a->getpos() < b->getpos();
    if (a->getcamp() == RED)
        return true;
    return false;
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
    std::sort(AllWarrior.begin(), AllWarrior.end(), cmp);
    while (AllWarrior.size() > 0 && !AllWarrior[AllWarrior.size() - 1]->vis())
        AllWarrior.pop_back();
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
        if (x.redid() == -1 || x.blueid() == -1)
            continue;
        warrior *redw = nullptr, *bluew = nullptr;
        for (auto w: AllWarrior)
            if (w->vis())
            {
                if (w->getcamp() == RED && w->getid() == x.redid())
                    redw = w;
                else if (w->getcamp() == BLUE && w->getid() == x.blueid())
                    bluew = w;
            }
        if (redw == nullptr || bluew == nullptr)
            continue;
        if (x.getid() % 2 == 1)
            redw->fight(*bluew);
        else
            bluew->fight(*redw);
    }
}

void wolf_loot()
{
    for (auto x: AllWarrior)
        if (x->vis() && x->gettype() == wolf)
        {
            Wolf *pw = dynamic_cast<Wolf *>(x);
            warrior *po = nullptr;
            if (pw->getcamp() == BLUE)
            {
                if (citys[pw->getpos()].redid() == -1)
                    continue;
                for (auto y: AllWarrior)
                    if (y->vis() && y->getcamp() == RED && y->getid() == citys[pw->getpos()].redid())
                        po = y;
            } else
            {
                if (citys[pw->getpos()].blueid() == -1)
                    continue;
                for (auto y: AllWarrior)
                    if (y->vis() && y->getcamp() == BLUE && y->getid() == citys[pw->getpos()].blueid())
                        po = y;
            }
            if (po == nullptr)
                continue;
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
    int sum = CurHour * 60 + minu;
    if (sum <= T)
        return false;
    isGameEnd = true;
    return true;
}