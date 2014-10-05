#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../F_Vector/C_FVector.h"
#include "../F_Vector/C_FRotation.h"

//----------------------------------------------------------------------------------
//Enum's for identification

enum CameraViews { FRIST_PERSON = 0,
				   THRID_TRAIL  = 1, 
				   THRID_LOCK   = 2,
				   THRID_RUBBER = 3
};

class Camera
{
public:

    //------------------------------------------------------------------------------
    //Gets the Type of object ID of the selected Entity
    __forceinline DWORD GetSelectedTypeID()
    {
        return *(DWORD*) ((DWORD)this + 0x1E4);
    }

	//------------------------------------------------------------------------------
	//Gets the UID of the selected Object

	__forceinline DWORD GetSelectedUID()
	{
		return *(DWORD*) ((DWORD)this + 0x1E8);
	}

	//------------------------------------------------------------------------------
	//Gets the current view of the clients camera
	__forceinline CameraViews GetCurrentCameraView()
	{
		return *(CameraViews*) (byte*) ((DWORD)this + 0x1EC);
	}

	//------------------------------------------------------------------------------
	//Gets the camera location

	__forceinline FVector GetPosision()
	{
		return *(FVector*) ((DWORD)this + 0x1AC);
	}

	//------------------------------------------------------------------------------
	//Gets the camera rotation

	__forceinline FRotator GetRotation()
	{
		return *(FRotator*) ((DWORD)this + 0x1B8);
	}

    //------------------------------------------------------------------------------
    //Gets targets rotation

    __forceinline FRotator GetTargetRotation()
    {
        return *(FRotator*) ((DWORD)this + 0x16C);
    }

    //------------------------------------------------------------------------------
    //Gets the targets location

    __forceinline FVector GetTargetPosision()
    {
        return *(FVector*) ((DWORD)this + 0x160);
    }


};

#endif // !_CAMERA_H_
