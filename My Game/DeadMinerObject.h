/// \file DeadMinerObject.h
/// \brief Interface for the dead miner object CDeadMinerObject.

#pragma once

#include "Object.h"

/// \brief Dead miner object.
///
/// The dead miner object lands on the ground, waiting to be mined.

class CDeadMinerObject : public CObject {
private:

public:
	CDeadMinerObject(const Vector2& pos, const Vector2& vel); ///< Constructor.
};