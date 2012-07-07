#ifndef _JS_DIRECTOR_BINDING_H
#define _JS_DIRECTOR_BINDING_H
#include "cocos2d.h"
#include "jsapi.h"
using namespace cocos2d;
class JsDirectorBinding {
public:
	static JSBool SetDisplayFPS(JSContext *context, unsigned int argc,
			jsval *vp);
	static JSBool End(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Pause(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Resume(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool GetWinSize(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool LoadResources(JSContext *context, unsigned int argc,
			jsval *vp);
	static JSBool GetResource(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Start(JSContext *context, unsigned int argc, jsval *vp);

	static void BindingOnEngine(JSContext *context, JSObject *global);
private:
	static JSClass clz;
};

#endif
