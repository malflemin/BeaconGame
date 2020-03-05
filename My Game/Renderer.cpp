/// \file Renderer.cpp
/// \brief Code for the renderer class CRenderer.

#include "Renderer.h"
#include "ComponentIncludes.h"
#include "Abort.h"

CRenderer::CRenderer():
  CSpriteRenderer(Batched2D){
} //constructor

/// Load the specific images needed for this game.
/// This is where eSpriteType values from GameDefines.h get
/// tied to the names of sprite tags in gamesettings.xml. Those
/// sprite tags contain the name of the corresponding image file.
/// If the image tag or the image file are missing, then
/// the game should abort from deeper in the Engine code,
/// leaving you with a dialog box that tells you what
/// went wrong.

void CRenderer::LoadImages(){  
  BeginResourceUpload();

  Load(TILE_SPRITE, "tile"); 
  Load(PLAYER_SPRITE, "player");
  Load(GREENLINE_SPRITE, "greenline");
  Load(BULLET_SPRITE, "bullet");
  Load(BULLET2_SPRITE, "bullet2");
  Load(SMOKE_SPRITE, "smoke");
  Load(SPARK_SPRITE, "spark");
  Load(TURRET_SPRITE, "turret");
  Load(SPIKES_SPRITE, "spikes");
  Load(AMBER_SPRITE, "amber");
  Load(MINER_SPRITE, "miner");
  Load(WARRIOR_SPRITE, "warrior");
  Load(PLATFORM_SPRITE, "platform");
  Load(PLAY_SPRITE, "play");
  Load(GOLD_SPRITE, "gold");
  Load(BRIDGE_SPRITE, "bridge");
  Load(ROT_SPRITE, "rot");
  Load(FIN_SPRITE, "finish");
  Load(BLOOD_SPRITE, "blood");
  Load(MENU1_SPRITE, "menu");
  Load(ISPIKE_SPRITE, "ispike");
	Load(IBRIDGE_SPRITE, "ibridge");
	Load(ILGOBLIN_SPRITE, "ilgoblin");
	Load(IRGOBLIN_SPRITE, "irgoblin");
  Load(MSELECT_SPRITE, "mselect");
  Load(WEB_SPRITE, "web");
  Load(SPIDER_SPRITE, "spider");
  Load(SWITCH_SPRITE, "switch");
  Load(DOOR_SPRITE, "door");
  Load(SHADE_SPRITE, "fshade");
  Load(BACK_SPRITE, "back");
	Load(END_SPRITE, "endlvl");
	Load(DEATH_SPRITE, "death");
	Load(SAPPHIRE_SPRITE, "sapphire");
	Load(RUBY_SPRITE, "ruby");
	Load(EMERALD_SPRITE, "emerald");
	Load(AMETHYST_SPRITE, "amethyst");
	Load(DIAMOND_SPRITE, "diamond");
	Load(BACON_SPRITE, "cavebacon");
	Load(ONE_SPRITE, "one");
	Load(TWO_SPRITE, "two");
	Load(THREE_SPRITE, "three");
	Load(STAR_SPRITE, "star");
	Load(BLANKSTAR_SPRITE, "blankstar");
	Load(RESULTSCREEN_SPRITE, "resultscreen");
	Load(LGOBLIN_SPRITE, "lgoblinhand");
	Load(RGOBLIN_SPRITE, "rgoblinhand");
	Load(GOBLINARM_SPRITE, "goblinarm");
	Load(GAMEOVER_SPRITE, "gameover");
	Load(BUTTON_SPRITE, "button");
	Load(MOVING_SPRITE, "platform");
  EndResourceUpload();
} //LoadImages

void CRenderer::LoadMenu() {
	BeginResourceUpload();

	Load(PLAY_SPRITE, "play");

	EndResourceUpload();
}

/// Draw an axially aligned bounding box using the green line sprite.
/// \param aabb An axially aligned bounding box.

void CRenderer::DrawBoundingBox(const BoundingBox& aabb){
  const Vector3 center = aabb.Center;
  const Vector3 extent = aabb.Extents;
  
  const Vector2 topleft(center.x - extent.x, center.y + extent.y);
  const Vector2 topright(center.x + extent.x, center.y + extent.y);
  const Vector2 bottomleft(center.x - extent.x, center.y - extent.y);
  const Vector2 bottomright(center.x + extent.x, center.y - extent.y);
  
  DrawLine(GREENLINE_SPRITE, topleft, topright);
  DrawLine(GREENLINE_SPRITE, bottomleft, bottomright);
  DrawLine(GREENLINE_SPRITE, topleft, bottomleft);
  DrawLine(GREENLINE_SPRITE, topright, bottomright);
} //DrawBoundingBox


