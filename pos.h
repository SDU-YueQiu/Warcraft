#ifndef _POS_H
#define _POS_H

#include "declears.h"

class City
{
private:
    int RedID;
    int BlueID;
    int id;

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