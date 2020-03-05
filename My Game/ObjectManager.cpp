/// \file ObjectManager.cpp
/// \brief Code for the the object manager class CObjectManager.

#include "ObjectManager.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"

/// Create the tile manager;

CObjectManager::CObjectManager(){
  m_pTileManager = new CTileManager(32);
} //constructor

/// Destruct all of the objects in the object list.

CObjectManager::~CObjectManager(){
  delete m_pTileManager;

  for(auto const& p: m_stdObjectList) //for each object
    delete p; //delete object
} //destructor

/// Load a map from a text file into the tile manager.

void CObjectManager::LoadMap(int curLevel){
	switch (curLevel) {
//	case 1: m_pTileManager->LoadMap("Media\\Maps\\map.txt"); break;
	//case 2: m_pTileManager->LoadMapFromImageFile("Media\\Maps\\maze.png"); break;
		//case 3: m_pTileManager->LoadMapFromImageFile("Media\\Maps\\map2.png"); break;
	case 1: m_pTileManager->LoadMap("Media\\Maps\\map3.txt"); break;
	case 2: m_pTileManager->LoadMap("Media\\Maps\\map4.txt"); break;
	case 3: m_pTileManager->LoadMap("Media\\Maps\\map5.txt"); break;
	} //switch
} //LoadMap

/// Create an object and put a pointer to it on the object list.
/// \param t Sprite type.
/// \param v Initial position..
/// \return Pointer to the object created.

CObject* CObjectManager::create(eSpriteType t, const Vector2& v){
  CObject* p = new CObject(t, v); 
  m_stdObjectList.push_back(p); 
	p->InitialPos = p->GetPos();
  return p;
} //create

CObject* CObjectManager::create(eSpriteType t, CObject* pObj) {
	CObject* p = nullptr;
	switch (t) {
	case GOLD_SPRITE: p = new CDeadMinerObject(pObj->GetPos(), pObj->GetVelocity()); break;
	default: p = new CObject(t, pObj->GetPos()); break;
	}
	m_stdObjectList.push_back(p);
	return p;
}


// MINER CREATE CLASS FOR LATER USE - CURRENTLY EXPERIENCING ISSUES WITH IT'S INHERITANCE !!!(BREAKPOINT AT END OF GAME.EXE)!!!
/*
CMinerObject* CObjectManager::createMiner(eSpriteType t, const Vector2& v) {
	CMinerObject* p = new CMinerObject(t, v);
	m_stdObjectList.push_back(p);
	return p;
} //create
*/


/// Delete all of the objects managed by the object manager. 
/// This involves deleting all of the CObject instances pointed
/// to by the object list, then clearing the object list itself.

void CObjectManager::clear(){
  for(auto const& p: m_stdObjectList) //for each object
    delete p; //delete object

  m_stdObjectList.clear(); //clear the object list
} //clear

/// Draw the tiled background and all of the objects.

void CObjectManager::draw(){
  //draw tiled background

	
  m_pTileManager->Draw(TILE_SPRITE);
  if(m_bDrawAABBs)
    m_pTileManager->DrawBoundingBoxes(GREENLINE_SPRITE);

  //draw objects
 
	  for (auto const& p : m_stdObjectList) { //for each object
		  if (!p->IsDead()) {
		  m_pRenderer->Draw(*(CSpriteDesc2D*)p);

		  if (m_bDrawAABBs)
			  m_pRenderer->DrawBoundingBox(p->GetBoundingBox());
		  }
	  } //for
} //draw

/// Move all of the objects and perform 
/// broad phase collision detection and response.

