#ifndef _JS_USERDEFAULT_BINDING_H
#define _JS_USERDEFAULT_BINDING_H

#include "cocos2d.h"
#include "v8.h"
#include "Macros.h"
using namespace v8;
using namespace cocos2d;
class JsUserDefaultBinding {
public:
	static JS_METHOD( GetBoolForKey);
	static JS_METHOD( GetIntegerForKey);
	static JS_METHOD( GetFloatForKey);
	static JS_METHOD( GetDoubleForKey);
	static JS_METHOD( GetStringForKey);
	static JS_METHOD( SetBoolForKey);
	static JS_METHOD( SetIntegerForKey);
	static JS_METHOD( SetFloatForKey);
	static JS_METHOD( SetDoubleForKey);
	static JS_METHOD( SetStringForKey);
public:
	static void BindingOnV8(Persistent<Context> context);
private:
	static void ExposeMethod(Handle<Object> obj);
};

#endif
