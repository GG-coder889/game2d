#ifndef _JS_B2FIXTUREDEF_BINDING_H
#define _JS_B2FIXTUREDEF_BINDING_H
#include "Macros.h"
#include "Box2D/Box2D.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class Jsb2FixtureDefBinding {
public:
	static JS_METHOD( SetShape);
	static JS_METHOD( SetUserData);
	static JS_METHOD( SetDensity);
	static JS_METHOD( SetFriction);
	static JS_METHOD( SetRestitution);
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
