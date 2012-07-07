#define TAG "JsDelayTimeBinding"
#include "JsDelayTimeBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsDelayTimeBinding::clz = { "DelayTime", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsDelayTimeBinding::obj = NULL;

JSBool JsDelayTimeBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval durationVal;
		JS_GetProperty(context, jsonObj, "duration", &durationVal);
		if (!JSVAL_IS_VOID(durationVal)) {
			double duration = 0;
			JS_ValueToNumber(context, durationVal, &duration);
			CCActionInterval *pDelayTime = CCDelayTime::actionWithDuration(
					duration);
			if (pDelayTime) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pDelayTime);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsDelayTimeBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

