/*
    Author:George Karaszi

    Description:A automated bot designed for the game Anarchy Online. The purpose of 
        the bot is to automate redundant tasks in the given game, like fighting NPC's 
        and picking up loot.

    Design Goal:The main design behind this bot is the use of functional prototypes 
        still stored in visible memory. These prototypes are found in memory with the 
        help of IDA Pro and OllyDBG. With these prototypes the bot is designed to call 
        these functions to gather information. This information can vary from player 
        or NPC locations to obtaining entire class objects of the given zone. Thus
        giving massive amount of power to controlling the game to our own desire.

     PS:Further information and how prototypes are used can be found in the SDK 
        portion of the project.

*/


#include <Windows.h>
#include <vector>
#include "SDK/Playfield.h"
#include "SDK/N3Engine.h"
#include "SDK/Entity/LocalPlayer.h"
#define NPC_PLAYER_PET 50000

//-----------------------------------------------------------------------------------
//Home brewed loop that does scripted botting events
//NOTE:Would be better to utilize in-game looping structure.

DWORD WINAPI StartHack()
{
    N3Engine *engine    = N3Engine::GetInstance();
    LocalPlayer *player = engine->GetLocalPlayer();
    PlayField *playArea = PlayField::GetInstance();
    std::vector<Entity*> EntityInArea;

    MessageBox(NULL, "Here", "here", MB_OK);
    __asm{
        INT 3; //Pause game here and trigger an exception that OLLYDBG will stop at
    }
    /*
    Things to do:
    1.Check Health and Nano
        1.1:Read Stats
        1.2:Preform actions if needed
            1.2.1:Determined if health/nano pod is in inventory
            1.2.2:Determined if health is to be a spell or item base

    2.Check if being attacked

    3.Attack
    
    */
    while (1)
    {
        EntityInArea = playArea->GetObjectsByDistance(NPC_PLAYER_PET, 25);

        for (int i = 0; i < EntityInArea.size(); i++)
        {
            if (EntityInArea[i]->VerifyGoodEntity() == false)
                continue;

            if (NPC::IsNPC(EntityInArea[i]))
            {
                player->SetCurrentTarget(&EntityInArea[i]->GetIdentity());
                engine->StartDefaultAttack(&EntityInArea[i]->GetIdentity());

                while (EntityInArea[i]->VerifyGoodEntity() && player->IsAttacking())
                {
                    if (player->IsTargetInWeaponRange((NPC*) EntityInArea[i]))
                    {
                        Sleep(3000);
                    }
                    else
                    {
                        FVector TargetLoc = EntityInArea[i]->GetTransformingClass()->GetPosition();
                        player->GetTransformingClass()->SetPosition(TargetLoc);
                    }
                }
                
            }

            Sleep(5000); //Give the CPU a break in this infinite loop!
        }

    }

    return true;

}


//----------------------------------------------------------------------------------
//Start of the dll

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE) StartHack, 0, 0, 0);
	}

	return TRUE;
}