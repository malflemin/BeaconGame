/// \file Object.h
/// \brief Interface for the game object class CObject.

#pragma once
#include "MinerObject.h"
#include "ComponentIncludes.h"
#include "Tilemanager.h"
#include "GameDefines.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Object.h"

/// \brief The game object. 
///
/// CObject is the abstract representation of an object.

void CMinerObject::Think() {
} ///< Artificial intelligence.
void CMinerObject::StaticAi() {
}///< Ai for cruising along.
void CMinerObject::FollowingAi() {
}///< Ai for avoiding plane.
void CMinerObject::SetState(eStateType state) {
}///< Change state