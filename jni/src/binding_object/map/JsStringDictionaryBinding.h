#ifndef _JS_STRINGDICTIONARY_BINDING_H
#define _JS_STRINGDICTIONARY_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;

class JsStringDictionaryBinding {

public:
	static JS_METHOD( GetIntValue);
	static JS_METHOD( GetStringValue);
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
