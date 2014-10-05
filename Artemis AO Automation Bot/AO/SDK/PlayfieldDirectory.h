#ifndef _PLAYFIELD_DIRECTORY_H_
#define  _PLAYFIELD_DIRECTORY_H_
#include <Windows.h>

class PlayfieldDirectory
{
private:
    //-------------------------------------------------------------------------------
    //TypeDefs for in-game calls
    typedef PlayfieldDirectory *(__cdecl* GetPlayfields_t)();
public:
    //-------------------------------------------------------------------------------
    //Gets the instance address to the Object Mapping directory
    static PlayfieldDirectory *GetInstance(char *moduleName = "N3")
    {
        HMODULE ObjectHandle = GetModuleHandle(moduleName);
        GetPlayfields_t PlayfieldMap;

        PlayfieldMap = (GetPlayfields_t) GetProcAddress(ObjectHandle,
            "?GetPlayfields@n3Playfield_t@@SAPBV?");

        return PlayfieldMap();
    }

};

#endif