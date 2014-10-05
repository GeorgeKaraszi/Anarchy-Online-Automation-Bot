#include "FightManager.h"



//-----------------------------------------------------------------------------------
FightManager::FightManager()
{}


//-----------------------------------------------------------------------------------
//Generate a list of Target from the play zone the player is located

std::vector<NPC*>ObtainTargets(DWORD TypeID, int MaxDistance)
{
    PlayField *playArea = PlayField::GetInstance();
    std::vector<Entity*>Objects = playArea->GetObjectsByDistance(TypeID, MaxDistance);
    std::vector<NPC*> VerifiedNPC;

    for (int i = 0; i < Objects.size(); i++)
    {
        //Check for an error-free Entity class and that the Entity is an NPC
        if (Objects[i]->VerifyGoodEntity() && NPC::IsNPC(Objects[i]))
        {
            VerifiedNPC.push_back((NPC*) Objects[i]);
        }
    }

    return VerifiedNPC;



}


//-----------------------------------------------------------------------------------
//Sorts the target list by the distance of the the next target.

std::vector<NPC*>FightManager::QuickSort(std::vector<NPC*> TargetList, int left,
    int right)
{
    int i = left, j = right;
    int pivot         = player->GetDistance(TargetList[left + right / 2]);
    int LesserPivot   = player->GetDistance(TargetList[i]);
    int GreaterPivot  = player->GetDistance(TargetList[j]);
    NPC *Temp = NULL;

    while (i <= j)
    {
        while (LesserPivot < pivot)
        {
            LesserPivot = player->GetDistance(TargetList[i++]);
        }

        while (GreaterPivot > pivot)
        {
            GreaterPivot = player->GetDistance(TargetList[j--]);
        }

        if (i <= j)
        {
            Temp = TargetList[i];
            TargetList[i] = TargetList[j];
            TargetList[j] = Temp;
            i++;
            j--;
        }
    }

    if (left < j)
    {
        QuickSort(TargetList, left, j);
    }

    if (i < right)
    {
        QuickSort(TargetList, i, right);
    }

    return TargetList;
}

//-----------------------------------------------------------------------------------
//Sort the target list by the distance of each NPC target

std::vector<NPC*>FightManager::SortTargetListByDistance(std::vector<NPC*> TargetList)
{
    return QuickSort(TargetList, 0, TargetList.size());
}

//-----------------------------------------------------------------------------------
//Sets the target that we want to fight, and then attacks

INT FightManager::SetAndAttackTarget(std::vector<NPC*> TargetList)
{
    _SelectedTarget = TargetList[0];

    player->SetCurrentTarget(&_SelectedTarget->GetIdentity());
    return N3Engine::GetInstance()->StartDefaultAttack(&_SelectedTarget->GetIdentity());
}

//-----------------------------------------------------------------------------------
//Generates a list of targets and attacks the closest one.

MainEvent FightManager::SetAndAttackTarget()
{
    std::vector<NPC*>TargetList = ObtainTargets(50000, 30);

    if (TargetList.size() > 0)
    {
        TargetList = SortTargetListByDistance(TargetList);

        if (SetAndAttackTarget(TargetList) > 0)
        {
            if (player->GetAttackingClass()->isAttacking())
            {
                return MainEvent::Attacking;
            }
        }
        else
        {
            return MainEvent::Moving;
        }


    }

    //Just reset bot actions and make sure no healing action is required
    return MainEvent::StatCheack;
}

//-----------------------------------------------------------------------------------
//Handles the necessary actions during a fight between player and target

MainEvent FightManager::ManageFighting()
{
    if (player->GetAttackingClass()->isAttacking())
    {
        if (player->IsTargetInWeaponRange(_SelectedTarget) == false)
        {
            player->SetPosition(_SelectedTarget->GetPosition());

        }
        if (CheckHealthStats() == false)
        {
            HealPlayer(true);
        }
    }
    else if (_SelectedTarget->IsDead())
    {
        return MainEvent::StatCheack;
    }

    return MainEvent::Attacking;
}

