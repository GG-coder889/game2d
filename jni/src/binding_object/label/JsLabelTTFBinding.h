#ifndef _JS_LABEL_TTF_BINDING_H
#define _JS_LABEL_TTF_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsLabelTTFBinding {
public:
	static JS_METHOD( SetColor);
	static JS_METHOD( SetString);
	static JS_METHOD( GetString);

	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
