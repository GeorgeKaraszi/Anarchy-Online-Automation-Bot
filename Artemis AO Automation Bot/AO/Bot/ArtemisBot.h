#ifndef _ARTEMIS_H_
#define _ARTEMIS_H_

#include "FightManager.h"
#include "../SDK/N3Engine.h"
#include "../SDK/Playfield.h"
#include "../SDK/Entity/Entity.h"
#include "../SDK/Entity/NPC.h"
#include "../SDK/Entity/LocalPlayer.h"
#include "../Misc.h"
/*
1.Check Health and Nano
1.1:Read Stats
1.2:Preform actions if needed
1.2.1:Determined if health/nano pod is in inventory
1.2.2:Determined if health is to be a spell or item base

2.Check if being attacked

3.Attack */

//----------------------------------------------------------------------------------
//Event flags that are used to determine what event the bot is currently preforming

enum MainEvent
{
    Attacking,
    StatCheack,
    Healing,
    Animation,
    Moving,
    TargetFinding,
    Shutdown,
    Ignore
};

enum SecoundEvent
{
    HP_Heal,
    MP_Heal,
    FindNewSpot,
    Ignore
};

//-----------------------------------------------------------------------------------

class ArtemisBot
{
protected:
    LocalPlayer *player;
    BOOL CheckHealthStats();
    VOID HealPlayer(BOOL playerIsFighting);

private:
    MainEvent _MainEvent;       //Main Event the bot needs to preform
    SecoundEvent _SecoundEvent; //Another action the bot needs to perform with main
    FightManager *_FightManager;//Manages the actions the player does during attacks
    INT minHP;                  //Min HP before healing action is done
    INT minMP;                  //Min NP before healing action is done
    HWND AOHandle;              //Handle to the window for sending keys to

    
public:
    ArtemisBot(int minHP, int minMP);
    ~ArtemisBot();

    BOOL StartBot();
    BOOL StartBot(DWORD AttackType);
    BOOL StartBot(DWORD AttackType, DWORD *NPCList);

};


#endif