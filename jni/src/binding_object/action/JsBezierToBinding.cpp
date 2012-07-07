#define TAG "JsBezierToBinding"
#include "JsBezierToBinding.h"
#include "cocos2d.h"
#include "Log.h"
using namespace cocos2d;

JSClass JsBezierToBinding::clz = { "BezierTo", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsBezierToBinding::obj = NULL;

JSBool JsBezierToBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval durationVal;
		jsval endPonitVal;
		jsval controlPoint1Val;
		jsval controlPoint2Val;
		JS_GetProperty(context, jsonObj, "duration", &durationVal);
		JS_GetProperty(context, jsonObj, "endPoint", &endPonitVal);
		JS_GetProperty(context, jsonObj, "controlPoint1", &controlPoint1Val);
		JS_GetProperty(context, jsonObj, "controlPoint2", &controlPoint2Val);
		if (!JSVAL_IS_VOID(durationVal) && !JSVAL_IS_VOID(controlPoint2Val)
				&& !JSVAL_IS_VOID(controlPoint1Val) && !JSVAL_IS_VOID(
				endPonitVal)) {
			double duration = 0;
			JS_ValueToNumber(context, durationVal, &duration);
			CCPoint *pEndPont = static_cast<CCPoint*> (JS_GetPrivate(context,
					JSVAL_TO_OBJECT(endPonitVal)));
			CCPoint *pControlPoint1 = static_cast<CCPoint*> (JS_GetPrivate(
					context, JSVAL_TO_OBJECT(controlPoint1Val)));
			CCPoint *pControlPoint2 = static_cast<CCPoint*> (JS_GetPrivate(
					context, JSVAL_TO_OBJECT(controlPoint2Val)));
			ccBezierConfig c;
			c.endPosition = *pEndPont;
			c.controlPoint_1 = *pControlPoint1;
			c.controlPoint_2 = *pControlPoint2;
			CCActionInterval *pBezierTo = CCBezierTo::actionWithDuration(
					duration, c);
			if (pBezierTo) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pBezierTo);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsBezierToBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

