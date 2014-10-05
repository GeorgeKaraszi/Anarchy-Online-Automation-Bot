/*
1.Check Health and Nano
1.1:Read Stats
1.2:Preform actions if needed
1.2.1:Determined if health/nano pod is in inventory
1.2.2:Determined if health is to be a spell or item base

2.Check if being attacked

3.Attack */

#include "ArtemisBot.h"

//-----------------------------------------------------------------------------------
//Defined healing keyboard-keys that get sent to the game.

#define HPMPSIT_KEY  0x35 // 5 on keyboard
#define FIRSTAID_KEY 0x36 // 6 on keyboard


//-----------------------------------------------------------------------------------
//Initialization of the main bot program
ArtemisBot::ArtemisBot(int minHP, int minMP)
{
    _MainEvent       = MainEvent::StatCheack;
    _SecoundEvent    = SecoundEvent::Ignore;
    this->minHP      = minHP;
    this->minMP      = minMP;
    _FightManager    = (FightManager*)this;
    player           = N3Engine::GetInstance()->GetLocalPlayer();
    AOHandle         = GetWindowsHWND("Anarchy Online - ", player->GetName());


}


//-----------------------------------------------------------------------------------
//De-Initialization, if needed.

ArtemisBot::~ArtemisBot()
{

}

//-----------------------------------------------------------------------------------
//Checks the players health, to make sure he is in good standing

BOOL ArtemisBot::CheckHealthStats()
{
    if (player->GetHealthPercent() <= minHP)
    {
        _SecoundEvent = SecoundEvent::HP_Heal;
        return false;
    }

    if (player->GetNanoPercent() <= minMP)
    {
        _SecoundEvent = SecoundEvent::MP_Heal;
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------------
//Heals the player depending on his attacking status

VOID ArtemisBot::HealPlayer(BOOL playerIsFighting)
{
    if (_SecoundEvent == SecoundEvent::HP_Heal)
    {
        if (playerIsFighting)
        {
            SendMessage(AOHandle, WM_KEYDOWN, (WPARAM) FIRSTAID_KEY, 0);
            SendMessage(AOHandle, WM_KEYUP, (WPARAM) FIRSTAID_KEY, 0);
        }
        else
        {
            player->ChangeAnimation(AnimationType::SIT);
            SendMessage(AOHandle, WM_KEYDOWN, (WPARAM) HPMPSIT_KEY, 0);
            SendMessage(AOHandle, WM_KEYUP, (WPARAM) HPMPSIT_KEY, 0);
        }
    }

    if (_SecoundEvent == SecoundEvent::MP_Heal)
    {
        if (playerIsFighting)
        {
        }
        else
        {

            player->ChangeAnimation(AnimationType::SIT);
            SendMessage(AOHandle, WM_KEYDOWN, (WPARAM) HPMPSIT_KEY, 0);
            SendMessage(AOHandle, WM_KEYUP, (WPARAM) HPMPSIT_KEY, 0);
        }
    }

    _SecoundEvent = SecoundEvent::Ignore;
}

//-----------------------------------------------------------------------------------
//Main Loop that handles all the bot functions and attributes

BOOL ArtemisBot::StartBot()
{
    while (_MainEvent != MainEvent::Shutdown)
    {
        player = N3Engine::GetInstance()->GetLocalPlayer();

        switch (_MainEvent)
        {
        case Attacking:
            _MainEvent = _FightManager->ManageFighting();

            break;
        case StatCheack:
            if (CheckHealthStats() == true)
            {
                _MainEvent = MainEvent::TargetFinding;
            }
            else
            {
                _MainEvent  = MainEvent::Healing;
            }
            

            break;
        case Moving:
            break;
        case TargetFinding:
            _MainEvent = _FightManager->SetAndAttackTarget();
            break;
        case Healing:
            HealPlayer(player->IsAttacking());
            _MainEvent = MainEvent::StatCheack;
            break;
        default:
            break;
        }


        Sleep(500);
    }

    return true;
}
