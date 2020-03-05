/// \file MouseControls.cpp
/// \brief Code for the mouse class CMouse.
#include "MouseControls.h"
#include "Common.h"


CMouse::CMouse() {

}

float CMouse::GetPointsX(float x){
	POINT p;
	if (GetCursorPos(&p)) {
			if (ScreenToClient(m_Hwnd, &p))
			{
				if (x != NULL) {
					p.x = p.x + x -512.0f;
				}
					return p.x;
			}
	}

}

float CMouse::GetPointsY(float y){
	POINT p;
	if (GetCursorPos(&p)) {
		if (ScreenToClient(m_Hwnd, &p))
		{
			p.y = -p.y + y;
			return p.y;
		}
	}
}