#include "JsSkillSprite.h"
JsSkillSprite::JsSkillSprite(char* blockfile, char* skillNormalFile,
		char* skillSelectedFile) {
	spriteBlock = CCSprite::spriteWithFile(blockfile);
	spriteBlock->setPosition(CCPointZero);
	this->addChild(spriteBlock, 100, 20);
	spriteBlock->setIsVisible(false);
	itemSkill = CCMenuItemImage::itemFromNormalImage(skillNormalFile,
			skillSelectedFile, this,
			menu_selector(JsSkillSprite::SkillClickCallBack));
	menuSkill = CCMenu::menuWithItems(itemSkill, NULL);
	menuSkill->setPosition(CCPointZero);
	this->addChild(itemSkill, 90, 10);
	progressTimeSkill = CCProgressTimer::progressWithFile(skillNormalFile);
	progressTimeSkill->setPosition(CCPointZero);
	this->addChild(progressTimeSkill, 110, 30);
	progressTimeSkill->setIsVisible(false);
}

void JsSkillSprite::SkillClickCallBack(CCObject* object) {
	itemSkill->setIsEnabled(false);
	spriteBlock->setIsVisible(true);
	progressTimeSkill->setType(kCCProgressTimerTypeRadialCW);
	progressTimeSkill->setIsVisible(true);
	CCCallFuncN* actionCallBack = CCCallFuncN::actionWithTarget(this,
			callfuncN_selector(JsSkillSprite::SkillCoolDownCallBack));
	actionProgressTo = CCProgressTo::actionWithDuration(5.0f, 100);
	progressTimeSkill->runAction(
			CCSequence::actions(actionProgressTo, actionCallBack, NULL));
}

void JsSkillSprite::SkillCoolDownCallBack(CCNode* node) {
	spriteBlock->setIsVisible(false);
	progressTimeSkill->setIsVisible(false);
	itemSkill->setIsEnabled(true);
}
