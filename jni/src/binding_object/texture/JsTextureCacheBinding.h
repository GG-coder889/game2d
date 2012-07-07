#ifndef _JS_TEXTURECACHE_BINDING_H
#define _JS_TEXTURECACHE_BINDING_H
#include "cocos2d.h"
#include "jsapi.h"
using namespace cocos2d;
class JsTextureCacheBinding {
public:
	static JSBool AddImage(JSContext *context, unsigned int argc, jsval *vp);
	static void BindingOnEngine(JSContext *context, JSObject *global);
private:
	static JSClass clz;
};

#endif
