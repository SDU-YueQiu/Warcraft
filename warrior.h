#ifndef _WARRIOR_H
#define _WARRIOR_H

#include "declears.h"
#include "vector"

int InitHealth[5];
int InitATK[5];

class weapon
{
private:
    int ATKtoOther;
    int ATKtoSelf;
    int NumOfUse;
    int id;

public:
    weapon(_WEAPON, const warrior &);
    bool operator<(const weapon &b) const;
};

class warrior
{
private:
    int id;
    std::vector<weapon> weapons;
    bool visble;
    _WARRIOR type;
    int ATK;
    int Health;
    virtual void useweapon(warrior &b);


public:
    warrior(_WARRIOR ttype, int curid);
    int getATK() const { return ATK; }
    virtual ~warrior(){};
    virtual void march();
    virtual void fight(warrior &b);
};

class lion : public warrior
{
private:
    bool WillRun;
    int loyalty;

public:
    lion(int curid);
    bool isrun();
    bool check();
};

class wolf : public warrior
{
public:
    void loot();
};

class iceman : public warrior
{
public:
    void march()
    {
        if ()
    }
};

#endif