#ifndef _JS_CALLFUNC_BINDING_H
#define _JS_CALLFUNC_BINDING_H
#include "JsCallback.h"
#include "jsapi.h"
#include "cocos2d.h"
#include "Log.h"
#include "Macros.h"
using namespace cocos2d;
class JsCallFuncBinding {

public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};

#endif
