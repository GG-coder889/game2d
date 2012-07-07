#ifndef _JS_LOG_BINDING_H
#define _JS_LOG_BINDING_H
#include "jsapi.h"
class JsLogBinding {
public:
	static JSBool Write(JSContext *context, unsigned int argc, jsval *vp);
	static void BindingOnEngine(JSContext *context, JSObject *global);
public:
	static JSClass clz;
};

#endif
