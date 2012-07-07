#ifndef _JS_BOX2D_DEBUG_LAYER_BINDING_H
#define _JS_BOX2D_DEBUG_LAYER_BINDING_H

#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;

class JsBox2dDebugLayerBinding {
public:
	static JS_GET_PROPERTY( OnDraw);
	static JS_SET_PROPERTY( OnDraw);

	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);

public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
