/// \file Game.h
/// \brief Interface for the game class CGame.

#pragma once

#include "Component.h"
#include "Common.h"
#include "ObjectManager.h"
#include "Settings.h"

/// \brief The game class.

class CGame: 
  public CComponent, 
  public CSettings,
  public CCommon{ 

  private:
	int nMiners;
	int nWarriors;
	int menu = 0;
	int curLevel = 0;
	bool m_bDisable = false;
	bool fSelected = false;
    void BeginGame(); ///< Begin playing the game.
    void KeyboardHandler(); ///< The keyboard handler.
    void ControllerHandler(); ///< The controller handler.
    void RenderFrame(); ///< Render an animation frame.
	void NextLevel();// load next level
    void CreateObjects(int menu); ///< Create game objects.
    void FollowCamera(); ///< Make camera follow player character.
		float camposx;

  public:
    ~CGame(); ///< Destructor.
	
    void Initialize(); ///< Initialize the game.
    void ProcessFrame(); ///< Process an animation frame.
    void Release(); ///< Release the renderer.
	void setMenu(int n);
	int getMenu();
}; //CGame
