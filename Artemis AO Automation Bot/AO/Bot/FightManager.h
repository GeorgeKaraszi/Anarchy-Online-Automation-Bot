#ifndef _FIGHTMANAGER_H_
#define _FIGHTMANAGER_H_
#include "ArtemisBot.h"

class FightManager : ArtemisBot
{
private:
    NPC * _SelectedTarget;

    INT SetAndAttackTarget(std::vector<NPC*> TargetList);
    std::vector<NPC*>QuickSort(std::vector<NPC*> TargetList, int left, int right);
    std::vector<NPC*>SortTargetListByDistance(std::vector<NPC*> TargetList);
    std::vector<NPC*>ObtainTargets(DWORD TypeID, int MaxDistance);
public:
    FightManager();

    MainEvent SetAndAttackTarget();
    MainEvent ManageFighting();

};

#endif