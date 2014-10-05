#ifndef _PLAYFIELD_H_
#define _PLAYFIELD_H_
#include <windows.h>
#include <vector>
#include "Entity/Entity.h"
#include "Entity/LocalPlayer.h"
#include "N3Engine.h"

//typedef PlayField *(__cdecl* GetPlayfield_t)();

//----------------------------------------------------------------------------------
//Enum's for identification
enum ZoneType { GROUND_OUTSIDE = 0,
                DUNGEON_INSIDE = 1, 
                UNKNOWN = 2};


class ZoneField
{
public:
    //------------------------------------------------------------------------------
    //Return the type of tile the user is standing on

    __forceinline ZoneType GetZoneType()
    {
        DWORD *TileIdentPtr = *(DWORD**) ((DWORD)this + 0xC);
        DWORD GroundTileType = *(DWORD*) (TileIdentPtr + 0x18);

        switch (GroundTileType)
        {
        case DUNGEON_INSIDE:
            return DUNGEON_INSIDE;
        case GROUND_OUTSIDE:
            return GROUND_OUTSIDE;
        default:
            return UNKNOWN;
        }
    }

};

class ZoneSurface
{
public:
};


class PlayField
{
private:
    //------------------------------------------------------------------------------
    //Type Defs for in-game calls

    typedef PlayField *(__cdecl* GetPlayfield_t)();

public:
    //------------------------------------------------------------------------------
    //Gets the static instance of the class used in game.

	static PlayField *GetInstance(char* moduleName = "N3")
	{
		HMODULE module = GetModuleHandle(moduleName);
		GetPlayfield_t GetPlayfield;

		GetPlayfield = (GetPlayfield_t) GetProcAddress(module, 
			"?GetPlayfield@n3EngineClient_t@@SAPAVn3Playfield_t@@XZ");

        return GetPlayfield();

	}

    //------------------------------------------------------------------------------
    //Gets the name of the zone currently in

    __forceinline char *GetName()
    {
        DWORD NamePointer = *(DWORD*) ((DWORD)this + 0x8c);
        if (NamePointer)
        {
            return *(char**) (NamePointer + 0x20);
        }

        return 0;
    }

    //------------------------------------------------------------------------------
    //Returns the zone type of which the current user is located in

    __forceinline ZoneType GetZoneType()
    {
        return GetZoneField()->GetZoneType();
    }

    //------------------------------------------------------------------------------
    //Returns the zone's size as a calculated area

	__forceinline int GetZoneSize()
	{
		return ((DWORD)this + 0x50);
	}

    //------------------------------------------------------------------------------
    //Returns a set of objects based on requested ID

    __forceinline std::vector<Entity*> GetObjectsInArea(DWORD TypeID, 
                bool includeLocal = false)
    {
        std::vector<Entity*> ObjectsInArea;  //Return contained of objects
        DWORD ObjectArrayStart    = *(DWORD*) ((DWORD)this + 0x30); //Start of list
        DWORD ObjectArrayEnd      = *(DWORD*) ((DWORD)this + 0x34); //End of list
        LocalPlayer *player       = N3Engine::GetInstance()->GetLocalPlayer();
        IDENT_T EntityIdent       = { 0, 0 };
        Entity *ObjectEntity = 0;

        //Loop through the list of objects.
        for (; ObjectArrayStart != ObjectArrayEnd; ObjectArrayStart += 4)
        {
            ObjectEntity = *(Entity**) ObjectArrayStart;
            EntityIdent  = ObjectEntity->GetIdentity();

            //Check the entity to see if it matches the type we're looking for
            if (EntityIdent.EntityType == TypeID || TypeID == 0)
            {
                if (includeLocal == true)
                {
                    ObjectsInArea.push_back(ObjectEntity);
                }
                else
                {
                    if (EntityIdent.EntityUID != player->GetIdentity().EntityUID)
                    {
                        ObjectsInArea.push_back(ObjectEntity);
                    }
                }
            }
        }

        return ObjectsInArea;
    }

    //------------------------------------------------------------------------------
    //Gets objects in an area based on their distances between local player and itself

    __forceinline std::vector<Entity*> GetObjectsByDistance(DWORD TypeID,
                FLOAT maxDistance, BOOL includeLocal = false)
    {
        LocalPlayer *player = N3Engine::GetInstance()->GetLocalPlayer();
        std::vector<Entity*>ObjectsInArea = GetObjectsInArea(TypeID, includeLocal);
        std::vector<Entity*>EntitiesByDistance;
        FLOAT distance = 0;

        for (int i = 0; i < ObjectsInArea.size(); i++)
        {
            distance = player->GetDistance(ObjectsInArea[i]);
            if (distance <= maxDistance)
            {
                EntitiesByDistance.push_back(ObjectsInArea[i]);
            }

        }

        return EntitiesByDistance;
        
    }

    //------------------------------------------------------------------------------
    //Get the zone instance details class

	__forceinline ZoneField *GetZoneField()
	{
		return (ZoneField*) *(DWORD*) ((DWORD)this + 0x54);
	}

    //------------------------------------------------------------------------------
    //Get the Zone specific surface details

	__forceinline ZoneSurface *GetZoneSurface()
	{
		return(ZoneSurface*) *(DWORD*) ((DWORD)this + 0x60);
	}
};


#endif