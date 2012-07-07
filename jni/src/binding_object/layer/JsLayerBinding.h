#ifndef _JS_LAYER_BINDING_H
#define _JS_LAYER_BINDING_H

#include "cocos2d.h"
#include "jsapi.h"
#include "Macros.h"
using namespace cocos2d;

class JsLayerBinding {

public:
	static JS_METHOD( SetIsTouchEnabled);
	static JS_METHOD( SetIsMultiTouches);
	static JS_METHOD( SetIsAccelerometerEnabled);

	static JS_METHOD( OnTouchesMoved);
	static JS_METHOD( OnTouchesEnded);
	static JS_METHOD( OnTouchesBegan);
	static JS_METHOD( OnTouchesCancelled);
	static JS_METHOD( OnTouchMoved);
	static JS_METHOD( OnTouchEnded);
	static JS_METHOD( OnTouchBegan);
	static JS_METHOD( OnTouchCancelled);

	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
