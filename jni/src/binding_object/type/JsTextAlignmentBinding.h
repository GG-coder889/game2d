#ifndef _JS_ALIGNMENT_BINDING_H
#define _JS_ALIGNMENT_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;

class JsTextAlignmentBinding {
public:
	static JS_GET_PROPERTY( Left);
	static JS_GET_PROPERTY( Center);
	static JS_GET_PROPERTY( Right);
public:
	static void BindingOnEngine(JSContext *ctx, JSObject *global);
public:
	static JSClass clz;
};
#endif
