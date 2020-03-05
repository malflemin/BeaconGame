/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "Renderer.h"
#include "ComponentIncludes.h"
#include "ParticleEngine.h"
#include <cmath>
#include "MouseControls.h"

/// Delete the renderer and the object manager.

CGame::~CGame(){
  delete m_pParticleEngine;
  delete m_pRenderer;
  delete m_pObjectManager;
} //destructor

/// Initialize the renderer and the object manager, load 
/// images and sounds, and begin the game.

void CGame::Initialize(){
  m_pRenderer = new CRenderer; 
  m_pRenderer->Initialize(NUM_SPRITES); 
  m_pRenderer->LoadImages(); //load images from xml file list

  m_pObjectManager = new CObjectManager; //set up the object manager 
  m_pAudio->Load(); //load the sounds for this game

  m_pParticleEngine = new CParticleEngine2D((CSpriteRenderer*)m_pRenderer);

  menu = 0;//initialize menu
  
  m_pAudio->loop(BCK1_SOUND);
  BeginGame();
} //Initialize

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create a player object
/// and a turret.

void CGame::CreateObjects(int menu){
		
	
		switch (curLevel) {
		case 1:
			m_pTrap[1] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(600.0f, 585.0f));
			m_pTrap[1]->SetOrientation(9.4f);
			m_pTrap[2] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(580.0f, 401.0f));
			m_pTrap[3] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(660.0f, 401.0f));

			/*miner creation loop*/
			for (nMiners = 0; nMiners < 3; nMiners++)
				m_pMiner[nMiners] = m_pObjectManager->create(MINER_SPRITE, Vector2(160.0f + 30 * nMiners, 450.0f));

			/*nWarriors = 1;
			m_pWarrior[0] = m_pObjectManager->create(WARRIOR_SPRITE, Vector2(160.0f, 450.0f));*/
			
				
			m_pOre[0] = m_pObjectManager->create(AMBER_SPRITE, Vector2(1400.0f, 450.0f));
			m_pOre[1] = m_pObjectManager->create(AMBER_SPRITE, Vector2(1550.0f, 450.0f));
			m_pOre[2] = m_pObjectManager->create(SAPPHIRE_SPRITE, Vector2(1700.0f, 250.0f));

			m_pObjectManager->create(PLATFORM_SPRITE, Vector2(550.0f, 400.0f));
			m_pObjectManager->create(PLATFORM_SPRITE, Vector2(625.0f, 400.0f));

			m_pTrap[4] = m_pObjectManager->create(BRIDGE_SPRITE, Vector2(1090.0f, 360.0f));
			m_pBridge2 = m_pObjectManager->create(BRIDGE_SPRITE, Vector2(1100.0f, -300.0f));
			m_pSwitch = m_pObjectManager->create(SWITCH_SPRITE, Vector2(60.0, 50.0f));

			m_pObjectManager->create(FIN_SPRITE, Vector2(1950.0f, 68.0f));
			m_pObjectManager->create(WEB_SPRITE, Vector2(810.0f, 250.0f));
			m_pSpider = m_pObjectManager->create(SPIDER_SPRITE, Vector2(820.0f, 280.0f));

			m_pDoor = m_pObjectManager->create(DOOR_SPRITE, Vector2(1200.0f, 205.0f));
			m_pObjectManager->create(SHADE_SPRITE, Vector2(462.0f, 190.0f));
			m_pObjectManager->create(END_SPRITE, Vector2(1950.0f, 700.0f));
			m_pObjectManager->create(DEATH_SPRITE, Vector2(1080.0f, -150.0f));

			m_pGoblinArm[0] = m_pObjectManager->create(GOBLINARM_SPRITE, Vector2(975.0f, 335.0f));
			m_pGoblinArm[1] = m_pObjectManager->create(GOBLINARM_SPRITE, Vector2(1200.0f, 305.0f));
			m_pGoblinArm[2] = m_pObjectManager->create(GOBLINARM_SPRITE, Vector2(975.0f, 271.0f));

			m_pTrap[5] = m_pObjectManager->create(LGOBLIN_SPRITE, Vector2(980.0f, 335.0f));
			m_pTrap[6] = m_pObjectManager->create(RGOBLIN_SPRITE, Vector2(1195.0f, 305.0f));
			m_pTrap[7] = m_pObjectManager->create(LGOBLIN_SPRITE, Vector2(980.0f, 271.0f));

			/*UI*/
			m_pMenu1 = m_pObjectManager->create(MENU1_SPRITE, Vector2(50.0f, 50.0f));
			m_pOne = m_pObjectManager->create(ONE_SPRITE, Vector2(50.0f, 50.0f));
			m_pTwo = m_pObjectManager->create(TWO_SPRITE, Vector2(50.0f, 50.0f));
			m_pThree = m_pObjectManager->create(THREE_SPRITE, Vector2(50.0f, 50.0f));
			/*UI end*/

			
			m_pPlayer = m_pObjectManager->create(PLAYER_SPRITE, Vector2(200.0f, 450.0f));
			
			break;

			case 2:   
				nMiners = 1;
				m_pObjectManager->create(RESULTSCREEN_SPRITE, Vector2(-50.0f, 0));
				m_pMiner[0] = m_pObjectManager->create(MINER_SPRITE, Vector2(160.0f + 30 * nMiners, -2000.0f));

				m_pObjectManager->create(BUTTON_SPRITE, Vector2(-20.0f, 200.0f));
				m_pObjectManager->create(BUTTON_SPRITE, Vector2(-20.0f, -0.0f));
				m_pObjectManager->create(BUTTON_SPRITE, Vector2(-20.0f, -300.0f));
				m_pPlayer = m_pObjectManager->create(PLAYER_SPRITE, Vector2(128.0f, 100.0f));
			
			break;
			case 3:
				//nMiners = 1;
				m_pObjectManager->create(PLATFORM_SPRITE, Vector2(360.0f, 45.0f));
				m_pObjectManager->create(MOVING_SPRITE, Vector2(130.0f, 125.0f));
				m_pObjectManager->create(MOVING_SPRITE, Vector2(360.0f, 250.0f));
				m_pObjectManager->create(MOVING_SPRITE, Vector2(130.0f, 250.0f));
				m_pTrap[0] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(250.0f, 145.0f));
				m_pTrap[1] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(100.0f, 435.0f));
				m_pTrap[2] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(492.0f, 367.0f));
				m_pObjectManager->create(MOVING_SPRITE, Vector2(1050.0f, 250.0f));
				;

				m_pObjectManager->create(MOVING_SPRITE, Vector2(1370.0f, 255.0f));
				m_pObjectManager->create(PLATFORM_SPRITE, Vector2(1380.0f, 170.0f));

				for (int s = 0; s < 5; s++) {
				m_pObjectManager->create(SPIKES_SPRITE, Vector2(1420.0f + (30*s), 180.0f));
				}
				m_pDoor = m_pObjectManager->create(DOOR_SPRITE, Vector2(810.0f, 210.0f));
				m_pOre[0] = m_pObjectManager->create(SAPPHIRE_SPRITE, Vector2(600.0f, 210.0f));
				m_pOre[1] = m_pObjectManager->create(BACON_SPRITE, Vector2(1250.0f, 360.0f));
				
				m_pOre[2] = m_pObjectManager->create(EMERALD_SPRITE, Vector2(100.0f, 100.0f));

				m_pSwitch = m_pObjectManager->create(SWITCH_SPRITE, Vector2(60.0, 435.0f));
				//m_pTrap[2] = m_pObjectManager->create(SPIKES_SPRITE, Vector2(660.0f, 401.0f));
				for (nMiners = 0; nMiners < 3; nMiners++)
					m_pMiner[nMiners] = m_pObjectManager->create(MINER_SPRITE, Vector2(1350.0f + 30 * nMiners, 100.0f));

				m_pObjectManager->create(DEATH_SPRITE, Vector2(1700.0f, -150.0f));

				m_pPlayer = m_pObjectManager->create(PLAYER_SPRITE, Vector2(128.0f, 100.0f));

				m_pObjectManager->create(FIN_SPRITE, Vector2(1700.0f, 200.0f));
				m_pObjectManager->create(END_SPRITE, Vector2(1700.0f, 700.0f));
				/*UI*/
				m_pMenu1 = m_pObjectManager->create(MENU1_SPRITE, Vector2(50.0f, 50.0f));
				m_pOne = m_pObjectManager->create(ONE_SPRITE, Vector2(50.0f, 50.0f));
				m_pTwo = m_pObjectManager->create(TWO_SPRITE, Vector2(50.0f, 50.0f));
				m_pThree = m_pObjectManager->create(THREE_SPRITE, Vector2(50.0f, 50.0f));
				/*UI end*/


				break;
		} //switch
	
} //CreateObjects

