#ifndef _WARRIOR_H
#define _WARRIOR_H

#include "pos.h"
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
    _CAMP camp;
    int pos;
    int curweapon;
    void useweapon(warrior &b);

public:
    warrior(_WARRIOR ttype, int curid);
    int getATK() const { return ATK; }
    virtual ~warrior(){};
    void march();
    int fight(warrior &b);
    bool &vis() { return visble; }
    _CAMP getcamp() { return camp; }
    int getid() { return id; }
    int getpos() { return pos; }
};

class Lion : public warrior
{
private:
    bool WillRun;
    int loyalty;

public:
    Lion(_WARRIOR ttype, int curid);
    bool isrun();
    bool check();
};

class Wolf : public warrior
{
public:
    Wolf(_WARRIOR ttype, int curid) : warrior(ttype, curid){};
    void loot();
};

#endif