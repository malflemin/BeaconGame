/// \file Common.h
/// \brief Interface for the class CCommon.

#pragma once

#include "SndList.h"

//forward declarations to make the compiler less stroppy

class CObjectManager; 
class CRenderer;
class CParticleEngine2D;
class CObject;
class CMouse;

/// \brief The common variables class.
///
/// CCommon is a singleton class that encapsulates 
/// things that are common to different game components,
/// including game state variables.
/// Making it a singleton class means
/// that we can avoid passing its member variables
/// around as parameters, which makes the code
/// minisculely faster, and more importantly, reduces
/// function clutter.

class CCommon{
  protected:  
    static CRenderer* m_pRenderer; ///< Pointer to the renderer.
    static CObjectManager* m_pObjectManager; ///< Pointer to the object manager.
    static CParticleEngine2D* m_pParticleEngine; ///< Pointer to particle engine.    

    static bool m_bDrawAABBs; ///< Whether to draw AABBs.
    static Vector2 m_vWorldSize; ///< World height and width.
		static int size;
		static float range;
	static CObject* m_pPlay;
    static CObject* m_pPlayer; ///< Pointer to player character.
	//static CObject* m_pSpikes; ///< Pointer to spikes.
	static CObject* m_pTrap[32]; ///< Pointer to spikes.
	static CObject* m_pSwitch;
	static CObject* m_pRotSpike;
	static CObject* m_pMiner[32]; ///< Pointer to miners
	static CObject* m_pWarrior[32]; // pointer to warriors
	static CObject* m_pMSelect[32]; ///< Pointer to miner select outlines
	static CObject* m_pMenu1; ///< trap distance UI
	static CObject* m_pMiner1;
	static CObject* m_pSpider;
	static CObject* m_pOre[32];
	static CObject* m_pBridge;
	static CObject* m_pBridge2; 
	static CObject* m_pDoor;
	static CObject* m_pPlat; 
	static CObject* m_pPlat2;
	static CObject* m_pPlat3;
	static CObject* m_pOne;
	static CObject* m_pTwo;
	static CObject* m_pThree;
	static CObject* m_pResultScreen;
	static CObject* m_pStar[3];
	static CObject* m_pLGoblin;
	static CObject* m_pRGoblin;
	static CObject* m_pGoblinH[32];
	static CObject* m_pGoblinArm[32];
	static CObject* m_pGameOverScreen;
	static CObject* m_pMovingPlat;
	static CMouse* m_pMouse; ///<Pointer to the mouse
}; //CCommon
