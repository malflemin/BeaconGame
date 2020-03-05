#pragma once

#include "WindowDesc.h"

/// \brief The mouse controls.
///
/// The mouse controls returns the x and y position of the mouse and
/// adjusts the x and y positions in respect to the camera

class CMouse : public CWindowDesc {

private:

public:
	CMouse(); ///< Constructor.
	float GetPointsX(float x);
	float GetPointsY(float y);
	
}; //CMouse