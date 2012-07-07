#ifndef _JS_B2WORLD_BINDING_H
#define _JS_B2WORLD_BINDING_H
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "jsapi.h"
class Jsb2WorldBinding {
public:
	static JS_METHOD( CreateBody);
	static JS_METHOD( SetAllowSleeping);
	static JS_METHOD( SetContinuousPhysics);
	static JS_METHOD( GetBodyList);
	static JS_METHOD( GetBodyCount);
	static JS_METHOD( Step);
	static JS_METHOD( SetDebugDraw);
	static JS_METHOD( DrawDebugData);
public:
	static void Finalize(JSContext *context, JSObject *obj);
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
