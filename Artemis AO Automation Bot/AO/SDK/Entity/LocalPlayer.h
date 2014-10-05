#ifndef _LOCALPLAYER_H_
#define _LOCALPLAYER_H_
#include "NPC.h"
#include "Attributes/Targeting.h"


class LocalPlayer : public Entity
{
private:

public:
    //------------------------------------------------------------------------------
    //Change the current animation

    void ChangeAnimation(AnimationType aType)
    {
        Animation *MyAnimation = this->GetTransformingClass()->GetAnimation();
        MyAnimation->SetCurrentMovementMode(aType);
    }

    //------------------------------------------------------------------------------
    //Return the information about the current animation

    AnimationType GetAnimation()
    {
        Animation *MyAnimation = this->GetTransformingClass()->GetAnimation();
        return MyAnimation->GetCurrentMovementMode();
    }

    //------------------------------------------------------------------------------
    //Get Attack action class 0x1d4 -> 0x44  is attacking
    //if 0x44 == 1 it is not attacking, else attacking is occurring

    __forceinline BOOL IsAttacking()
    {
        return GetAttackingClass()->isAttacking();
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

    //------------------------------------------------------------------------------
    //Gives the status of whether an NPC is in range of your attack

    __forceinline BOOL IsTargetInWeaponRange(NPC *target)
    {
        int myWeaponRange  = this->GetCurrentStat(WeaponRange, 2);
        FLOAT LocalRadius  = this->GetTransformingClass()->Radius();
        FLOAT TargetRadius = target->GetTransformingClass()->Radius();
        FLOAT DistanceArea = GetDistance(target) - LocalRadius - TargetRadius;

        if (DistanceArea > myWeaponRange)
        {
            return false;
        }


        return true;
    }

    //-------------------------------------------------------------------------------
    //Get the distance between the local player and the target

    __forceinline FLOAT GetDistance(Entity *target)
    {
        FVector LocalVec3  = this->GetTransformingClass()->GetPosition();
        FVector TargetVec3 = target->GetTransformingClass()->GetPosition();
        FVector DistanceVec = LocalVec3 - TargetVec3;
        FLOAT DistanceArea = C_FVector::VectorDotProduct(&DistanceVec, &DistanceVec);

        return sqrt(DistanceArea);
    }

    //-------------------------------------------------------------------------------
    //Set the current target for the local user

    __forceinline VOID SetCurrentTarget(IDENT_T *target)
    {
        Target::GetInstance()->SetSelectedTarget(target);
    }
};
#endif