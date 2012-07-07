#include "ViewAutoScale.h"

#define DESIGN_W (480.0f)
#define DESIGN_H (320.0f)

float ViewAutoScale::GetScaleX() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return winSize.width / DESIGN_W;
}

float ViewAutoScale::GetScaleY() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return winSize.height / DESIGN_H;
}

float ViewAutoScale::GetCenterX() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return winSize.width / 2.0f;
}

float ViewAutoScale::GetCenterY() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return winSize.height / 2.0f;
}

CCPoint ViewAutoScale::GetCenterXY() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	return ccp(winSize.width / 2.0f, winSize.height / 2.0f);
}

inline CCPoint ViewAutoScale::GetScreenPoint(float x, float y,
		Alignment alignment) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	const float scaleX = winSize.width / DESIGN_W;
	const float scaleY = winSize.height / DESIGN_H;

	CCPoint result;

	if (alignment % 3 == 0) {
		result.x = x * scaleX;
	} else if (alignment % 3 == 2) {
		result.x = winSize.width + x * scaleX;
	} else {
		result.x = winSize.width / 2.0f + x * scaleY;
	}

	if (alignment / 3 == 0) {
		result.y = y * scaleY;
	} else if (alignment / 3 == 2) {
		result.y = winSize.height + y * scaleY;
	} else {
		result.y = winSize.height / 2.0f + y * scaleY;
	}

	return result;
}

CCPoint ViewAutoScale::GetScreenPoint(const CCPoint& point, Alignment alignment) {
	return GetScreenPoint(point.x, point.y, alignment);
}
