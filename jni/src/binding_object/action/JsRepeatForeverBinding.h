#ifndef _JS_REPEATFOREVER_BINDING_H
#define _JS_REPEATFOREVER_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsRepeatForeverBinding {

public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *vp);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};

#endif
