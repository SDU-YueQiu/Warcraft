#include "warrior.h"
#include "cstdio"
#include "cstring"
extern City *citys;
extern int K;

extern const char WarriorName[5][10];

weapon::weapon(_WEAPON type, const warrior &w)
{
    if (type == sword)
    {
        id = 0;
        ATKtoOther = w.getATK() * 2 / 10;
        ATKtoSelf = 0;
        NumOfUse = -1;
    } else if (type == bomb)
    {
        id = 1;
        ATKtoOther = w.getATK() * 4 / 10;
        ATKtoSelf = w.getATK() * 2 / 10;
        NumOfUse = 1;
    } else if (type == arrow)
    {
        id = 2;
        ATKtoOther = w.getATK() * 3 / 10;
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
    ATK = InitATK[type];
    Health = InitHealth[type];
    if (type == dragon || type == lion)
        weapons.push_back(weapon(_WEAPON(id % 3), *this));
    if (type == ninja)
    {
        weapons.push_back(weapon(_WEAPON(id % 3), *this));
        weapons.push_back(weapon(_WEAPON((id + 1) % 3), *this));
    }
    if (type == iceman)
        weapons.push_back(weapon(_WEAPON(id % 3), *this));
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
        citys[pos].clear();
        pos++;
        citys[pos].add(camp, id);
    }
}

void warrior::report_march()
{
    printf("%03d:10 %s %s %d marched to city %d with %d elements and force %d\n",
           CurHour, CampName[camp], WarriorName[type], id, pos, ATK, Health);
}

Lion::Lion(_WARRIOR ttype, int curid, _CAMP tcamp) : warrior(ttype, curid, tcamp) {}

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

int warrior::fight(warrior &b)
{
    sortWeapon();
    b.sortWeapon();

}