/*
* VERY MESSY, But was the most simplest solution I could come up with.
*/

#ifndef _TARGETTING_H_
#define _TARGETTING_H_
#include <Windows.h>

class Target
{
private:
    //-------------------------------------------------------------------------------
    //Typedefs to in-game functions

    typedef Target *(__cdecl *GetTargetInstance_t)();
    typedef VOID *(__cdecl *GetInputInstance_t)();
    typedef VOID *(__cdecl *GetAFCMInstance_t)();

    typedef INT(__thiscall *SetCurrentTargetInput_t)(VOID*, IDENT_T*);
    typedef INT(__thiscall *SendTarget_t)(VOID *, INT, INT, IDENT_T *);

    //-------------------------------------------------------------------------------
    //Set a particular target

    __forceinline INT SetInputTarget(IDENT_T *target)
    {
        HMODULE GuiHandle = GetModuleHandle("GUI");

        //Get the input instance that handles GUI selection of an object
        GetInputInstance_t GetInputInstance_o = (GetInputInstance_t)
            GetProcAddress(GuiHandle, "?GetInstance@InputConfig_t@@SAPAV1@XZ");

        //Get the function address that assigns a target locally
        SetCurrentTargetInput_t SetCurrentTargetInput_o = (SetCurrentTargetInput_t)
            GetProcAddress(GuiHandle,
            "?SetCurrentTarget@InputConfig_t@@QAEXABVIdentity_t@@@Z");

        //Get Input class instance
        VOID *InputInstance = GetInputInstance_o();

        //Set up our target for the GUI
        return SetCurrentTargetInput_o(InputInstance, target);

    }

    //-------------------------------------------------------------------------------
    //Send the selected target to the AO server

    __forceinline INT SendInputTarget(IDENT_T *target)
    {
        HMODULE AFCMHandle = GetModuleHandle("AFCM");

        //Get the AFCM (Communication to server) Instance class.
        GetAFCMInstance_t GetAFCMInstance_o = (GetAFCMInstance_t) 
            GetProcAddress(AFCMHandle, "?GetInstance@AFCM@@SAPAV1@XZ");

        //Get the function that sends the target data to the server
        SendTarget_t SendTarget_o = (SendTarget_t) 
            GetProcAddress(AFCMHandle, "?Send@AFCM@@QAEXHHABVIdentity_t@@@Z");

        //Obtain the class instance of AFCM
        VOID *AFCMInstance = GetAFCMInstance_o();

        //Send target to server
        return SendTarget_o(AFCMInstance, 0x13, 0x127, target);
    }

    //-------------------------------------------------------------------------------

public:
    //-------------------------------------------------------------------------------
    //Get the instances to the Targeting module class

    static Target *GetInstance(char *n3ModuleName = "GUI")
    {
        HMODULE GUIHandle = GetModuleHandle(n3ModuleName);
        GetTargetInstance_t GetTargetInstance_o;
        GetTargetInstance_o = (GetTargetInstance_t) GetProcAddress(GUIHandle,
            "?GetInstance@TargetingModule_t@@SAPAV1@XZ");

        return 	GetTargetInstance_o();
    }

    //------------------------------------------------------------------------------
    //Set the Target

    __forceinline VOID SetSelectedTarget(IDENT_T *target)
    {      
        SetInputTarget(target);
        SendInputTarget(target);
    }




};

#endif