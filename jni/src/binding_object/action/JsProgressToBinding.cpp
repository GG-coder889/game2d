#define TAG "JsProgressToBinding"
#include "JsProgressToBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsProgressToBinding::clz = { "ProgressTo", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsProgressToBinding::obj = NULL;

JSBool JsProgressToBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval durationVal;
		jsval percentVal;
		JS_GetProperty(context, jsonObj, "duration", &durationVal);
		JS_GetProperty(context, jsonObj, "percent", &percentVal);
		if (!JSVAL_IS_VOID(durationVal) && !JSVAL_IS_VOID(percentVal)) {
			double duration = 0;
			JS_ValueToNumber(context, durationVal, &duration);
			double percent = 0;
			JS_ValueToNumber(context, percentVal, &percent);
			CCActionInterval *pProgressTo = CCProgressTo::actionWithDuration(
					duration, percent);
			if (pProgressTo) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pProgressTo);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}

		}
	}
	return JS_TRUE;
}

JSObject * JsProgressToBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

