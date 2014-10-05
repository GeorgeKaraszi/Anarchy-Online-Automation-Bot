#ifndef _ATTACKING_H_
#define _ATTACKING_H_
#include <Windows.h>

class Attacking
{
public:
    //------------------------------------------------------------------------------
    //Entity is attacking if the flag does not equal 1
    __forceinline BOOL isAttacking()
    {
        return *(byte*) ((DWORD)this + 0x44) != 1;
    }

    //------------------------------------------------------------------------------
    //Gets the Type ID of an entity being attacked

    __forceinline DWORD GetAttackerTypeID()
    {
        if (isAttacking())
        {
            return *(DWORD*) ((DWORD)this + 0x4C);
        }

        return -1;
    }

    //------------------------------------------------------------------------------
    //Gets the UID of the entity being attacked

    __forceinline DWORD GetAttackerUID()
    {
        if (isAttacking())
        {
            return *(DWORD*) ((DWORD)this + 0x50);
        }

        return -1;
    }

};

#endif