void CObjectManager::move() {
	CullDeadObjects(); //remove dead objects from object list
	for (auto const& p : m_stdObjectList) { //for each object
		if(p->IsDead()){
		
		}
		else {
			const Vector2 oldpos = p->m_vPos; //its old position

			p->move(); //move it

			//object to wall collision detection and response using
			//bounding spheres for the objects and AABBs for the walls.

			vector<BoundingBox> walls; //bounding boxes for wall collision

			if (m_pTileManager->CollideWithWall(p->GetBoundingBox(), walls))
				switch (p->m_nSpriteIndex) {
				case PLAYER_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case MINER_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case WARRIOR_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case AMBER_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case GOLD_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case SAPPHIRE_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case RUBY_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case EMERALD_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case AMETHYST_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case DIAMOND_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case BACON_SPRITE:
					for (auto const& b : walls)
						p->CollisionResponse(b);
					break;
				case DEATH_SPRITE:
					break;
				case BRIDGE_SPRITE:
					break;
				case ROT_SPRITE:
					break;
				case FIN_SPRITE:
					break;
				case MENU1_SPRITE:
					break;
				case ISPIKE_SPRITE:
					break;
				case SPIKES_SPRITE:
					break;
				case MSELECT_SPRITE:
					break;
				case WEB_SPRITE:
					break;
				case DOOR_SPRITE:
					break;
				case SHADE_SPRITE:
					break;
				case ONE_SPRITE:
					break;
				case TWO_SPRITE:
					break;
				case THREE_SPRITE:
					break;
				case RESULTSCREEN_SPRITE:
					break;
				case STAR_SPRITE:
					break;
				case BLANKSTAR_SPRITE:
					break;
				case LGOBLIN_SPRITE:
					break;
				case RGOBLIN_SPRITE:
					break;
				case GOBLINARM_SPRITE:
					break;
				case GAMEOVER_SPRITE:
					break;
				case MOVING_SPRITE:
					/*The moving platforms will reverse upon wall contact.*/
					p->m_vVelocity.x = -p->m_vVelocity.x;
					break;
				default:
					p->kill();
					m_pAudio->play(RICOCHET_SOUND);
				} //switch

			if (p->m_nSpriteIndex == MINER_SPRITE) {
				const float r = m_pPlayer->m_Sphere.Radius;
				bool bFollow = p->IsFollowing();
				for (int i = 0; i < size; i++) {
					if (bFollow) {
						p->follow(m_pPlayer->GetPos().x);
					}

					else if (!bFollow && m_pOre[i] != NULL)
					{
						if (!m_pOre[i]->IsDead() && p->GetPos().x > m_pOre[i]->GetPos().x - 100 && p->GetPos().x < m_pOre[i]->GetPos().x + 100) {
							if (p->GetPos().y - m_pOre[i]->GetPos().y < 15.0f && p->GetPos().y - m_pOre[i]->GetPos().y > -15.0f)
								mine(p, m_pOre[i]);
						}
					}//else if

					if (m_pTrap[i] != nullptr && m_pTrap[i]->m_nSpriteIndex == BRIDGE_SPRITE) {
						if (p->GetPos().x > m_pTrap[i]->GetPos().x - 100 && p->GetPos().x < m_pTrap[i]->GetPos().x + 110)
							p->CollisionResponse(m_pTrap[i]->GetBoundingBox());
					}//if
				}//for
			}
			if (p->m_nSpriteIndex == WARRIOR_SPRITE) {
				const float r = m_pPlayer->m_Sphere.Radius;
				bool bFollow = p->IsFollowing();
				for (int i = 0; i < size; i++) {
					if (bFollow) {
						p->follow((m_pPlayer->GetPos().x));
					}

					else if (!bFollow && m_pOre[i] != NULL)
					{
						if (!m_pOre[i]->IsDead() && p->GetPos().x > m_pOre[i]->GetPos().x - 200 && p->GetPos().x < m_pOre[i]->GetPos().x + 200)
							if (p->GetPos().y - m_pOre[i]->GetPos().y < 15.0f && p->GetPos().y - m_pOre[i]->GetPos().y > -15.0f)
								mine(p, m_pOre[i]);
					}//else if

					if (m_pTrap[i] != nullptr && m_pTrap[i]->m_nSpriteIndex == BRIDGE_SPRITE) {
						if (p->GetPos().x > m_pTrap[i]->GetPos().x - 100 && p->GetPos().x < m_pTrap[i]->GetPos().x + 110)
							p->CollisionResponse(m_pTrap[i]->GetBoundingBox());
					}//if
				}//for
				if (p->GetPos().x > m_pBridge2->GetPos().x - 100 && p->GetPos().x < m_pBridge2->GetPos().x + 110)
					p->CollisionResponse(m_pBridge2->GetBoundingBox());
			} //for
		
			if (p->m_nSpriteIndex == SPIDER_SPRITE) {
				if (m_pSwitch->m_nCurrentFrame == 1) {
					if (p->GetPos().y > 100.0f)
						p->m_vVelocity.y = -30.0f;
					else {
						p->m_vVelocity.y = 0.0f;
						p->m_vVelocity.x = -20.0f;
					}

					if (p->GetPos().x < 150.0f) {
						p->m_vVelocity.x = 0.0;
					}

				}
			}
			/*moving platform movement*/
			if (p->m_nSpriteIndex == MOVING_SPRITE) {
					if (p->m_vVelocity.x == 0)
						p->m_vVelocity.x = 50.0f;
				}
			/*moving platform movement end*/
			if (p->m_nSpriteIndex == LGOBLIN_SPRITE) {
				for (int i = 0; i < size; i++) {
					if (!p->IsDisabled()) {
						if (m_pMiner[i] != nullptr && !m_pMiner[i]->IsDead())
							MoveGoblinHand(m_pMiner[i], p);
						else if (m_pMiner[i] != nullptr && m_pMiner[i]->IsDead()) {
							MoveBackGoblinHand(p);
							StopGoblinHand(p);
						}
					}
					else if (p->IsDisabled()) {
						BurnGoblinHand(p);
						StopGoblinHand(p);
					}
					//}//else if
				}//for
			}//if

			if (p->m_nSpriteIndex == RGOBLIN_SPRITE) {
				for (int i = 0; i < size; i++) {
					if (!p->IsDisabled()) {
						if (m_pMiner[i] != nullptr && !m_pMiner[i]->IsDead())
							MoveGoblinHand(m_pMiner[i], p);
						else if (m_pMiner[i] != nullptr && m_pMiner[i]->IsDead()) {
							MoveBackGoblinHand(p);
							StopGoblinHand(p);
						}//else if
					}
					else if (p->IsDisabled()) {
						BurnGoblinHand(p);
						StopGoblinHand(p);
					}
				}//for
			}//if
			//now do object-object collision detection and response and
			//remove any dead objects from the object list.

			BroadPhase(); //broad phase collision detection and response

		}
		//CullDeadObjects(); //remove dead objects from object list
	} //move
}

