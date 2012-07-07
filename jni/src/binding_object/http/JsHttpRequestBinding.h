#ifndef _JS_HTTP_REQUEST_BINDING_H
#define _JS_HTTP_REQUEST_BINDING_H

#include "v8.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace v8;
using namespace cocos2d;
class JsHttpRequestBinding {
public:
	static JS_METHOD( Get);
	static JS_METHOD( Post);
public:
	static void BindingOnV8(Persistent<Context> context);
private:
	static void ExposeMethod(Handle<Object> obj);
};

#endif
