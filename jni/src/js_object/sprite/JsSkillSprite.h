#ifndef _JS_SKILL_SPRITE_H
#define _JS_SKILL_SPRITE_H
#include "cocos2d.h"
using namespace cocos2d;

class JsSkillSprite: public CCSprite {
private:
	CCMenuItemImage* itemSkill;
	CCMenu* menuSkill;
	CCSprite* spriteBlock;
	CCProgressTimer* progressTimeSkill;
	CCProgressTo* actionProgressTo;
public:
	JsSkillSprite(char* blockfile, char* skillNormalFile,
			char* skillSelectedFile);
	void SkillClickCallBack(CCObject* object);
	void SkillCoolDownCallBack(CCNode* node);
};
#endif
