#ifndef _NPC_H_
#define _NPC_H_

#include "Entity.h"

class NPC : public Entity
{
private:

public:

    //-------------------------------------------------------------------------------
    //Conditional check if object is an NPC

    __forceinline BOOL IsNPC()
    {
        return IsNPC(this);
    }

    //-------------------------------------------------------------------------------
    //Conditional check if object is an NPC

    __forceinline static BOOL IsNPC(Entity *entity)
    {

        //Honestly don't understand why you gotta check a stat function on a player,
        //then AND that result with 0x800000. But thats AO logic: "lets not rely on a 
        //simple byte flag" >_>
        byte NPCFlag = *(byte*) ((DWORD) entity + 0x21C);

        if (NPCFlag || entity->GetCurrentStat(NPCStatus, 2) & 0x800000)
        {
            return true;
        }

        return false;
    }

    //-------------------------------------------------------------------------------
    //Is Attacking an entity

    __forceinline BOOL IsAttacking()
    {
        if (IsNPC())
        {
            return GetAttackingClass()->isAttacking();
        }
    }

    //------------------------------------------------------------------------------
    //Check if NPC is alive

    __forceinline BOOL IsDead()
    {
        DWORD npcValue = 0;

        if (VerifyGoodEntity() == false)
            return true;

        if (IsNPC())
        {
            npcValue = *(DWORD*) ((DWORD)this + 0x138);

            if ((npcValue >> 4) & 1)
            {
                return true;
            }
        }

        return false;
    }

    //------------------------------------------------------------------------------
    //Returns the percentage of health the player has left

    __forceinline INT GetHealthPercent()
    {
        int mHealth = GetCurrentStat(MaxHealth);
        int cHealth = GetCurrentStat(CurrentHealth);

        return (int) ((cHealth / mHealth) * 100);
    }

    //------------------------------------------------------------------------------
    //Returns the percentage of nano the player has left

    __forceinline INT GetNanoPercent()
    {
        int mNano = GetCurrentStat(MaxNano);
        int cNano = GetCurrentStat(CurrentNano);

        return (int) ((cNano / mNano) * 100);
    }


};


#endif