/* START OF MINER AI DEFINITIONS
Functions:
follow()
mine()
*/





void CObjectManager::mine(CObject* p, CObject* a) {
	float pos = a->GetPos().x;
	float ran = p->GetPos().x;
	float dis = pos - ran;

	if (pos < ran && pos < ran - (95.0f)) 
		p->SetSpeed(-100.0f);
	if (pos > ran && pos > ran + (95.0f)) 
		p->SetSpeed(100.0f);

	if (a->m_nSpriteIndex == AMBER_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 15) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 30) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 45) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 60) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 10;
				p->m_nMinerScore += 10;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == SAPPHIRE_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 33) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 66) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 99) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 132) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 50;
				p->m_nMinerScore += 50;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == RUBY_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 25) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 50) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 75) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 100) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 20;
				p->m_nMinerScore += 20;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == EMERALD_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 40) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 80) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 120) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 160) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 70;
				p->m_nMinerScore += 70;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == AMETHYST_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 50) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 100) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 150) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 200) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 100;
				p->m_nMinerScore += 100;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == DIAMOND_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 65) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 130) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 195) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 260) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 150;
				p->m_nMinerScore += 150;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == BACON_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 75) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 150) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 225) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 300) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += 500;
				p->m_nMinerScore += 500;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
	if (a->m_nSpriteIndex == GOLD_SPRITE) {
		if (pos < ran && pos > ran - (55.0f)) {
			p->SetState(false);
			p->SetSpeed(0.0f);
			p->mining();
			a->IncrHit();
			m_pAudio->vary(MINING_SOUND);
			if (a->Gethit() == 50) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 100) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 150) {
				a->m_nCurrentFrame++;
			}
			if (a->Gethit() == 200) {
				m_pAudio->stop(MINING_SOUND);
				a->kill();
				m_nScore += a->m_nMinerScore;
				p->m_nMinerScore += a->m_nMinerScore;
				p->m_nCurrentFrame = 0;
			}//if
		}//if
	}//if
}
/*END OF MINER AI DEFINITIONS*/

/*START OF OBJECT AI DEFINITIONS
Functions:
rise() -- Select escalator object rises
*/

/*END OF OBJECT AI DEFINITIONS*/

/// Set current spike damage to zero to indicate that it has receded.
void CObjectManager::RecedeSpikes(CObject* p) {
	if (p->m_nSpriteIndex == SPIKES_SPRITE) {
		const size_t nFrameCount = m_pRenderer->GetNumFrames(p->m_nSpriteIndex);
		const float dt = 1000 * p->m_fFrameInterval / (1500 + fabs(p->m_vVelocity.x));

		if (p->SpikeCooldown == 0.0f) {
			if (!p->IsDisabled())
				m_pAudio->play(TIMER_SOUND);
			p->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
			//p->m_nCurrSpikeDamage = 0;
			if (p->m_nCurrentFrame != 6) {
				p->m_fFrameTimer = m_pStepTimer->GetTotalSeconds();
				p->m_nCurrentFrame = (p->m_nCurrentFrame + 1) % nFrameCount;
			}//if
			else
				p->SpikeCooldown++;
		}//if

		else if (p->SpikeCooldown == 1.0f) {
			if ((p->m_fCurrentTrapTimer - p->m_fInitialTrapTimer) >= (p->m_fSpikeTimeLimit + 1.0f)) {
				if (!p->IsDisabled())
					m_pAudio->play(TIMER_SOUND);
				//p->m_nCurrSpikeDamage = 0;
				if (p->m_nCurrentFrame != 6) {
					p->m_fFrameTimer = m_pStepTimer->GetTotalSeconds();
					p->m_nCurrentFrame = (p->m_nCurrentFrame + 1) % nFrameCount;
				}//if
				else {
					p->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
				}
			}//if
		}//else if
	}//if
}//RecedeSpikes

/// Set spike damage to max damage to indicate that it's active.
void CObjectManager::ReleaseSpikes(CObject* p) {
	if (p->m_nSpriteIndex == SPIKES_SPRITE) {
		p->m_fCurrentTrapTimer = m_pStepTimer->GetTotalSeconds();

		const size_t nFrameCount = m_pRenderer->GetNumFrames(p->m_nSpriteIndex);
		const float dt = 1000 * p->m_fFrameInterval / (1500 + fabs(p->m_vVelocity.x));

		if ((p->m_fCurrentTrapTimer - p->m_fInitialTrapTimer) >= p->m_fSpikeTimeLimit - 1.8f) {
			//p->m_nCurrSpikeDamage = p->m_nSpikeDamage;
			p->SetDisableState(false);

			if (p->m_nCurrentFrame != 0) {
				p->m_nCurrentFrame = (p->m_nCurrentFrame - 1) % nFrameCount;
			}//if
		}//if
	}//if
}//ReleaseSpikes
void CObjectManager::CurrentFloor() {
	m_nCurrentFloor = 1;
}
/*BRIDGE FUNCTIONS*/
///Move bridge out
void CObjectManager::MoveBridge(CObject* p) {
	//if (!p->m_bActiveBridge) {
	//	p->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
	//	p->m_vVelocity.x = 30.0f;
	//	p->SetBridgeState(true);
	//}//if
	if (p->m_nSpriteIndex == BRIDGE_SPRITE) {
		if (m_nCurrentFloor == 1) {
			if (!p->m_bActiveBridge) {
				p->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
				p->m_vVelocity.y = -15.0f;
				p->SetBridgeState(true);
				m_nCurrentFloor = 2;
			}//if
		}//if
		if (m_nCurrentFloor == 3) {
			if (!p->m_bActiveBridge) {
				p->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
				p->m_vVelocity.y = -15.0f;
				p->SetBridgeState(true);
				//m_nCurrentFloor = 3;
			}//if
		}//if
	}//if
}//MoveBridge

