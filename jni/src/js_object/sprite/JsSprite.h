#ifndef _JS_SPRITE_H
#define _JS_SPRITE_H
#include "cocos2d.h"
#include "StateMachine.h"
#include "StateMachineDefine.h"
using namespace cocos2d;

class JsSprite: public CCSprite {
	STATE_MACHINE_DEFINE( JsSprite);
public:
	JsSprite();
	virtual ~JsSprite();
	virtual bool init();
public:
	static JsSprite* SpriteWithFile(const char *pszFileName);
	static JsSprite
	* SpriteWithFile(const char *pszFileName, const CCRect& rect);
	static JsSprite* SpriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	static JsSprite
	* SpriteWithTexture(CCTexture2D *pTexture, const CCRect &rect);
	static JsSprite
	* SpriteWithTexture(CCTexture2D *pTexture);
};

#endif
