#ifndef WARCRAFT_DECLEARS_H
#define WARCRAFT_DECLEARS_H

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

#endif//WARCRAFT_DECLEARS_H
