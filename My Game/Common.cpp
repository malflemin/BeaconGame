/// \file Common.cpp
/// \brief Code for the class CCommon.
///
/// This file contains declarations and initial values
/// for CCommon's static member variables.

#include "Common.h"

CRenderer* CCommon::m_pRenderer = nullptr;
CObjectManager* CCommon::m_pObjectManager = nullptr;
CParticleEngine2D* CCommon::m_pParticleEngine = nullptr;

Vector2 CCommon::m_vWorldSize = Vector2::Zero;
bool CCommon::m_bDrawAABBs = false;
int CCommon::size = 32;
float CCommon::range = 150.0f;
CObject* CCommon::m_pPlay = nullptr;
CObject* CCommon::m_pPlayer = nullptr;
CObject* CCommon::m_pMiner[32] = {nullptr};
CObject* CCommon::m_pWarrior[32] = { nullptr };
CObject* CCommon::m_pSpider = nullptr;
CObject* CCommon::m_pMSelect[32] = { nullptr };
CObject* CCommon::m_pMenu1 = nullptr;
CObject* CCommon::m_pOre[32] = { nullptr };
//CObject* CCommon::m_pSpikes = nullptr;
CObject* CCommon::m_pTrap[32] = { nullptr };
CObject* CCommon::m_pSwitch = nullptr;
CObject* CCommon::m_pRotSpike = nullptr;
CObject* CCommon::m_pBridge = nullptr;
CObject* CCommon::m_pBridge2 = nullptr;
CObject* CCommon::m_pDoor = nullptr;
CObject* CCommon::m_pPlat = nullptr;
CObject* CCommon::m_pPlat2 = nullptr;
CObject* CCommon::m_pPlat3 = nullptr;
CObject* CCommon::m_pOne = nullptr;
CObject* CCommon::m_pTwo = nullptr;
CObject* CCommon::m_pThree = nullptr;
CObject* CCommon::m_pResultScreen = nullptr;
CObject* CCommon::m_pStar[3] = { nullptr };
CObject* CCommon::m_pLGoblin = nullptr;
CObject* CCommon::m_pRGoblin = nullptr;
CObject* CCommon::m_pGoblinH[32] = { nullptr };
CObject* CCommon::m_pGoblinArm[32] = { nullptr };
CObject* CCommon::m_pGameOverScreen = nullptr;
CObject* CCommon::m_pMovingPlat = nullptr;
CMouse* CCommon::m_pMouse = nullptr;  ///<Pointer to the mouse