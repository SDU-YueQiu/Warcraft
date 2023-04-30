#ifndef _POS_H
#define _POS_H

extern int CurHour;

enum _WARRIOR
{
    iceman,
    lion,
    wolf,
    ninja,
    dragon
};

enum _WEAPON
{
    sword,
    bomb,
    arrow
};
enum _CAMP
{
    RED,
    BLUE
};

const _WARRIOR makelist[2][5] = {{iceman, lion, wolf, ninja, dragon}, {lion, dragon, ninja, iceman, wolf}};
class Command;
class City;
class warrior;
class weapon;
class Lion;
class Wolf;

class City
{
private:
    int RedID;
    int BlueID;
    int id;

public:
    void fight();
    void clear()
    {
        RedID = 0;
        BlueID = 0;
    }
    void add(_CAMP camp, int id)
    {
        if (camp == RED)
            RedID = id;
        else
            BlueID = id;
    }
};

class Command
{
private:
    _CAMP camp;
    int bioelement;
    int curid;

public:
    Command(){};
    Command(_CAMP cp, int bio) : camp(cp), bioelement(bio), curid(0) {}
    inline void report_bio();
    warrior *create();
};


#endif