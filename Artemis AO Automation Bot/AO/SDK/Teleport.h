#ifndef _TELEPORT_H_
#define _TELEPORT_H_

#include "N3Engine.h"
#include "Entity/LocalPlayer.h"

class Teleport
{
private:
    typedef BOOL (__stdcall *StartTeleportTry_t)(N3Engine *inst, int a2_0,
                   int GetZoneRet, LocalPlayer *lPlayer);


public:
    static BOOL TryTeleport()
    {
        N3Engine *engineInst = N3Engine::GetInstance();
        HMODULE GCHandle = GetModuleHandle("GameCode");
        StartTeleportTry_t TryTeleport_o;
        TryTeleport_o = (StartTeleportTry_t) GetProcAddress(GCHandle,
                    "?StartTeleportTry@n3EngineClientAnarchy_t@@QAE_NXZ");

        return TryTeleport_o(engineInst, 0, 0, engineInst->GetLocalPlayer());
    }



};

#endif