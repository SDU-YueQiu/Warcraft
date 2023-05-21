#include "cstdio"
#include "warrior.h"

extern int CurHour;
extern int InitHealth[5];
extern int InitATK[5];
extern int K, N, M;

void Command::report_bio()
{
    printf("%03d:50 %d elements in %s headquarter\n", CurHour, bioelement, (camp == RED ? "red" : "blue"));
}

warrior *Command::create()
{
    if (isStop)
        return nullptr;
    curid++;
    _WARRIOR wartype = makelist[camp][CurHour % 5];
    if (bioelement - InitHealth[wartype] < 0)
    {
        isStop = true;
        return nullptr;
    }
    bioelement -= InitHealth[wartype];
    warrior *pt;
    if (wartype == lion)
        pt = new Lion(wartype, curid, camp, bioelement);
    else if (wartype == wolf)
        pt = new Wolf(wartype, curid, camp);
    else
        pt = new warrior(wartype, curid, camp);
    printf("%03d:00 %s %s %d born\n", CurHour, CampName[camp], WarriorName[pt->gettype()], curid);
    if (wartype == lion)
        printf("Its loyalty is %d\n", bioelement);
    return pt;
}

void Command::init(_CAMP c)
{
    camp = c;
    bioelement = M;
    curid = 0;
    isStop = false;
}