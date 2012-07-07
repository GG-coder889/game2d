#ifndef _JS_SPRITEBATCHNODE_BINDING_H
#define _JS_SPRITEBATCHNODE_BINDING_H
#include "cocos2d.h"
#include "Macros.h"
#include "jsapi.h"
using namespace cocos2d;
class JsSpriteBatchNodeBinding {
public:
	static JS_METHOD( GetTexture);
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;

};
#endif
