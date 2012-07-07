#ifndef _JS_LABELBMFONT_BINDING_H
#define _JS_LABELBMFONT_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsLabelBMFontBinding {
public:
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
