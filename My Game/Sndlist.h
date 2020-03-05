/// \file SndList.h
/// \brief Enumerated type for sounds.

#pragma once

#include "Sound.h"

/// \brief Game sound enumerated type. 
///
/// These are the sounds used in actual gameplay. 
/// The sounds must be listed here in the same order that
/// they are in the sound settings XML file.

enum eSoundType{ 
  GUN_SOUND, RICOCHET_SOUND, OW_SOUND, CLANG_SOUND, TIMER_SOUND, BOUNCE_SOUND, DOOR_SOUND, BCK1_SOUND, MINING_SOUND, DEATH_SOUND
}; //eSoundType