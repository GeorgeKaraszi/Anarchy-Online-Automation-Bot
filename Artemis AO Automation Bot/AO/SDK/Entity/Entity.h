#ifndef _PLAYERCLASS_H_
#define _PLAYERCLASS_H_


#include <Windows.h>
#include "Attributes/EntityTransforming.h"
#include "Attributes/Attacking.h"
#include "../../F_Vector/C_FVector.h"
#include "../../F_Vector/C_FRotation.h"


//-----------------------------------------------------------------------------------
//Globals

//StatCode variables are the keys to the hash table structure of data each entity has
enum StatCode{
        MaxHealth     = 0x01,
        MaxNano       = 0xDD,
        CurrentHealth = 0x1B,
        CurrentNano   = 0xD6,
        CurrentLevel  = 0x36,
        AttackRating  = 0x16,
        NPCStatus     = 0xE0,
        WeaponRange   = 0x11F
};

//Each entity has an identity structure that tells the application what and who its is
struct IDENT_T
{
    DWORD EntityType; //Code that describes the object NPC/Player, item, etc
    DWORD EntityUID;  //Unique code that is given to each object
};

class Entity
{
private:
    virtual void Function0(); //Unknown

    //(WARNING player needs 're-alignment' to use)
    virtual int GetCurrentStatAttribute(DWORD Code, DWORD unknown);//0x4
public:

	//------------------------------------------------------------------------------
	//Gets the objects name

	__forceinline char* GetName()
	{
		byte NameTypeCheck = *(byte*)((DWORD)this + 0x164);

		//If the object name is greater then 16 bytes, 
        //the game assigns a pointer address to the address location
		if (NameTypeCheck == 16)
		{
            return (char*) *(DWORD**) ((DWORD)this + 0x154);
		}
		else
		{
			return (char*) ((DWORD)this + 0x154);
		}
	}

    //-------------------------------------------------------------------------------
    //Gets the structure that unique identifies a given object in game.

    __forceinline IDENT_T GetIdentity()
    {
        //ID = 50000 = player or NPC
        return *(IDENT_T*) ((DWORD)this + 0x14);
    }

    //-------------------------------------------------------------------------------
    //Determines if the Entity is visible to the local player

    __forceinline BOOL IsVisible()
    {
        return *(byte*)((DWORD)this + 0xC9);
    }

    //-------------------------------------------------------------------------------
    //Remove or see entities from the local play field. (This only hides them)

    __forceinline void SetVisibility(BOOL setVisible)
    {
        *(byte*) ((DWORD)this + 0xC9) = setVisible;
    }

    //-------------------------------------------------------------------------------
    //Gets the health of the object
    __forceinline int GetHealth()
    {
        return *(int*) ((DWORD)this + 0x218);
    }

	//-------------------------------------------------------------------------------
	//Gets the transforming class in the player object class

	__forceinline EntityTransforming *GetTransformingClass()
	{
		return (EntityTransforming*) *(DWORD**) ((DWORD)this + 0x50);
	}


    //-------------------------------------------------------------------------------
    //Gets the attacking class for each object

    __forceinline Attacking *GetAttackingClass()
    {
        return (Attacking*) *(DWORD**) ((DWORD)this + 0x1D4);
    }

	//-------------------------------------------------------------------------------
	//Get object location

	__forceinline FVector GetPosition()
	{
		return GetTransformingClass()->GetPosition();
	}

	//-------------------------------------------------------------------------------
	//Get object rotation

	__forceinline FRotator GetRotation()
	{
		return GetTransformingClass()->GetRotation();
	}

	//-------------------------------------------------------------------------------
	//Set object location

	__forceinline void SetPosition (float x, float y, float z)
	{
		SetPosition (FVector(x, y, z));
	}

	//-------------------------------------------------------------------------------
	//Set object location

	__forceinline void SetPosition (FVector location)
	{
		GetTransformingClass()->SetPosition(location);
	}

	//-------------------------------------------------------------------------------
	//Set object rotation

	__forceinline void SetRotation(float pitch, float yaw, float roll)
	{
		SetRotation(FRotator(pitch, yaw, roll));
	}

	//-------------------------------------------------------------------------------
	//Set object rotation

	__forceinline void SetRotation(FRotator rot)
	{
		GetTransformingClass()->SetRotation(rot);
	}


    //------------------------------------------------------------------------------
    //Returns the stat information that attributes to the character

    __forceinline INT GetCurrentStat(StatCode code, DWORD pushValue = 0)
    {
        //The needed VTable is located further down the player structure.
        Entity *vTableLoc = (Entity*) ((DWORD)this + 0x11C);
        return vTableLoc->GetCurrentStatAttribute((DWORD) code, pushValue);
    }

    //------------------------------------------------------------------------------
    //Error checking data to see if its use able

    BOOL VerifyGoodEntity()
    {
        if ((DWORD*)this == NULL)
            return false;

        if ((DWORD*)this->GetTransformingClass() == NULL)
            return false;

        return true;
    }
};

#endif