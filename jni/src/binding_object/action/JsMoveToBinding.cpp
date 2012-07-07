#define TAG "JsMoveToBinding"
#include "JsMoveToBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsMoveToBinding::clz = { "MoveTo", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsMoveToBinding::obj = NULL;

JSBool JsMoveToBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval durationVal;
		jsval pointVal;
		JS_GetProperty(context, jsonObj, "duration", &durationVal);
		JS_GetProperty(context, jsonObj, "point", &pointVal);
		if (!JSVAL_IS_VOID(durationVal) && !JSVAL_IS_VOID(pointVal)) {
			double duration = 0;
			JS_ValueToNumber(context, durationVal, &duration);
			JSObject *pointObj;
			JS_ValueToObject(context, pointVal, &pointObj);
			CCPoint *p =
					static_cast<CCPoint*> (JS_GetPrivate(context, pointObj));
			CCActionInterval *pMoveTo = CCMoveTo::actionWithDuration(duration,
					*p);
			if (pMoveTo) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pMoveTo);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}

		}
	}
	return JS_TRUE;
}

JSObject * JsMoveToBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

