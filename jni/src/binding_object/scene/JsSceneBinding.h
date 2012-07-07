#ifndef _JS_SCENE_BINDING_H
#define _JS_SCENE_BINDING_H
#include "Macros.h"
#include "jsapi.h"
class JsSceneBinding {
public:
	static JS_METHOD( Loop);
	static JS_METHOD( Status);
	static JS_METHOD( ControlPanel);
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject* obj;
};
#endif
