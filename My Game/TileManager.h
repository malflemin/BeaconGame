/// \file TileManager.h
/// \brief Interface for the tile manager CTileManager.

#pragma once

#include <vector>

using namespace std;
#include "Settings.h"
#include "Common.h"
#include "Sprite.h"
#include "GameDefines.h"

/// \brief The tile manager.
///
/// The tile manager is responsible for the
/// tile-based background.

class CTileManager : public CCommon, CSettings {
private:
	int m_nWidth = 0; ///< Number of tiles wide.
	int m_nHeight = 0; ///< Number of tiles high.
	vector<Vector2> m_vecTurrets; ///< Positions of turrets.
	float m_fTileSize; ///< Tile width and height.
	Vector2 m_vTileRadius; ///< Tile radius.

	char** m_chMap = nullptr; ///< The level map.

	vector<BoundingBox> m_vecWalls; ///< AABBs for the walls.

	void MakeBoundingBoxes(); ///< Make bounding boxes for walls.

public:
	CTileManager(size_t tilesize); ///< Constructor.
	~CTileManager(); ///< Destructor.

	void LoadMap(char* filename); ///< Load a map.
	void Draw(eSpriteType t); ///< Draw the map with a given tile.
	void DrawBoundingBoxes(eSpriteType t); ///< Draw the bounding boxes.
	void LoadMapFromImageFile(char* filename); ///< Load map.
	vector<Vector2> GetTurrets() { return m_vecTurrets; }; ///< Get turrets.
	bool Visible(const Vector2& v0, const Vector2& v1, float radius); ///< Check visibility.

	template<class t> bool CollideWithWall(const t& s, vector<BoundingBox>& walls); ///< Check object collision with a wall.
}; //CTileManager

/// \brief Template for bounding shape collisions.
/// 
/// Determine whether a bounding shape intersects a wall. If it does,
/// then the second parameter is set to the walls that it collided with,
/// which will usually be one or two walls (one horizontal, one vertical).
/// \param s A bounding shape.
/// \param walls [OUT] A vector of the walls that collided with. 
/// \return true if the bounding shape intersects a wall.

template<class t> bool CTileManager::CollideWithWall(const t& s, vector<BoundingBox>& walls) {
	bool hit = false;
	walls.clear();

	for (auto wall : m_vecWalls) {
		if (s.Intersects(wall)) {
			hit = true;
			walls.push_back(wall);
		} //if
	} //for

	return hit;
} //CollideWithWall