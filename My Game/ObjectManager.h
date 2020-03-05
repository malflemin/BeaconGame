/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#pragma once

#include <list>

#include "Object.h"
//#include "MinerObject.h"
#include "Component.h"
#include "Common.h"
#include "Settings.h"
#include "TileManager.h"
#include "DeadMinerObject.h"

using namespace std;

/// \brief The object manager.
///
/// A collection of all of the game objects.

class CObjectManager: 
  public CComponent, 
  public CCommon, 
  public CSettings{

  private:
    list<CObject*> m_stdObjectList; ///< Object list.

    CTileManager* m_pTileManager = nullptr; ///< Pointer to tile manager.

    void BroadPhase(); ///< Broad phase collision detection and response.
    void NarrowPhase(CObject* p0, CObject* p1); ///< Narrow phase collision detection and response.
    void CullDeadObjects(); ///< Cull dead objects.

		int m_nScore = 0;
		
		float orientation = 0;
		int deadCount = 0;
		int m_nCurrentFloor;

  public:
    CObjectManager(); ///< Constructor.
    ~CObjectManager(); ///< Destructor.

    CObject* create(eSpriteType t, const Vector2& v); ///< Create new object.
		CObject* create(eSpriteType t, CObject* Obj); ///< Create new object.
	//CMinerObject* createMiner(eSpriteType t, const Vector2& v); ///< Create new miner unit.

    void clear(); ///< Reset to initial conditions.
    void move(); ///< Move all objects.
    void draw(); ///< Draw all objects.
	bool isNext = false;
	void CurrentFloor(); //keeps track of the current floor the bridge is
	void mine(CObject* p, CObject* a);

	void RecedeSpikes(CObject* p); ///< Make spikes recede.
	void ReleaseSpikes(CObject* p); ///< Make spikes release.

	void MoveBridge(CObject* p); ///<Make bridge move out.
	void ReverseBridge(CObject* p); ///Make bridge move in.

	void MoveGoblinHand(CObject* p, CObject* g); ///< Goblin hand movement
	void MoveBackGoblinHand(CObject* g); ///< Make goblin hand move back
	void StopGoblinHand(CObject* g); ///< Make goblin hand stop
	void BurnGoblinHand(CObject* g); ///< Make gbolin hand move back on button press

	void getDeadMinerCount(); ///< Get the number of dead miners
	void resetDeadMinerCount(); ///< Reset number of dead miners

	void resetPointers(); ///<Make specified pointers a nullptr

	int GetScore(); ///< Get current score.

	void getScoreSpecs(int lvl); ///Get the score specs

    void LoadMap(int curLevel); ///< Load a level.
}; //CObjectManager