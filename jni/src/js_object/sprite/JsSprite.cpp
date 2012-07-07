#define TAG "JsSprite"
#include "JsSprite.h"
#include "Log.h"
JsSprite::JsSprite() {
	NEW_STATE_MACHINE( JsSprite);
}

STATE_MACHINE_IMPLEMENT( JsSprite)

JsSprite::~JsSprite() {
	DELETE_STATE_MACHINE( JsSprite);
}

bool JsSprite::init() {
	if (!CCSprite::init()) {
		return false;
	}
	return true;
}

JsSprite * JsSprite::SpriteWithFile(const char *pszFileName) {
	JsSprite *pobSprite = new JsSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName)) {
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

JsSprite* JsSprite::SpriteWithFile(const char *pszFileName, const CCRect& rect) {
	JsSprite *pobSprite = new JsSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName, rect)) {
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

JsSprite * JsSprite::SpriteWithSpriteFrame(CCSpriteFrame *pSpriteFrame) {
	JsSprite *pobSprite = new JsSprite();
	if (pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame)) {
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

JsSprite * JsSprite::SpriteWithTexture(CCTexture2D *pTexture,
		const CCRect &rect) {
	JsSprite *pobSprite = new JsSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect)) {
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

JsSprite * JsSprite::SpriteWithTexture(CCTexture2D *pTexture) {
	JsSprite *pobSprite = new JsSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture)) {
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
