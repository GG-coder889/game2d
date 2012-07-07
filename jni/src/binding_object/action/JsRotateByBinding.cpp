#define TAG "JsRotateByBinding"
#include "JsRotateByBinding.h"
#include "cocos2d.h"
#include "Log.h"
using namespace cocos2d;

JSClass JsRotateByBinding::clz = { "RotateBy", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsRotateByBinding::obj = NULL;

JSBool JsRotateByBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval durationVal;
		jsval angelVal;
		JS_GetProperty(context, jsonObj, "duration", &durationVal);
		JS_GetProperty(context, jsonObj, "angle", &angelVal);
		if (!JSVAL_IS_VOID(durationVal) && !JSVAL_IS_VOID(angelVal)) {
			double angel = 0;
			double duration = 0;
			JS_ValueToNumber(context, durationVal, &duration);
			JS_ValueToNumber(context, angelVal, &angel);
			CCActionInterval *pRotateBy = CCRotateBy::actionWithDuration(
					duration, angel);
			if (pRotateBy) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pRotateBy);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsRotateByBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

