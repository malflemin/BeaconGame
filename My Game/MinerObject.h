/// \file Object.h
/// \brief Interface for the game object class CObject.

#pragma once

#include "GameDefines.h"
#include "Renderer.h"
#include "Common.h"
#include "Component.h"
#include "SpriteDesc.h"
#include "Object.h"

/// \brief The game object. 
///
/// CObject is the abstract representation of an object.

class CMinerObject :
	public CCommon,
	public CComponent,
	public CSpriteDesc2D,
	public CObject
{
	friend class CObjectManager;

private:
	enum eStateType {
		STATIC_STATE, FOLLOWING_STATE
	}; //eStateType

public:
	CMinerObject(eSpriteType t, const Vector2& p) :CObject(t, p) {

	};///< Constructor.
	void Think(); ///< Artificial intelligence.
	void StaticAi(); ///< Ai for cruising along.
	void FollowingAi(); ///< Ai for avoiding plane.
	void SetState(eStateType state); ///< Change state

}; //CObject