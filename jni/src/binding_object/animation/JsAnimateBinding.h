#ifndef _JS_ANIMATE_BINDING_H
#define _JS_ANIMATE_BINDING_H

#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsAnimateBinding {

public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
	static void Release();
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
