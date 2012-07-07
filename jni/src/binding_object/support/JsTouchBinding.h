#ifndef _JS_TOUCH_BINDING_H
#define _JS_TOUCH_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;

class JsTouchBinding {
public:
	static JS_METHOD( Location);
	static JS_METHOD( PreviousLocation);
public:
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