/// Call this function to start a new game. This
/// should be re-entrant so that you can start a
/// new game without having to shut down and restart the
/// program.

void CGame::BeginGame(){  
  m_pParticleEngine->clear(); //clear old particles
  m_pObjectManager->clear(); //clear old objects
  if(menu > 0)
  m_pObjectManager->LoadMap(curLevel); //load map
	m_pRenderer->SetBgColor(Colors::Black);

  CreateObjects(menu); //create new objects 
} //BeginGame
void CGame::NextLevel() {
	curLevel = (curLevel + 1);
	m_pObjectManager->resetDeadMinerCount();
	m_pObjectManager->resetPointers();
	if (curLevel == 2)
		curLevel = 3;
	if (curLevel > 3) {
		curLevel = 1;	}
	ShowCursor(FALSE); //hide cursor

	BeginGame();
	
} //NextLevel
/// Poll the keyboard state and respond to the
/// key presses that happened since the last frame.

void CGame::KeyboardHandler() {
	m_pKeyboard->GetState(); //get current keyboard state 

	if (menu == 0) {
		if (m_pKeyboard->TriggerDown(VK_F2)) {
			menu++;
			BeginGame();
		}
	}
	else if (menu >= 1 && m_pResultScreen==nullptr && m_pGameOverScreen==nullptr) {


		//Quick de-selection
		if (m_pKeyboard->TriggerDown('R')) {
			for (int i = 0; i < (*(&m_pMSelect + 1) - m_pMSelect); i++) {
				if (m_pMSelect[i] != nullptr) {
					m_pMSelect[i]->kill();
						if (m_pMiner[i] != nullptr)
							m_pMiner[i]->SetDisableState(false);
						if(m_pWarrior[i] != nullptr)
							m_pWarrior[i]->SetDisableState(false);
				}
			}		
		}

		if (m_pKeyboard->TriggerDown(VK_SPACE)) {
			if (curLevel == 2)
			{
				NextLevel();
			}
		}

		if (m_pKeyboard->TriggerDown(VK_BACK))
			BeginGame();

		if (m_pKeyboard->TriggerDown(VK_F1))
			m_bDrawAABBs = !m_bDrawAABBs;

		if (m_pKeyboard->Down(0x31)) {
			for (int i = 0; i < size; i++){
				if (m_pTrap[i] != nullptr && m_pTrap[i]->IsOnMenu1() && abs(m_pPlayer->GetPos().x - m_pTrap[i]->GetPos().x) < range && abs(m_pPlayer->GetPos().y - m_pTrap[i]->GetPos().y) < range) {
					m_pObjectManager->RecedeSpikes(m_pTrap[i]);
					m_pTrap[i]->SetDisableState(true);
				}
			}
		}

		if (!m_pKeyboard->Down(0x31) & !m_pKeyboard->Down(0x32)) {
			for (int i = 0; i < size; i++){
				if (m_pTrap[i] != nullptr)
					m_pObjectManager->ReleaseSpikes(m_pTrap[i]);
			}
		}

		if (m_pKeyboard->Down(0x32)) {
			for (int i = 0; i < size; i++){
				if (m_pTrap[i] != nullptr && m_pTrap[i]->IsOnMenu2() && abs(m_pPlayer->GetPos().x - m_pTrap[i]->GetPos().x) < range && abs(m_pPlayer->GetPos().y - m_pTrap[i]->GetPos().y) < range) {
					m_pObjectManager->RecedeSpikes(m_pTrap[i]);
					m_pTrap[i]->SetDisableState(true);
				}
			}
		}

		if (m_pKeyboard->TriggerDown(0x33)) {
			for (int i = 0; i < size; i++){
				if (m_pTrap[i] != nullptr && m_pTrap[i]->IsOnMenu3() && abs(m_pPlayer->GetPos().x - m_pTrap[i]->GetPos().x) < range && abs(m_pPlayer->GetPos().y - m_pTrap[i]->GetPos().y) < range) {
					m_pObjectManager->MoveBridge(m_pTrap[i]);
				}
			}
		}

		if (!m_pKeyboard->TriggerDown(0x33)) {
			for (int i = 0; i < size; i++){
				if (m_pTrap[i] != nullptr) {
					m_pObjectManager->ReverseBridge(m_pTrap[i]);
				}
			}
		}

		if (!m_pKeyboard->Down(0x33)) {
			for (int i = 0; i < size; i++){
				if (m_pTrap[i] != nullptr) {
					m_pObjectManager->ReverseBridge(m_pTrap[i]);
				}
			}
		}

		if (m_pKeyboard->TriggerDown(VK_LBUTTON)) {
			float x = m_pPlayer->GetPos().x;
			float y = m_pPlayer->GetPos().y;

			/*Miner selection code*/
			for (int i = 0; i < nMiners; i++) {
				if (m_pMiner[i] != nullptr) {
					bool fSelected = abs(x - m_pMiner[i]->GetPos().x) < 20 && abs(y - m_pMiner[i]->GetPos().y) < 20;
					if (!m_pMiner[i]->IsDisabled() && fSelected) {
						m_pMSelect[i] = m_pObjectManager->create(MSELECT_SPRITE, Vector2(m_pMiner[i]->GetPos()));
						m_pMiner[i]->SetDisableState(true);
					}
					else if (m_pMiner[i]->IsDisabled() && fSelected) {
						m_pMSelect[i]->kill();
						m_pMiner[i]->SetDisableState(false);
					}
					else if (m_pMiner[i]->IsDisabled() && !fSelected) {
						m_pMSelect[i]->SetVector(m_pMiner[i]->GetPos());
						m_pMiner[i]->SetState(true);
					}
				}
			}
			/*Miner selection code END*/


		for (int i = 0; i < nWarriors; i++) {
			if (m_pWarrior[i] != nullptr) {
				bool fSelected = abs(x - m_pWarrior[i]->GetPos().x) < 20 && abs(y - m_pWarrior[i]->GetPos().y) < 20;
				if (!m_pWarrior[i]->IsDisabled() && fSelected) {
					m_pMSelect[i+ (nMiners)] = m_pObjectManager->create(MSELECT_SPRITE, Vector2(m_pWarrior[i]->GetPos()));
					m_pWarrior[i]->SetDisableState(true);
				}
				else if (m_pWarrior[i]->IsDisabled() && fSelected) {
					m_pMSelect[i + (nMiners)]->kill();
					m_pWarrior[i]->SetDisableState(false);
				}
				else if (m_pWarrior[i]->IsDisabled() && !fSelected) {
					m_pMSelect[i + (nMiners)]->SetVector(m_pWarrior[i]->GetPos());
					m_pWarrior[i]->SetState(true);
				}
			}
		}
	}
	}
	else if (menu > 0 && m_pResultScreen != nullptr) {
		if (m_pKeyboard->TriggerDown(VK_SPACE)) {
			m_pResultScreen = nullptr;
			m_pStar[0] = nullptr;
			m_pStar[1] = nullptr;
			m_pStar[2] = nullptr;
			NextLevel();
			m_pObjectManager->CurrentFloor();
		}
	}
	else if (menu > 0 && m_pGameOverScreen != nullptr) {
	if (m_pKeyboard->TriggerDown(VK_SPACE)) {
		m_pObjectManager->resetPointers();
		BeginGame();
		m_pGameOverScreen = nullptr;
		m_pObjectManager->resetDeadMinerCount();
		m_pObjectManager->CurrentFloor();
	}
	}
	if (m_pKeyboard->TriggerDown(VK_F2)) {
		//menu++;
	   //  curLevel++;
		NextLevel();
		m_pObjectManager->CurrentFloor();
	}
	
}


