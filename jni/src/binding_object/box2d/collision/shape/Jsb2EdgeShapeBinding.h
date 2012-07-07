#ifndef _JS_B2EDGESHAPE_BINDING_H
#define _JS_B2EDGESHAPE_BINDING_H
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "jsapi.h"
class Jsb2EdgeShapeBinding {
public:
	static JS_METHOD( Set);
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
