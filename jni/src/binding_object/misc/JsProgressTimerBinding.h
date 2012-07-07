#ifndef _JS_PROGRESSTIMER_BINDING_H
#define _JS_PROGRESSTIMER_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
#include "Log.h"
using namespace cocos2d;
class JsProgressTimerBinding {
public:
	static JS_METHOD( SetPercentage);
	static JS_METHOD( SetType);
public:
	static JS_GET_PROPERTY( RadialCCW);
	static JS_GET_PROPERTY( RadialCW);
	static JS_GET_PROPERTY( HorizontalBarLR);
	static JS_GET_PROPERTY( HorizontalBarRL);
	static JS_GET_PROPERTY( HorizontalBarBT);
	static JS_GET_PROPERTY( HorizontalBarTB);
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};

#endif
