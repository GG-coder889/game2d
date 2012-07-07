#ifndef _JS_ANIMATION_BINDING_H
#define _JS_ANIMATION_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;
class JsAnimationBinding {
public:
	static JS_METHOD( GetSpriteFrame);
public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
	static void Finalize(JSContext *context, JSObject *obj);
public:
	static JSClass clz;
	static JSObject *obj;
};

#endif