///Make bridge stop after a specified time.
///Make bridge move back after a specified time.
void CObjectManager::ReverseBridge(CObject* p) {
	if (p->m_nSpriteIndex == BRIDGE_SPRITE) {
		p->m_fCurrentTrapTimer = m_pStepTimer->GetTotalSeconds();
		if (m_nCurrentFloor == 2) {
			if (p->m_fCurrentTrapTimer - p->m_fInitialTrapTimer >= 7.6f) {
				if (p->m_vVelocity.y != 0.0f) {
					p->m_vVelocity.y = 0.0f;
					p->m_fInitialTrapTimer = p->m_fCurrentTrapTimer;
					p->SetBridgeState(false);
					m_nCurrentFloor = 3;
				}//if
			}//if
		}
		if (m_nCurrentFloor == 3) {
			if (p->m_fCurrentTrapTimer - p->m_fInitialTrapTimer >= 4.2f) {
				if (p->m_vVelocity.y != 0.0f) {
					p->m_vVelocity.y = 0.0f;
					p->m_fInitialTrapTimer = p->m_fCurrentTrapTimer;
					p->SetBridgeState(false);
					m_nCurrentFloor = 4;
				}//if
			}//if
		}
		if (m_nCurrentFloor == 4) {
			if (p->m_fCurrentTrapTimer - p->m_fInitialTrapTimer >= 4.2f) {
				if (p->m_vVelocity.y == 0.0f) {
					p->m_vVelocity.y = 15.0f;
					p->m_fInitialTrapTimer = p->m_fCurrentTrapTimer;
					//p->SetBridgeState(false);
					//m_nCurrentFloor = 1;
				}//if
				else if (p->m_vVelocity.y != 0.0f) {
					p->m_vVelocity.y = 0.0f;
					p->m_fInitialTrapTimer = p->m_fCurrentTrapTimer;
					p->SetBridgeState(false);
					m_nCurrentFloor = 3;
				}
			}//if
		}
	}
}//ReverseBridge
/*BRIDGE FUNCTIONS END*/

void CObjectManager::MoveGoblinHand(CObject* p, CObject* g) {
	if (g != nullptr) {
		if (g->m_nSpriteIndex == LGOBLIN_SPRITE) {
			if ((g->GetPos().x - g->InitialPos.x) >= 32.0f)
				g->m_vVelocity.x = -30.0f;
			else if (g->m_vVelocity.x == 0.0f && (p->GetPos().x - g->GetPos().x) > 110.0f && abs(p->GetPos().y - g->GetPos().y) < 45.0f)
				g->m_vVelocity.x = 30.0f;
			else if((g->GetPos().x - g->InitialPos.x) <= 0.0f)
				g->m_vVelocity.x = 0;
		}//if
		else if (g->m_nSpriteIndex == RGOBLIN_SPRITE) {
			if (abs(g->GetPos().x - g->InitialPos.x) >= 32.0f)
				g->m_vVelocity.x = 30.0f;
			else if (g->m_vVelocity.x == 0.0f && (p->GetPos().x - g->GetPos().x) < 110.0f && abs(p->GetPos().y - g->GetPos().y) < 45.0f)
				g->m_vVelocity.x = -30.0f;
			else if ((g->GetPos().x - g->InitialPos.x) >= 0.0f)
				g->m_vVelocity.x = 0.0f;
		}//else if
	}//if
}//MoveGoblinHand

void CObjectManager::MoveBackGoblinHand(CObject* g) {
	if (g != nullptr) {
		if (g->m_nSpriteIndex == LGOBLIN_SPRITE) {
			if ((g->GetPos().x - g->InitialPos.x) >= 32.0f) {
				g->m_vVelocity.x = -30;
			}
		}//if
		else if (g->m_nSpriteIndex == RGOBLIN_SPRITE) {
			if (abs(g->GetPos().x - g->InitialPos.x) >= 32.0f)
				g->m_vVelocity.x = 30.0f;
		}//else if
	}//if
}//MoveBackGoblinHand

void CObjectManager::StopGoblinHand(CObject* g) {
	if (g != nullptr) {
		g->m_fCurrentTrapTimer = m_pStepTimer->GetTotalSeconds();
		if (g->m_nSpriteIndex == LGOBLIN_SPRITE) {
			if ((g->GetPos().x - g->InitialPos.x) <= 0.0f) {
				g->m_vVelocity.x = 0.0f;
				//g->SetDisableState(false);
			}
			else if (g->m_vVelocity.x == 0.0f && g->IsDisabled() && (g->m_fCurrentTrapTimer - g->m_fInitialTrapTimer) >= 1.0f) {
				g->SetDisableState(false);
			}
		}//if
		else if (g->m_nSpriteIndex == RGOBLIN_SPRITE) {
			if ((g->GetPos().x - g->InitialPos.x) >= 0.0f) {
				g->m_vVelocity.x = 0.0f;
			}
			else if (g->m_vVelocity.x == 0.0f && g->IsDisabled() && (g->m_fCurrentTrapTimer - g->m_fInitialTrapTimer) >= 1.0f) {
				g->SetDisableState(false);
			}
		}//else if
	}//if
}//StopGoblinHand

