#define TAG "JsLogBinding"
#include "JsLogBinding.h"
#include "Log.h"
JSClass JsLogBinding::clz = { "console", 0, JS_PropertyStub, JS_PropertyStub,
		JS_PropertyStub, JS_StrictPropertyStub, JS_EnumerateStub,
		JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };
JSBool JsLogBinding::Write(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *messageStr = JS_ValueToString(context, args[0]);
		char *message = JS_EncodeString(context, messageStr);
		LogInfo("console", message);
		JS_free(context, message);
	}
	return JS_TRUE;
}

void JsLogBinding::BindingOnEngine(JSContext *context, JSObject *global) {

	JSFunctionSpec methods[] = { { "fatal", Write, 1, 0 }, { "error", Write, 1,
			0 }, { "info", Write, 1, 0 }, { "warn", Write, 1, 0 }, { "debug",
			Write, 1, 0 }, { "verbose", Write, 1, 0 },
			{ "trace", Write, 1, 0 }, { 0 } };
	JSObject *logObj = JS_DefineObject(context, global, "console", &clz, NULL,
			JSPROP_ENUMERATE);
	JS_DefineFunctions(context, logObj, methods);
}
