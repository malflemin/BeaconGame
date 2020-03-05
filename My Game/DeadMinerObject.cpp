/// \file DeadCrowObject.cpp
/// \brief Code for the dead crow object CDeadCrowObject.

#include "DeadMinerObject.h"
#include "SndList.h"

/// \param pos Initial position.
/// \param vel Initial velocity.

CDeadMinerObject::CDeadMinerObject(const Vector2& pos, const Vector2& vel) :
	CObject(GOLD_SPRITE, pos)
{
	m_vVelocity.x = 0.5f * m_vVelocity.x;
	m_vVelocity.y = -80.0f;
} //constructor