void CObjectManager::BurnGoblinHand(CObject* g) {
	if (g != nullptr) {
		if (g->m_nSpriteIndex == LGOBLIN_SPRITE) {
			g->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
			g->m_vVelocity.x = -30.0f;
		}//if
		else if (g->m_nSpriteIndex == RGOBLIN_SPRITE) {
			g->m_fInitialTrapTimer = m_pStepTimer->GetTotalSeconds();
			g->m_vVelocity.x = 30.0f;
		}//else if
	}//if
}//BurnGoblinHand

void CObjectManager::getDeadMinerCount() {
	for (int i = 0; i < size; i++) {
		if (m_pMiner[i] != nullptr) {
			
			if (m_pMiner[i]->IsDead() && !m_pMiner[i]->counted) {
				deadCount++;
				m_pMiner[i]->IsCounted(true);
			}
			if (deadCount >= 3) {
				m_pGameOverScreen = m_pObjectManager->create(GAMEOVER_SPRITE, Vector2(100.0f, 450.0f));
				m_pGameOverScreen->SetDisableState(true);
			}
		}
	}
}

void CObjectManager::resetDeadMinerCount() {
	for (int i = 0; i < size; i++) {
		if (m_pMiner[i] != nullptr) 
			if (m_pMiner[i]->IsDead())
				m_pMiner[i]->IsCounted(false);
	}
	deadCount = 0;
}

void CObjectManager::resetPointers() {
	for (int i = 0; i < size; i++) {
		m_pTrap[i] = nullptr;
	}
	m_pPlat = nullptr;
	m_pPlat2 = nullptr;
	m_pPlat3 = nullptr;
	m_pStar[0] = nullptr;
	m_pStar[1] = nullptr;
	m_pStar[2] = nullptr;
}

