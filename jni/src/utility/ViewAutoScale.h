#ifndef _VIEW_AUTO_SCALE_H
#define _VIEW_AUTO_SCALE_H

#include "cocos2d.h"
using namespace cocos2d;

enum Alignment {
	ALIGNMENT_LB = 0, // left bottom
	ALIGNMENT_CB = 1, // center bottom
	ALIGNMENT_RB = 2, // right bottom
	ALIGNMENT_LC = 3, // left center
	ALIGNMENT_CC = 4, // center center
	ALIGNMENT_RC = 5, // right center
	ALIGNMENT_LT = 6, // left top
	ALIGNMENT_CT = 7, // center top
	ALIGNMENT_RT = 8,
// right top
};

class ViewAutoScale {
public:
	static float GetScaleX();
	static float GetScaleY();
	static float GetCenterX();
	static float GetCenterY();
	static CCPoint GetCenterXY();
	static CCPoint GetScreenPoint(float x, float y, Alignment alignment);
	static CCPoint GetScreenPoint(const CCPoint& point, Alignment alignment);
};
#endif
