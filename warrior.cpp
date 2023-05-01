#include "warrior.h"
#include "cstdio"

extern City *citys;
extern int K;
extern int N;
extern const char WarriorName[5][10];
extern bool gameend;

int InitHealth[5];
int InitATK[5];

weapon::weapon(_WEAPON type)
{
    if (type == sword)
    {
        id = 0;
        ATKtoOther = 20;
        ATKtoSelf = 0;
        NumOfUse = -1;
    } else if (type == bomb)
    {
        id = 1;
        ATKtoOther = 40;
        ATKtoSelf = 20;
        NumOfUse = 1;
    } else if (type == arrow)
    {
        id = 2;
        ATKtoOther = 30;
        ATKtoSelf = 0;
        NumOfUse = 2;
    }
}

bool weapon::operator<(const weapon &b) const
{
    if (NumOfUse == 0)
        return false;
    if (b.NumOfUse == 0)
        return true;
    if (id != b.id)
        return id < b.id;
    return NumOfUse > b.NumOfUse;
}

warrior::warrior(_WARRIOR ttype, int curid, _CAMP tcamp) : type(ttype), id(curid), visble(true), camp(tcamp)
{
    if (type == nulwar)
        return;
    pos = (camp == RED ? 0 : N);
    ATK = InitATK[type];
    Health = InitHealth[type];
    if (type == dragon || type == lion)
        weapons.push_back(weapon(_WEAPON(id % 3)));
    if (type == ninja)
    {
        weapons.push_back(weapon(_WEAPON(id % 3)));
        weapons.push_back(weapon(_WEAPON((id + 1) % 3)));
    }
    if (type == iceman)
        weapons.push_back(weapon(_WEAPON(id % 3)));
}

void warrior::march()
{
    if (type == iceman)
        Health -= Health / 10;
    if (Health <= 0)
    {
        visble = false;
        return;
    }
    if (camp == RED)
    {
        citys[pos].clearRED();
        pos++;
        citys[pos].add(camp, id);
    } else
    {
        citys[pos].clearBLUE();
        pos--;
        citys[pos].add(camp, id);
    }
}

void warrior::report_march()
{
    if ((camp == RED && pos == N + 1) || (camp == BLUE && pos == 0))
    {
        gameend = true;
        printf("%03d:10 %s %s %d reached %s headquarter with %d elements and force %d",
               CurHour, CampName[camp], WarriorName[type], id, (camp == RED ? "blue" : "red"), Health, ATK);
    } else
        printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",
               CurHour, CampName[camp], WarriorName[type], id, pos, ATK, Health);
}

Lion::Lion(_WARRIOR ttype, int curid, _CAMP tcamp) : warrior(ttype, curid, tcamp), loyalty(K), WillRun(false) {}

warrior *Command::create()
{
    curid++;
    _WARRIOR wartype = makelist[camp][CurHour % 5];
    warrior *pt;
    if (wartype == lion)
        pt = new Lion(wartype, curid, camp);
    else if (wartype == wolf)
        pt = new Wolf(wartype, curid, camp);
    else
        pt = new warrior(wartype, curid, camp);
    printf("%03d:00 %s %s %d born\n", CurHour, CampName[camp], WarriorName[pt->gettype()], curid);
    if (wartype == lion)
        printf("Its loyalty is %d\n", K);
    return pt;
}

weapon warrior::belooted()
{
    weapon looted = weapons[0];
    weapons.erase(weapons.begin());
    return looted;
}

void Wolf::loot(warrior *b)
{
    if (b->gettype() == wolf)
        return;
    b->sortWeapon();
    int Fid = b->firstweapon().getID();
    int lootnum = 0;
    while (weaponNum() < 10 && b->firstweapon().getID() == Fid)
    {
        ++lootnum;
        addWeapon(b->belooted());
    }
    sortWeapon();
    printf("%03d:35 %s wolf %d took %d %s from %s %s %d in city %d\n",
           CurHour, CampName[getcamp()], getid(), lootnum, WeaponName[Fid], CampName[b->getcamp()], WarriorName[b->gettype()], b->getid(), getpos());
}

bool warrior::emptyWeapon()
{
    bool ret = true;
    for (auto x: weapons)
        if (x.getNum() > 0)
            ret = false;
    return ret;
}

