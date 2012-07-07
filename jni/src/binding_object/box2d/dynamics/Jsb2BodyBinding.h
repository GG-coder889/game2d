#ifndef _JS_B2BODY_BINDING_H
#define _JS_B2BODY_BINDING_H
#include "Box2D/Box2D.h"
#include "Macros.h"
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class Jsb2BodyBinding {
public:
	static JS_METHOD( CreateFixture);
	static JS_METHOD( GetNext);
	static JS_METHOD( GetUserData);
	static JS_METHOD( GetPosition);
	static JS_METHOD( GetAngle);

	static JS_GET_PROPERTY( DynamicBody);
	static JS_GET_PROPERTY( StaticBody);
	static JS_GET_PROPERTY( KinematicBody);
public:
	static JSBool Create(JSContext *context, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
