#ifndef _JS_TEXTRUE2D_BINDING
#define _JS_TEXTRUE2D_BINDING
#include "cocos2d.h"
#include "jsapi.h"
#include "Macros.h"
using namespace cocos2d;

class JsTexture2DBinding {
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
