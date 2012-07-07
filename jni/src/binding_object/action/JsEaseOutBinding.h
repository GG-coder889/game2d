#ifndef _JS_EASEOUT_BINDING_H
#define _JS_EASEOUT_BINDING_H
#include "jsapi.h"
class JsEaseOutBinding {
public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *vp);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
