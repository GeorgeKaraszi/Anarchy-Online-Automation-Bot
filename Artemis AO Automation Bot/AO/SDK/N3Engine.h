#ifndef _N3ENGINE_H_
#define _N3ENGINE_H_


#include <Windows.h>
#include "../SDK/Entity/LocalPlayer.h"
#include "Camera.h"

class N3Engine
{
private:
    //------------------------------------------------------------------------------
    //Typedefs for in-game calls

    typedef N3Engine *(__cdecl *GetInstance_t)();
    typedef INT(__thiscall *DefaultAttack_t)(N3Engine *, IDENT_T *, BOOL);
public:

	//------------------------------------------------------------------------------
	//Obtains the instance pointer address to the in-game engine.

	static N3Engine *GetInstance(char *n3ModuleName = "N3")
	{
		HMODULE N3Handle = GetModuleHandle(n3ModuleName);
		GetInstance_t GetInstance_o;
		GetInstance_o = (GetInstance_t) GetProcAddress(N3Handle,
										"?GetInstance@n3Engine_t@@SAPAV1@XZ");
		return 	GetInstance_o();
	}

	//------------------------------------------------------------------------------
	//Gets the pointer address to the local character object
	__forceinline LocalPlayer *GetLocalPlayer()
	{
        return (LocalPlayer*) *(DWORD**) ((DWORD)this + 0x84);
	}

	//------------------------------------------------------------------------------
	//Gets the active camera instance for the current client

	__forceinline Camera *GetCamera()
	{
		return (Camera*) *(DWORD**) ((DWORD)this + 0x7C);
	}
	//-------------------------------------------------------------------------------
    //Tells the client to start attacking the target selected

    __forceinline INT StartDefaultAttack(IDENT_T *targetID)
    {
        HMODULE N3Handle = GetModuleHandle("GameCode");
        DefaultAttack_t DefaultAttack_o;
        DefaultAttack_o = (DefaultAttack_t) GetProcAddress(N3Handle, 
            "?N3Msg_DefaultAttack@n3EngineClientAnarchy_t@@QBEXABVIdentity_t@@_N@Z");


        return DefaultAttack_o(this, targetID, false);
    }
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------

};

#endif // !_N3ENGINE_H_
