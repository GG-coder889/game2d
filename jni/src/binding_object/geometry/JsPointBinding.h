#ifndef _JS_POINT_BINDING_H
#define _JS_POINT_BINDING_H

#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;
class JsPointBinding {
	enum {
		X = 1, Y
	};
public:
	static JS_METHOD( ToAngle);
	static JS_METHOD( Sub);
	static JS_METHOD( Add);
	static JS_METHOD( Mult);
	static JS_METHOD( Normalize);
	static JS_METHOD( Distance);
public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
	static void Finalize(JSContext *context, JSObject *obj);
	static JSBool PropertyGet(JSContext *context, JSObject *obj, jsid id,
			jsval *val);
	static JSBool PropertySet(JSContext *context, JSObject *obj, jsid id,
			JSBool strict, jsval *val);

public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
