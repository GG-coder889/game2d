#ifndef _JS_RECT_BINDING_H
#define _JS_RECT_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;
class JsRectBinding {
public:
	enum {
		Origin = 1, Size
	};
public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
	static void Finalize(JSContext *context, JSObject *obj);
	static JSBool PropertyGet(JSContext *context, JSObject *obj, jsid id,
			jsval *val);
	static JSBool PropertySet(JSContext *context, JSObject *obj, jsid id,
			JSBool strict, jsval *val);
	static JSBool
	RectContainsPoint(JSContext *context, uint32_t argc, jsval *vp);
	static JSBool RectIntersectsRect(JSContext *context, uint32_t argc,
			jsval *vp);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
