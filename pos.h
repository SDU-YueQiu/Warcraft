#ifndef _POS_H
#define _POS_H

extern int CurHour;

enum _WARRIOR
{
    dragon,
    ninja,
    iceman,
    lion,
    wolf
};
const char WarriorName[5][10] = {
        "dragon",
        "ninja",
        "iceman",
        "lion",
        "wolf"};

enum _WEAPON
{
    sword,
    bomb,
    arrow
};
const char WeaponName[3][10] = {
        "sword",
        "bomb",
        "arrow"};
enum _CAMP
{
    RED,
    BLUE
};
const char CampName[2][5] = {
        "red",
        "blue"};


const _WARRIOR makelist[2][5] = {
        {iceman, lion, wolf, ninja, dragon},
        {lion, dragon, ninja, iceman, wolf}};
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
    void clearRED() { RedID = -1; }
    void clearBLUE() { BlueID = -1; }
    void add(_CAMP camp, int tid)
    {
        if (camp == RED)
            RedID = tid;
        else
            BlueID = tid;
    }
    int getid() { return id; }
    int redid() { return RedID; }
    int blueid() { return BlueID; }
    City(int i) : id(i), RedID(-1), BlueID(-1) {}
};

class Command
{
private:
    _CAMP camp;
    int bioelement;
    int curid;
    bool isStop;

public:
    Command(){};
    Command(_CAMP cp, int bio) : camp(cp), bioelement(bio), curid(0) {}
    void report_bio();
    warrior *create();
    void init(_CAMP);
};


#endif