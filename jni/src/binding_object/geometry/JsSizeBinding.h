#ifndef _JS_SIZE_BINDING_H
#define _JS_SIZE_BINDING_H

#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;
class JsSizeBinding {
	enum {
		Width = 1, Height
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
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
