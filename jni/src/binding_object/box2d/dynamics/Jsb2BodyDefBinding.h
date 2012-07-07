#ifndef _JS_B2BODYDEF_BINDING_H
#define _JS_B2BODYDEF_BINDING_H
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class Jsb2BodyDefBinding {
public:
	static JS_METHOD( SetUserData);
	static JS_METHOD( SetPosition);
	static JS_GET_PROPERTY( Type);
	static JS_SET_PROPERTY( Type);
public:
	static void Finalize(JSContext *context, JSObject *obj);
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
