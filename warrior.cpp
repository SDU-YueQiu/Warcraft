#include "warrior.h"

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

warrior::warrior(_WARRIOR ttype, int curid) : type(ttype), id(curid), visble(true)
{
    ATK = InitATK[type];
    Health = InitHealth[type];
    if (type == dragon)
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

}