/// Poll the XBox controller state and respond to the
/// controls there.

void CGame::ControllerHandler(){
  if(!m_pController->IsConnected())return;

  m_pController->GetState(); //get state of controller's controls 
  
  m_pPlayer->SetSpeed(100*m_pController->GetRTrigger());

  if(m_pController->GetRTrigger() == 0)
    m_pPlayer->SetSpeed(-100*m_pController->GetLTrigger());

  m_pPlayer->SetRotSpeed(-2.0f*m_pController->GetRThumb().x);

  if(m_pController->GetButtonLSToggle())
    m_pPlayer->Jump();
  
  if(m_pController->GetButtonAToggle())
    BeginGame();
  
  if(m_pController->GetButtonBToggle())
    m_bDrawAABBs = !m_bDrawAABBs;}
 //ControllerHandler

/// Ask the object manager to draw the game objects. RenderWorld
/// is notified of the start and end of the frame so
/// that it can let Direct3D do its pipelining jiggery-pokery.

void CGame::RenderFrame() {
	m_pRenderer->BeginFrame();
	m_pObjectManager->draw();
	m_pParticleEngine->Draw();
	m_pObjectManager->draw();
	m_pParticleEngine->Draw();
	if (menu == 0) {
		string s = "F2: Play";
		m_pRenderer->DrawScreenText(s.c_str(), Vector2(45.0f, 550.0f), Colors::White);
		m_pObjectManager->create(BACK_SPRITE, Vector2(512.0f, 384.0f));
		m_pObjectManager->create(PLAY_SPRITE, Vector2(100.0f, 100.0f));
	}
	if (menu > 0) {
		if (m_pResultScreen == nullptr && m_pGameOverScreen==nullptr) {
			string s = "Score: " + to_string(m_pObjectManager->GetScore());
			m_pRenderer->DrawScreenText(s.c_str(), Vector2(30.0f, 30.0f), Colors::White);
			if (curLevel == 2) {
				s = "Warrior - 50";
				m_pRenderer->DrawScreenText(s.c_str(), Vector2(450.0f, 150.0f), Colors::White);
				s = "Helm - 20";
				m_pRenderer->DrawScreenText(s.c_str(), Vector2(450.0f, 350.0f), Colors::White);
				s = "Continue";
				m_pRenderer->DrawScreenText(s.c_str(), Vector2(450.0f, 650.0f), Colors::White);
			}
		}
		else if (m_pResultScreen!=nullptr) {
			string s = "Score: " + to_string(m_pObjectManager->GetScore());
			m_pRenderer->DrawScreenText(s.c_str(), Vector2(450.0f, 300.0f), Colors::White);
			string s2 = "Press Space to Continue ";
			m_pRenderer->DrawScreenText(s2.c_str(), Vector2(350.0f, 600.0f), Colors::White);
		}
		else if (m_pGameOverScreen != nullptr) {
			string s = "GAME OVER";
			m_pRenderer->DrawScreenText(s.c_str(), Vector2(425.0f, 250.0f), Colors::Red);
			string s3 = "Final Score: " + to_string(m_pObjectManager->GetScore());
			m_pRenderer->DrawScreenText(s3.c_str(), Vector2(425.0f, 350.0f), Colors::White);
			string s2 = "Press Space to Restart ";
			m_pRenderer->DrawScreenText(s2.c_str(), Vector2(380.0f, 610.0f), Colors::White);
		}
		if (m_pObjectManager->isNext == true) {
			//NextLevel();
			//m_pResultScreen = m_pObjectManager->create(RESULTSCREEN_SPRITE, Vector2(512.0f, 384.0f));
			m_pObjectManager->getScoreSpecs(curLevel);
			m_pObjectManager->isNext = false;
		}

		if (nMiners > 0) {
			/*selection follows miner sprite*/
			for (int i = 0; i < nMiners; i++) {
				if (m_pMiner[i]->IsDisabled() && !m_pMiner[i]->IsDead())
					m_pMSelect[i]->SetVector(m_pMiner[i]->GetPos());
				if (m_pMiner[i]->IsDead())
					m_pMSelect[i]->kill();
			}
			/*end of selection follow*/
		}

			if (nWarriors> 0) {
				/*selection follows warrior sprite*/
				for (int i = 0; i < nWarriors; i++) {
					if (m_pWarrior[i]->IsDisabled() && !m_pWarrior[i]->IsDead())
						m_pMSelect[i + (nMiners)]->SetVector(m_pWarrior[i]->GetPos());
					if (m_pWarrior[i]->IsDead())
						m_pMSelect[i + (nMiners)]->kill();
				}
				/*end of selection follow*/
		}

			if (m_pGameOverScreen == nullptr){
					m_pObjectManager->getDeadMinerCount();
			}
			else if (m_pGameOverScreen != nullptr) {
				m_pGameOverScreen->SetDisableState(false);
			}
	}
  m_pRenderer->EndFrame();
} //RenderFrame

