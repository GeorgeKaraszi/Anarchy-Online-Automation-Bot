#include "Misc.h"

//-----------------------------------------------------------------------------------
//Get all module related info, this will include the base DLL. 
//and the size of the module
MODULEINFO GetModuleInfo(char *szModule)
{
    MODULEINFO modinfo = { 0 };
    HMODULE hModule = GetModuleHandle(szModule);
    if (hModule == 0)
        return modinfo;
    GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
    return modinfo;
}

//----------------------------------------------------------------------------------
//Find a certain pattern of bytes in memory

DWORD FindPattern(char *module, char *pattern, char *mask)
{
    //Get all module related information
    MODULEINFO mInfo = GetModuleInfo(module);

    //Assign our base and module size
    //Having the values right is ESSENTIAL, this makes sure
    //that we don't scan unwanted memory and leading our game to crash
    DWORD base = (DWORD) mInfo.lpBaseOfDll;
    DWORD size = (DWORD) mInfo.SizeOfImage;

    //Get length for our mask, this will allow us to loop through our array
    DWORD patternLength = (DWORD) strlen(mask);

    for (DWORD i = 0; i < size - patternLength; i++)
    {
        bool found = true;
        for (DWORD j = 0; j < patternLength; j++)
        {
            //if we have a ? in our mask then we have true by default, 
            //or if the bytes match then we keep searching until finding it or not
            found &= mask[j] == '?' || pattern[j] == *(char*) (base + i + j);
        }

        //found = true, our entire pattern was found
        //return the memory addy so we can write to it
        if (found)
        {
            return base + i;
        }
    }

    return NULL;
}


char *WindowTitle = NULL;
HWND FoundHWND    = NULL;

//-----------------------------------------------------------------------------------
//Finds a windows HWID

BOOL CALLBACK WndWorker(HWND hwnd, LPARAM lParam)
{
    static TCHAR buffer[50];

    GetWindowText(hwnd, buffer, 50);
    if (strstr(buffer, WindowTitle))
    {
        // do something with hwnd here
        FoundHWND = hwnd;
        return FALSE;
    }

    return TRUE;
}

//-----------------------------------------------------------------------------------
//Initializes the structure that finds the windows HWND

HWND GetWindowsHWND(char *Title, char *ConcatStr)
{
    WindowTitle = Title;
    strcat(WindowTitle, ConcatStr);

    EnumWindows(WndWorker, 0);
    return FoundHWND;
}
