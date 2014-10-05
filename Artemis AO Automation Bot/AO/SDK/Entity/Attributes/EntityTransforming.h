#ifndef _OBJECTTRANSFORMING_H_
#define _OBJECTTRANSFORMING_H_

#include "../../../F_Vector/C_FRotation.h"
#include "../../../F_Vector/C_FVector.h"

#include "Animation.h"

class EntityTransforming
{
public:
	//------------------------------------------------------------------------------
	//Get object location
	__forceinline FVector GetPosition()
	{
		return *(FVector*) ((DWORD)this + 0x58);
	}

	//------------------------------------------------------------------------------
	//Get object rotation position
	__forceinline FRotator GetRotation()
	{
		return *(FRotator*) ((DWORD)this + 0xC0);
	}

	//------------------------------------------------------------------------------
	//Set object location

	__forceinline void SetPosition(FVector location)
	{
		*(FVector*) ((DWORD)this + 0x58) = location;
	}

	//------------------------------------------------------------------------------
	//Set object rotation
	__forceinline void SetRotation(FRotator rotation)
	{
		*(FRotator*) ((DWORD) this + 0xC0) = rotation;
	}

    //------------------------------------------------------------------------------
    //Gets the Animation class from the transforming class

    __forceinline Animation* GetAnimation()
    {
        return *(Animation**) ((DWORD)this + 0x178);
    }

    //------------------------------------------------------------------------------
    //Gets the radius that the entity fills.

    __forceinline FLOAT Radius()
    {
        return *(FLOAT*) ((DWORD)this + 0x30);
    }

    //------------------------------------------------------------------------------
    //Sets the entities radius to the given value.

    __forceinline void SetRadius(float radius)
    {
        *(FLOAT*) ((DWORD)this + 0x30) = radius;
    }

};

#endif // !_OBJECTTRANSFORMING_H_