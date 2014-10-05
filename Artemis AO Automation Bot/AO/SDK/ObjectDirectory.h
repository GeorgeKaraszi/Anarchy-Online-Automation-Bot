#ifndef _OBJECTDIRECORY_H_
#define _OBJECTDIRECORY_H_
#include <windows.h>
#include "Entity/Entity.h"


class ObjectDirectory
{
private:
    //-------------------------------------------------------------------------------
    //TypeDefs for in-game calls
    typedef ObjectDirectory *(__cdecl* GetDirectoryMap_t)();

public:

	//-------------------------------------------------------------------------------
	//Gets the instance address to the Object Mapping directory
    static ObjectDirectory *GetInstance(char *moduleName = "N3")
	{
		HMODULE ObjectHandle = GetModuleHandle(moduleName);
		GetDirectoryMap_t ObjectMap;

		ObjectMap = (GetDirectoryMap_t) GetProcAddress(ObjectHandle, 
					"?GetDynelMap@n3Dynel_t@@SAABVDynelMap_t@@XZ");

		return ObjectMap();
	}


	//-------------------------------------------------------------------------------
	//Gets the total number of leaf nodes in the BTREE
	__forceinline int GetNumberOfNodes()
	{
		return *(int*) ((DWORD)this + 0x8);
	}

	//-------------------------------------------------------------------------------
	//Gets the root of the BTree that houses all the object nodes

	__forceinline EntityBTree *GetEntityBTreeRoot()
	{
		DWORD *HeadBTree = *(DWORD**) ((DWORD)this + 0x4);
		return (EntityBTree*) *(DWORD*) (HeadBTree + 0x4);
	}


    //------------------------------------------------------------------------------
    //Search the tree for the object

    __forceinline Entity *FindEntity(DWORD UID)
    {
        EntityBTree *Node = GetEntityBTreeRoot();

        while (Node != NULL && Node->UniqueID != UID)
        {
            if (Node->UniqueID > UID)
                Node = Node->LeftNode;
            else
                Node = Node->RightNode;
        }

        if (Node->UniqueID == UID)
            return Node->EntityObj;

       
        return NULL;
    }


};

//-----------------------------------------------------------------------------------
//Tree structure for all entities on a given map
class EntityBTree
{
public:
	EntityBTree *LeftNode;	   //0x00
	EntityBTree *ParentNode;   //0x04
	EntityBTree *RightNode;	   //0x08
	DWORD ObjectTypeID;		   //0x0C
	DWORD UniqueID;            //0x10
	Entity *EntityObj;         //0x14
	BYTE Unknown;              //0x18
	bool FoundDynel;           //0x19 //Not sure if this is, at all useful
};

#endif