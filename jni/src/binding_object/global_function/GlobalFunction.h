#ifndef _GLOBAL_FUNCTION_H
#define	 _GLOBAL_FUNCTION_H
#include "Log.h"
#include "Macros.h"
#include "jsapi.h"

class GlobalFunction {

public:
	static void BindingOnEngine(JSContext *context, JSObject *global);
private:
	static JSBool GetScaleX(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool GetScaleY(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Include(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Random01(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Random(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool RadiansToDegrees(JSContext *context, unsigned int argc,
			jsval *vp);
	static JSBool CCC4(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool CCC3(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Schedule(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Unschedule(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Abs(JSContext *context, unsigned int argc, jsval *vp);
	static JSBool Log(JSContext *context, unsigned int argc, jsval *vp);
};

#endif
