#ifndef _JS_SPRITEFRAMECACHE_BINDING_H
#define _JS_SPRITEFRAMECACHE_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsSpriteFrameCacheBinding {
public:
	static JSBool AddSpriteFramesWithFile(JSContext *context,
			unsigned int argc, jsval *vp);
	static JSBool SpriteFrameByName(JSContext *context, unsigned int argc,
			jsval *vp);
	static void BindingOnEngine(JSContext *context, JSObject *global);
private:
	static JSClass clz;
};
#endif
