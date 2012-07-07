#ifndef _JS_NODE_BINDING_H
#define _JS_NODE_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;

class JsNodeBinding {
public:
	static JS_METHOD( GetParent);
	static JS_METHOD( StopAllActions);
	static JS_METHOD( StopAction);
	static JS_METHOD( RunAction);
	static JS_METHOD( SetAnchorPoint);
	static JS_METHOD( SetRotation);
	static JS_METHOD( SetPosition);
	static JS_METHOD( GetPosition);
	static JS_METHOD( SetIsVisible);
	static JS_METHOD( SetScaleX);
	static JS_METHOD( GetScaleX);
	static JS_METHOD( SetScaleY);
	static JS_METHOD( GetScaleY);
	static JS_METHOD( GetContentSize);
	static JS_METHOD( SetContentSize);
	static JS_METHOD( AddChild);
	static JS_METHOD( RemoveChildByTag);
	static JS_METHOD( RemoveChild);
	static JS_METHOD( GetChildByTag);
	static JS_METHOD( GetChildren);
	static JS_METHOD( GetZOrder);
	static JS_METHOD( RemoveFromParentAndCleanup);
	static JS_METHOD( SetTag);
	static JS_METHOD( GetTag);
	static JS_METHOD( BoundingBox);
	static JS_METHOD( Schedule);
	static JS_METHOD( Unschedule);
	static JSBool IsClass(JSContext *context, JSObject *obj, jsid id,
			jsval *val);
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
