#define TAG "JsRotateToBinding"
#include "JsRotateToBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsRotateToBinding::clz = { "RotateTo", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsRotateToBinding::obj = NULL;

JSBool JsRotateToBinding::Create(JSContext *context, unsigned int argc,
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
			CCActionInterval *pRotateTo = CCRotateTo::actionWithDuration(
					duration, angel);
			if (pRotateTo) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pRotateTo);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsRotateToBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

