#ifndef _JS_ANIMATION_CACHE_BINDING_H
#define _JS_ANIMATION_CACHE_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;
class JsAnimationCacheBinding {
public:
	static JS_METHOD( AddAnimation);
	static JS_METHOD( AnimationByName);
	static JS_METHOD( RemoveAnimationByName);

	static void BindingOnEngine(JSContext *context, JSObject *global);
private:
	static JSClass clz;
};

#endif
