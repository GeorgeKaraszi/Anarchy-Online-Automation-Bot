#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <Windows.h>

enum AnimationType
{
    SLOW_SLIDE = 0,
    NO_MOVE = 1,
    WALKING = 2,
    RUNNING = 3,
    SWIMMING = 4,    //Cannot attack in this state
    CRAWLING = 5,
    SNEAK = 6,
    SUPER_HOVER = 7, //Will rubber-band
    SIT = 8,
    SIDE_STEP_ONLY = 9

};

class Animation
{
public:
    //------------------------------------------------------------------------------
    //Gets the current animation of the object

    __forceinline AnimationType GetCurrentMovementMode()
    {
        return *(AnimationType*) (DWORD*) ((DWORD)this + 0x4);
    }

    //------------------------------------------------------------------------------
    //Allows the setting of the animation to the current object

    __forceinline void SetCurrentMovementMode(AnimationType aType)
    {
        *(DWORD*) ((DWORD)this + 0x4) = aType;
    }

};


#endif