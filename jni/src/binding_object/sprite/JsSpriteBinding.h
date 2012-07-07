#ifndef _JS_SPRITE_BINDING_H
#define _JS_SPRITE_BINDING_H
#include "jsapi.h"
#include "Macros.h"
class JsSpriteBinding {
public:
	static JS_METHOD( SpriteWithFile);
	static JS_METHOD( SpriteWithSpriteFrame);
	static JS_METHOD( SpriteWithTexture);
public:
	static JS_METHOD( SetTextureRect);
	static JS_METHOD( SetOpacity);
	static JS_METHOD( Loop);
	static JS_METHOD( Status);
	static JS_METHOD( InitWithFile);
	static JS_METHOD( InitWithSpriteFrame);
	static JS_METHOD( InitWithTexture);
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;

};
#endif
