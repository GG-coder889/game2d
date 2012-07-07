#ifndef _JS_GELS_DEBUG_DRAW_BINDING_H
#define _JS_GELS_DEBUG_DRAW_BINDING_H
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;

class JsGLESDebugDrawBinding {
public:
	static JS_METHOD( SetFlags);
public:

	static void Finalize(JSContext *context, JSObject *obj);
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
