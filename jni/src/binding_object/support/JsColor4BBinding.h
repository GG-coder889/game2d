#ifndef _JS_COLOR4B_BINDING_H
#define _JS_COLOR4B_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;

class JsColor4BBinding {
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
	static void Finalize(JSContext *context, JSObject *obj);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