/// Make the camera follow the player, but don't let it get
/// too close to the edge. Unless the world is smaller than
/// the window, in which case we center everything.

void CGame::FollowCamera(){
	if (menu == 0) {
		float x = m_pMouse->GetPointsX(NULL);
		float y = m_pMouse->GetPointsY(700.0f);
		//m_pPlayer->SetVector(x, y);
	}
	else if (menu > 0) {
		Vector3 vCameraPos(m_pPlayer->GetPos()); //player position
		Vector2 vMenuPos; //Trap Selection UI definition
		Vector2 vMenuTop;
		float y;
		if (curLevel == 3) {
			vCameraPos.x = m_pMouse->GetPointsX(NULL) + 512.0f;
		}
		else {
			vCameraPos.x = m_pMouse->GetPointsX(NULL) + 512.0f;
		}

		float x = m_pMouse->GetPointsX(vCameraPos.x);
		if (curLevel == 2) {
			x = m_pMouse->GetPointsX(-12.0f);
		}
		if(curLevel == 1)
			y = m_pMouse->GetPointsY(700.0f);
		if (curLevel == 2)
			y = m_pMouse->GetPointsY(442.0f);
		if (curLevel == 3) {
			y = m_pMouse->GetPointsY(692.0f);
		}
		camposx = vCameraPos.x;

		if (m_vWorldSize.x > m_nWinWidth) { //world wider than screen
			vCameraPos.x = max(vCameraPos.x, m_nWinWidth / 2.0f); //stay away from the left edge
			vCameraPos.x = min(vCameraPos.x, m_vWorldSize.x - m_nWinWidth / 2.0f);  //stay away from the right edge
		} //if


		else vCameraPos.x = m_vWorldSize.x / 2.0f; //center horizontally.
	 // vCameraPos.x = m_vWorldSize.x/2.0f; //center horizontally.

		if (m_vWorldSize.y > m_nWinHeight) { //world higher than screen
			vCameraPos.y = max(vCameraPos.y, m_nWinHeight / 2.0f);  //stay away from the bottom edge
			vCameraPos.y = min(vCameraPos.y, m_vWorldSize.y - m_nWinHeight / 2.0f); //stay away from the top edge
		} //if

		else vCameraPos.y = m_vWorldSize.y / 2.0f; //center vertically
		
		/*MENU ITEMS*/
		vMenuPos.x = vCameraPos.x - 450.0f;//Follows camera position X
		vMenuPos.y = vCameraPos.y - 100.0f;//Follows camera position Y
		/*MENU ITEMS END*/
		/*PLACE SPIKE IN FIRST ITEM SLOT IN RANGE*/
		if (m_pResultScreen == nullptr && m_pGameOverScreen==nullptr) {
			for (int i = 0; i < size; i++) {
				if (m_pTrap[i] != nullptr) {
					if (abs(m_pPlayer->GetPos().x - m_pTrap[i]->GetPos().x) < range &&
						abs(m_pPlayer->GetPos().y - m_pTrap[i]->GetPos().y) < range) {
						if (m_pTrap[i]->m_nSpriteIndex == SPIKES_SPRITE) {
							if (m_pPlat == nullptr && !m_pTrap[i]->IsOnMenu2()) {
								m_pPlat = m_pObjectManager->create(ISPIKE_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu1(true);
								m_pPlat->SetVector(vMenuPos.x, vMenuPos.y + 60);
								m_pOne->kill();
							}//if
							else if (m_pPlat != nullptr)
								m_pPlat->SetVector(vMenuPos.x, vMenuPos.y + 60);

							if (m_pPlat2 == nullptr && !m_pTrap[i]->IsOnMenu1()) {
								m_pPlat2 = m_pObjectManager->create(ISPIKE_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu2(true);
								m_pPlat2->SetVector(vMenuPos.x, vMenuPos.y + 10);
								m_pTwo->kill();
							}//if
							else if (m_pPlat2 != nullptr)
								m_pPlat2->SetVector(vMenuPos.x, vMenuPos.y + 10);
							break;
						}//if
						else if (m_pTrap[i]->m_nSpriteIndex == LGOBLIN_SPRITE) {
							if (m_pPlat == nullptr && !m_pTrap[i]->IsOnMenu2()) {
								m_pPlat = m_pObjectManager->create(ILGOBLIN_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu1(true);
								m_pPlat->SetVector(vMenuPos.x, vMenuPos.y + 60);
								m_pOne->kill();
							}//if
							else if (m_pPlat != nullptr)
								m_pPlat->SetVector(vMenuPos.x, vMenuPos.y + 60);

							if (m_pPlat2 == nullptr && !m_pTrap[i]->IsOnMenu1()) {
								m_pPlat2 = m_pObjectManager->create(ILGOBLIN_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu2(true);
								m_pPlat2->SetVector(vMenuPos.x, vMenuPos.y + 10);
								m_pTwo->kill();
							}//if
							else if (m_pPlat2 != nullptr)
								m_pPlat2->SetVector(vMenuPos.x, vMenuPos.y + 10);
						}//else if
						else if (m_pTrap[i]->m_nSpriteIndex == RGOBLIN_SPRITE) {
							if (m_pPlat == nullptr && !m_pTrap[i]->IsOnMenu2()) {
								m_pPlat = m_pObjectManager->create(IRGOBLIN_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu1(true);
								m_pPlat->SetVector(vMenuPos.x, vMenuPos.y + 60);
								m_pOne->kill();
							}//if
							else if (m_pPlat != nullptr)
								m_pPlat->SetVector(vMenuPos.x, vMenuPos.y + 60);

							if (m_pPlat2 == nullptr && !m_pTrap[i]->IsOnMenu1()) {
								m_pPlat2 = m_pObjectManager->create(IRGOBLIN_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu2(true);
								m_pPlat2->SetVector(vMenuPos.x, vMenuPos.y + 10);
								m_pTwo->kill();
							}//if
							else if (m_pPlat2 != nullptr)
								m_pPlat2->SetVector(vMenuPos.x, vMenuPos.y + 10);
						}//else if
						else if (m_pTrap[i]->m_nSpriteIndex == BRIDGE_SPRITE) {
							if (m_pPlat3 == nullptr) {
								m_pPlat3 = m_pObjectManager->create(IBRIDGE_SPRITE, Vector2(vMenuPos));
								m_pTrap[i]->SetIsOnMenu3(true);
								m_pPlat3->SetVector(vMenuPos.x, vMenuPos.y - 45);
								m_pThree->kill();
							}//if
							else if (m_pPlat3 != nullptr)
								m_pPlat3->SetVector(vMenuPos.x, vMenuPos.y - 45);
						}

					}//if
					else {
						if (m_pPlat != nullptr) {
							m_pPlat->kill();
							m_pPlat = nullptr;
							m_pTrap[i]->SetIsOnMenu1(false);
							m_pOne = m_pObjectManager->create(ONE_SPRITE, Vector2(vMenuPos));
						}//if
						else if (m_pPlat2 != nullptr) {
							m_pPlat2->kill();
							m_pPlat2 = nullptr;
							m_pTrap[i]->SetIsOnMenu2(false);
							m_pTwo = m_pObjectManager->create(TWO_SPRITE, Vector2(vMenuPos));
						}//else if
						else if (m_pPlat3 != nullptr) {
							m_pPlat3->kill();
							m_pPlat3 = nullptr;
							m_pTrap[i]->SetIsOnMenu3(false);
							m_pThree = m_pObjectManager->create(THREE_SPRITE, Vector2(vMenuPos));
						}//else if
					}//else
				}//if
			}//for
		}
		/*PLACE SPIKE IN FIRST ITEM SLOT IN RANGE END*/
		m_pRenderer->SetCameraPos(vCameraPos); //camera to player
		m_pMenu1->SetVector(vMenuPos);
		m_pOne->SetVector(vMenuPos.x, vMenuPos.y + 60);
		m_pTwo->SetVector(vMenuPos.x, vMenuPos.y + 10);
		m_pThree->SetVector(vMenuPos.x, vMenuPos.y - 45);
		m_pPlayer->SetVector(x, y);
		if (m_pResultScreen != nullptr) {
			m_pResultScreen->SetVector(vMenuPos.x+450, vMenuPos.y+100);
		}
		if (m_pStar[0] != nullptr) {
			m_pStar[0]->SetVector(vMenuPos.x + 400, vMenuPos.y + 100);
		}
		if (m_pStar[1] != nullptr) {
			m_pStar[1]->SetVector(vMenuPos.x + 450, vMenuPos.y + 100);
		}
		if (m_pStar[2] != nullptr) {
			m_pStar[2]->SetVector(vMenuPos.x + 500, vMenuPos.y + 100);
		}
		if (m_pGameOverScreen != nullptr) {
			m_pGameOverScreen->SetVector(vMenuPos.x + 450, vMenuPos.y + 100);
		}
	}
} //FollowCamera

/// Handle keyboard input, move the game objects and render 
/// them in their new positions and orientations. Notify the 
/// audio player at the start of each frame so that it can 
/// prevent multiple copies of a sound from starting on the
/// same frame. Notify the timer of the start and end of the
/// frame so that it can calculate frame time. 

void CGame::ProcessFrame(){
  KeyboardHandler(); //handle keyboard input
  ControllerHandler(); //handle controller input
  m_pAudio->BeginFrame(); //notify audio player that frame has begun
  
  m_pStepTimer->Tick([&](){ 
    m_pObjectManager->move(); //move all objects
    FollowCamera(); //make camera follow player
    m_pParticleEngine->step(); //advance particle animation
  });

  RenderFrame(); //render a frame of animation
} //ProcessFrame