void warrior::sortWeapon()
{
    curweaponID = 0;
    std::sort(weapons.begin(), weapons.end());
    while (weapons.size() > 0 && weapons[weapons.size() - 1].getNum() == 0)
        weapons.pop_back();
}

inline const int weapon::getATK2s(const warrior &a)
{
    if (a.gettype() == ninja)
        return 0;
    return ATKtoSelf * a.getATK() / 100;
}
inline const int weapon::getATK2o(const warrior &a) { return ATKtoOther * a.getATK() / 100; }
bool warrior::sumAtk()
{
    int sum2o = 0;
    int sum2s = 0;
    for (auto x: weapons)
    {
        if (x.getNum() != 0)
        {
            sum2o += x.getATK2o(*this);
            sum2s += x.getATK2s(*this);
        }
    }
    return sum2o || sum2s;
}

enum ending
{
    con,
    die,
    zeroWeapon,
    zeroATK,
    alldie
};

inline ending isend(warrior &a, warrior &b)
{
    ending flag = con;
    if (a.vis() ^ b.vis())
        flag = die;
    if (a.vis() & b.vis())
        flag = alldie;
    if (a.emptyWeapon() & b.emptyWeapon())
        flag = zeroWeapon;
    if (!a.sumAtk() && !b.sumAtk())
        flag = zeroATK;
    return flag;
}

void warrior::beAtk(int num)
{
    Health -= num;
    if (Health <= 0)
        visble = false;
}

void warrior::useweapon(warrior &b)
{
    while (curweaponID < weapons.size() && weapons[curweaponID].getNum() == 0)
        ++curweaponID;
    if (curweaponID == weapons.size())
    {
        curweaponID = 0;
        while (curweaponID < weapons.size() && weapons[curweaponID].getNum() == 0)
            ++curweaponID;
        if (curweaponID == weapons.size())
            return;
    }
    this->beAtk(weapons[curweaponID].getATK2s(*this));
    b.beAtk(weapons[curweaponID].getATK2o(*this));
    weapons[curweaponID].use();
    ++curweaponID;
}


void warrior::fight(warrior &b)
{
    sortWeapon();
    b.sortWeapon();
    _CAMP initialCamp = getcamp();
    int time = 1;
    while (isend(*this, b) == con)
    {
        if (time % 2)
            useweapon(b);
        else
            b.useweapon(*this);
        ++time;
    }
    ending end = isend(*this, b);
    if (end == die)
    {
        warrior &winner = (this->vis() ? *this : b);
        warrior &died = (this->vis() ? b : *this);
        printf("%03d:40 %s %s %d killed %s %s %d in city %d remaining %d elements\n",
               CurHour, CampName[winner.getcamp()], WarriorName[winner.gettype()], winner.getid(),
               CampName[died.getcamp()], WarriorName[died.gettype()], died.getid(),
               pos, Health);
        if (winner.type == dragon)
            printf("%03d:40 %s dragon %d yelled in city %d\n",
                   CurHour, CampName[winner.camp], winner.id, pos);
    } else if (end == alldie)
    {
        warrior &redw = (this->camp == RED ? *this : b);
        warrior &bluew = (this->camp == BLUE ? *this : b);
        printf("%03d:40 both red %s %d and blue %s %d died in city %d\n",
               CurHour, WarriorName[redw.type], redw.id, WarriorName[bluew.type], bluew.id, pos);
    } else
    {
        warrior &redw = (this->camp == RED ? *this : b);
        warrior &bluew = (this->camp == BLUE ? *this : b);
        printf("%03d:40 both red %s %d and blue %s %d were alive in city %d\n",
               CurHour, WarriorName[redw.type], redw.id, WarriorName[bluew.type], bluew.id, pos);
    }
}

void warrior::report_weapon()
{
    int sum[3] = {0};
    sortWeapon();
    for (auto x: weapons)
        sum[x.getID()]++;
    printf("%03d:55 %s %s %d has %d sword %d bomb %d arrow and %d elements\n",
           CurHour, CampName[camp], WarriorName[type], id, sum[sword], sum[bomb], sum[arrow], Health);
}

bool Lion::check()
{
    loyalty -= K;
    if (loyalty <= 0)
        WillRun = true;
    return check();
}

bool Lion::isrun()
{
    return WillRun;
}