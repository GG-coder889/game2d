#ifndef _JS_SPRITEFRAME_BINDING_H
#define _JS_SPRITEFRAME_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;

class JsSpriteFrameBinding {
public:
	static JS_METHOD( SetOffsetInPixels);
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