///Get the result screen with the user's score specs per level
void CObjectManager::getScoreSpecs(int lvl) {
	m_pResultScreen = m_pObjectManager->create(RESULTSCREEN_SPRITE, Vector2(512.0f, 384.0f));
	if (lvl == 1) {
		if (m_nScore == 0) {
			m_pStar[0] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[1] = create(BLANKSTAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[2] = create(BLANKSTAR_SPRITE, Vector2(100.0f, 100.0f));
		}//if
		else if (m_nScore > 0 && m_nScore < 50) {
			m_pStar[0] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[1] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[2] = create(BLANKSTAR_SPRITE, Vector2(100.0f, 100.0f));
		}//else if
		else if (m_nScore >= 50) {
			m_pStar[0] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[1] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[2] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
		}//else if
	}//if
	if (lvl == 3) {
		if (m_nScore == 0) {
			m_pStar[0] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[1] = create(BLANKSTAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[2] = create(BLANKSTAR_SPRITE, Vector2(100.0f, 100.0f));
		}//if
		else if (m_nScore > 0 && m_nScore < 600) {
			m_pStar[0] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[1] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[2] = create(BLANKSTAR_SPRITE, Vector2(100.0f, 100.0f));
		}//else if
		else if (m_nScore >= 600) {
			m_pStar[0] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[1] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
			m_pStar[2] = create(STAR_SPRITE, Vector2(100.0f, 100.0f));
		}//else if
	}//if
}//getScoreSpecs

/// This is a "bring out yer dead" Monty Python type of thing.
/// Iterate through the objects and check whether their "is dead"
/// flag has been set. If so, then delete its pointer from
/// the object list and destruct the object.

void CObjectManager::CullDeadObjects(){
  for(auto &i=m_stdObjectList.begin(); i!=m_stdObjectList.end();){
    if((*i)->IsDead()){ //"He's dead, Dave." --- Holly, Red Dwarf
      *i = nullptr; //delete object
	  delete* i;
      i = m_stdObjectList.erase(i); //remove from object list and advance to next object
    } //if
      
    else ++i; //advance to next object
  } //for
} //CullDeadObjects

/// Perform collision detection and response for all pairs
/// of objects in the object list, making sure that each
/// pair is processed only once.

void CObjectManager::BroadPhase(){
  for(auto i=m_stdObjectList.begin(); i!=m_stdObjectList.end(); i++){
    for(auto j=next(i); j!=m_stdObjectList.end(); j++)
      NarrowPhase(*i, *j);
  } //for
} //BroadPhase

/// Perform collision detection and response for a pair of objects.
/// We are talking about bullets hitting the player and the
/// turrets here. When a collision is detected the response
/// is to delete the bullet (i.e. mark its "is dead" flag)
/// play a particle effect at the point of contact, and play one 
/// sound for the player and another for the turrets.
/// \param p0 Pointer to the first object.
/// \param p1 Pointer to the second object.

void CObjectManager::NarrowPhase(CObject* p0, CObject* p1){
	//vector<BoundingBox> obstacle; //bounding boxes for wall collision
  eSpriteType t0 = (eSpriteType)p0->m_nSpriteIndex;
  eSpriteType t1 = (eSpriteType)p1->m_nSpriteIndex;

  if(p0->m_Sphere.Intersects(p1->m_Sphere)){ //bounding spheres intersect
    if(t0 == BULLET_SPRITE && t1 == TURRET_SPRITE){ //bullet hits turret
      p0->kill();
      m_pAudio->play(CLANG_SOUND);
    } //if

    else if(t1 == BULLET_SPRITE && t0 == TURRET_SPRITE){ //turret hit by bullet
      p1->kill();
      m_pAudio->play(CLANG_SOUND);
    } //else if

    else if(t0 == BULLET2_SPRITE && t1 == PLAYER_SPRITE){ //player hit by bullet
      m_pAudio->play(OW_SOUND);
      p0->kill();
    } //else if

    else if(t1 == BULLET2_SPRITE && t0 == PLAYER_SPRITE){ //bullet hits playerd
      m_pAudio->play(OW_SOUND);
      p1->kill();
    } //else if

	else if (t0 == SPIKES_SPRITE && t1 == MINER_SPRITE) { //player hit by spikes
		if (!p0->IsDisabled()) {
			p1->m_nHitCount = p1->m_nHitCount + p0->m_nCurrSpikeDamage;
			if (p1->m_nMinerScore > 0) {
				if (!p1->IsDead()) {
					for (int i = 0; i < 10; i++) {
						if (m_pOre[i] == NULL) {
							m_pOre[i] = create(GOLD_SPRITE, p1);
							m_pOre[i]->m_nMinerScore = p1->m_nMinerScore;
							m_nScore -= p1->m_nMinerScore;
							break;
						}
					}
				}
			}
			p1->kill();
			p1->DeathFX();
		}
	} //else if
	else if (t0 == SPIKES_SPRITE && t1 == WARRIOR_SPRITE) { //player hit by spikes
		if (!p0->IsDisabled()) {
			p1->m_nHitCount = p1->m_nHitCount + p0->m_nCurrSpikeDamage;
			if (p1->m_nMinerScore > 0) {
				if (!p1->IsDead()) {
					for (int i = 0; i < 10; i++) {
						if (m_pOre[i] == NULL) {
							m_pOre[i] = create(GOLD_SPRITE, p1);
							m_pOre[i]->m_nMinerScore = p1->m_nMinerScore;
							m_nScore -= p1->m_nMinerScore;
							break;
						}
					}
				}
			}
			p1->kill();
			p1->DeathFX();
		}
	} //else if

	else if (t1 == SPIKES_SPRITE && t0 == MINER_SPRITE) { //spikes hit player
		if (!p1->IsDisabled()) {
			p0->m_nHitCount = p0->m_nHitCount + p1->m_nCurrSpikeDamage;
			if (p0->m_nMinerScore > 0) {
				if (!p1->IsDead()) {
					for (int i = 0; i < 10; i++) {
						if (m_pOre[i] == NULL) {
							m_pOre[i] = create(GOLD_SPRITE, p0);
							m_pOre[i]->m_nMinerScore = p0->m_nMinerScore;
							m_nScore -= p1->m_nMinerScore;
							break;
						}
					}
				}
			}
			p0->kill();
			p0->DeathFX();
		}
	} //else if

	else if (t1 == SPIKES_SPRITE && t0 == WARRIOR_SPRITE) { //spikes hit player
		if (!p1->IsDisabled()) {
			p0->m_nHitCount = p0->m_nHitCount + p1->m_nCurrSpikeDamage;
			if (p0->m_nMinerScore > 0) {
				if (!p1->IsDead()) {
					for (int i = 0; i < 10; i++) {
						if (m_pOre[i] == NULL) {
							m_pOre[i] = create(GOLD_SPRITE, p0);
							m_pOre[i]->m_nMinerScore = p0->m_nMinerScore;
							m_nScore -= p1->m_nMinerScore;
							break;
						}
					}
				}
			}
			p0->kill();
			p0->DeathFX();
		}
	} //else if
	/*MINER AND WARRIOR BOUNCE PLATFORM COLLISION*/
	else if (t0 == PLATFORM_SPRITE && t1 == MINER_SPRITE) { //player hit by platform
		m_pAudio->play(BOUNCE_SOUND);
		p1->m_vVelocity.y = 10.0f;
	} //else if

	else if (t0 == PLATFORM_SPRITE && t1 == WARRIOR_SPRITE) { //player hit by platform
		m_pAudio->play(BOUNCE_SOUND);
		p1->m_vVelocity.y = 10.0f;
	} //else if

	else if (t1 == PLATFORM_SPRITE && t0 == MINER_SPRITE) { //platform hit player
		m_pAudio->play(BOUNCE_SOUND);
		p0->m_vVelocity.y = 10.0f;
	} //else if

	else if (t1 == PLATFORM_SPRITE && t0 == WARRIOR_SPRITE) { //platform hit player
		m_pAudio->play(BOUNCE_SOUND);
		p0->m_vVelocity.y = 10.0f;
	} //else if
	/*MINER AND WARRIOR BOUNCE PLATFORM COLLISION END*/

	/*MINER AND WARRIOR MOVING BOUNCE PLATFORM COLLISION*/
	else if (t0 == MOVING_SPRITE && t1 == MINER_SPRITE) { //player hit by platform
	m_pAudio->play(BOUNCE_SOUND);
	p1->m_vVelocity.y = 10.0f;
	} //else if

	else if (t0 == MOVING_SPRITE && t1 == WARRIOR_SPRITE) { //player hit by platform
	m_pAudio->play(BOUNCE_SOUND);
	p1->m_vVelocity.y = 10.0f;
	} //else if

	else if (t1 == MOVING_SPRITE && t0 == MINER_SPRITE) { //platform hit player
	m_pAudio->play(BOUNCE_SOUND);
	p0->m_vVelocity.y = 10.0f;
	} //else if

	else if (t1 == MOVING_SPRITE && t0 == WARRIOR_SPRITE) { //platform hit player
	m_pAudio->play(BOUNCE_SOUND);
	p0->m_vVelocity.y = 10.0f;
	} //else if
	/*MINER AND WARRIOR MOVING BOUNCE PLATFORM COLLISION END*/

	else if (t0 == FIN_SPRITE && t1 == MINER_SPRITE) { //player hit by rotational spike
		//isNext = true;
	} //else if

	else if (t0 == FIN_SPRITE && t1 == WARRIOR_SPRITE) { //player hit by rotational spike
		//isNext = true;
	} //else if

	else if (t1 == FIN_SPRITE && t0 == MINER_SPRITE) { //rotational spike hit by player
		//isNext = true;
			if (p0->GetPos().x > p1->GetPos().x - 75 && p0->GetPos().x < p1->GetPos().x + 110 && p1->GetPos().y > p0->GetPos().y) {
				p1->m_vVelocity.y = 30.0f;
				p0->CollisionResponse(p1->GetBoundingBox());
			}
	}

	else if (t1 == FIN_SPRITE && t0 == WARRIOR_SPRITE) { //rotational spike hit by player
	   //isNext = true;
	   if (p0->GetPos().x > p1->GetPos().x - 75 && p0->GetPos().x < p1->GetPos().x + 110) {
		   p1->m_vVelocity.y = 30.0f;
		   p0->CollisionResponse(p1->GetBoundingBox());
	   }
	}

	/*Splits miners up*/
	else if (t0 == MINER_SPRITE && t1 == MINER_SPRITE) {
		if (p1->GetPos().x > p0->GetPos().x) {
			p1->m_vVelocity.x = 10.0f;
			p0->m_vVelocity.x = -10.0f;
		}
		if (p0->GetPos().x > p1->GetPos().x) {
			p0->m_vVelocity.x = 10.0f;
			p1->m_vVelocity.x = -10.0f;
		}
	} //else if

		/*Splits miners and warriors up*/
	else if (t0 == MINER_SPRITE && t1 == WARRIOR_SPRITE) {
	if (p1->GetPos().x > p0->GetPos().x) {
		p1->m_vVelocity.x = 10.0f;
		p0->m_vVelocity.x = -10.0f;
	}
	if (p0->GetPos().x > p1->GetPos().x) {
		p0->m_vVelocity.x = 10.0f;
		p1->m_vVelocity.x = -10.0f;
	}
	} //else if

		/*Splits warriors up*/
	else if (t0 == WARRIOR_SPRITE && t1 == WARRIOR_SPRITE) {
	if (p1->GetPos().x > p0->GetPos().x) {
		p1->m_vVelocity.x = 10.0f;
		p0->m_vVelocity.x = -10.0f;
	}
	if (p0->GetPos().x > p1->GetPos().x) {
		p0->m_vVelocity.x = 10.0f;
		p1->m_vVelocity.x = -10.0f;
	}
	} //else if

	/*Splits miners up*/
	else if (t1 == MINER_SPRITE && t0 == MINER_SPRITE) { //spikes hit player
		if (p1->GetPos().x > p0->GetPos().x) {
			p1->m_vVelocity.x = 10.0f;
			p0->m_vVelocity.x = -10.0f;
		}
		if (p0->GetPos().x > p1->GetPos().x) {
			p0->m_vVelocity.x = 5.0f;
			p1->m_vVelocity.x = -5.0f;
		}
	} //else if


	/*Splits miners and warriors up*/
		else if (t1 == MINER_SPRITE && t0 == WARRIOR_SPRITE) { //spikes hit player
		if (p1->GetPos().x > p0->GetPos().x) {
			p1->m_vVelocity.x = 10.0f;
			p0->m_vVelocity.x = -10.0f;
		}
		if (p0->GetPos().x > p1->GetPos().x) {
			p0->m_vVelocity.x = 5.0f;
			p1->m_vVelocity.x = -5.0f;
		}
	} //else if

		else if (t1 == WARRIOR_SPRITE && t0 == WARRIOR_SPRITE) { //spikes hit player
		if (p1->GetPos().x > p0->GetPos().x) {
			p1->m_vVelocity.x = 10.0f;
			p0->m_vVelocity.x = -10.0f;
		}
		if (p0->GetPos().x > p1->GetPos().x) {
			p0->m_vVelocity.x = 5.0f;
			p1->m_vVelocity.x = -5.0f;
		}
	} //else if



	else if (t0 == SWITCH_SPRITE && t1 == MINER_SPRITE) { //player hit by rotational spike
	
		m_pDoor->kill();
		if (p0->m_nCurrentFrame == 0)
			m_pAudio->play(DOOR_SOUND);
		p0->m_nCurrentFrame = 1;
	} //else if
	else if (t1 == SWITCH_SPRITE && t0 == MINER_SPRITE) { //player hit by rotational spike
	
		m_pDoor->kill();
		if(p1->m_nCurrentFrame == 0)
			m_pAudio->play(DOOR_SOUND);
		p1->m_nCurrentFrame = 1;
	} //else if
	else if (t0 == SPIDER_SPRITE && t1 == MINER_SPRITE) { //player hit by rotational spike
	p1->kill();

	} //else if
	else if (t1 == SPIDER_SPRITE && t0 == MINER_SPRITE) { //player hit by rotational spike
	if (p0->m_nMinerScore > 0) {
		if (!p0->IsDead()) {
			for (int i = 0; i < 10; i++) {
				if (m_pOre[i] == NULL) {
					m_pOre[i] = create(GOLD_SPRITE, p0);
					m_pOre[i]->m_nMinerScore = p0->m_nMinerScore;
					m_nScore -= p0->m_nMinerScore;
					break;
				}
			}
		}
	}
	p0->kill();
	p0->DeathFX();
	} //else if

	else if (t0 == SPIKES_SPRITE && t1 == GOLD_SPRITE) { //gold is on spikes
	const float d = (p1->GetPos() - p0->GetPos()).Length();

	if (d < m_pRenderer->GetWidth(SPIKES_SPRITE) / 1.01f)
		p1->m_vVelocity.x = 10.0f; //move the gold

	else
		p1->m_vVelocity.x = 0.0f;
	} //else if

	else if (t1 == END_SPRITE && t0 == MINER_SPRITE) { //rotational spike hit by player
	//isNext = true;
	isNext = true;
	p1->kill();
	}

	else if (t1 == END_SPRITE && t0 == WARRIOR_SPRITE) { //rotational spike hit by player
	//isNext = true;
	isNext = true;
	p1->kill();
	}

	else if (t1 == DEATH_SPRITE && t0 == MINER_SPRITE) { //rotational spike hit by player
	p0->kill();
	p0->DeathFX(); // kill miniors who fall out of the level
	}

	else if (t1 == DEATH_SPRITE && t0 == WARRIOR_SPRITE) { //rotational spike hit by player
	p0->kill();
	p0->DeathFX(); // kill miniors who fall out of the level
	}

	else if (t1 == DOOR_SPRITE && t0 == MINER_SPRITE) { //player hit by rotational spike
	if (p0->GetPos().x > p1->GetPos().x - 100 && p0->GetPos().x < p1->GetPos().x + 110 && p0->GetPos().y > p1->GetPos().y - 100 && p0->GetPos().y < p1->GetPos().y + 110)
		p0->CollisionResponse(p1->GetBoundingBox());
	} //else if
	else if (t0 == DOOR_SPRITE && t1 == MINER_SPRITE) { //player hit by rotational spike
	if (p0->GetPos().x > p1->GetPos().x - 100 && p0->GetPos().x < p1->GetPos().x + 110 && p0->GetPos().y > p1->GetPos().y - 100 && p0->GetPos().y < p1->GetPos().y + 110)
		p1->CollisionResponse(p0->GetBoundingBox());
	} //else if

	else if (t1 == DOOR_SPRITE && t0 == WARRIOR_SPRITE) { //player hit by rotational spike
	if (p0->GetPos().x > p1->GetPos().x - 100 && p0->GetPos().x < p1->GetPos().x + 110 && p0->GetPos().y > p1->GetPos().y - 100 && p0->GetPos().y < p1->GetPos().y + 110)
		p0->CollisionResponse(p1->GetBoundingBox());
	} //else if

	else if (t1 == LGOBLIN_SPRITE && t0 == MINER_SPRITE) { //gold is on spikes
	if (p0->m_nMinerScore > 0) {
		if (!p0->IsDead()) {
			for (int i = 0; i < 10; i++) {
				if (m_pOre[i] == NULL) {
					m_pOre[i] = create(GOLD_SPRITE, p0);
					m_pOre[i]->m_nMinerScore = p0->m_nMinerScore;
					m_nScore -= p0->m_nMinerScore;
					break;
				}
			}
		}
	}
	p0->kill(); //move the gold
	p0->DeathFX();
	//}

	} //else if
	else if (t1 == RGOBLIN_SPRITE && t0 == MINER_SPRITE) { //gold is on spikes
			if (p0->m_nMinerScore > 0) {
				if (!p0->IsDead()) {
					for (int i = 0; i < 10; i++) {
						if (m_pOre[i] == NULL) {
							m_pOre[i] = create(GOLD_SPRITE, p0);
							m_pOre[i]->m_nMinerScore = p0->m_nMinerScore;
							m_nScore -= p0->m_nMinerScore;
							break;
						}
					}
				}
			}
			p0->kill(); //move the gold
			p0->DeathFX();
			//}
		}//else if
  } //if
} //NarrowPhase

int CObjectManager::GetScore() {
	return m_nScore;
}