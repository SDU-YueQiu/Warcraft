#ifndef _POS_H
#define _POS_H

#include "warrior.h"

const _WARRIOR makelist[2][5] = {{iceman, lion, wolf, ninja, dragon}, {lion, dragon, ninja, iceman, wolf}};

enum _CAMP
{
    RED,
    BLUE
};

class City
{
private:
    int RedID;
    int BlueID;

public:
    void fight();
};

class Command
{
private:
    _CAMP camp;
    int bioelement;

public:
    Command(_CAMP cp, int bio) : camp(cp), bioelement(bio) {}
    inline void report_bio();
};


#endif