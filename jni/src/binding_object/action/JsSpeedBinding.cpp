#define TAG "JsSpeedBinding"
#include "JsSpeedBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsSpeedBinding::clz = { "Speed", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsSpeedBinding::obj = NULL;

JSBool JsSpeedBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval actionVal;
		jsval rateVal;
		JS_GetProperty(context, jsonObj, "action", &actionVal);
		JS_GetProperty(context, jsonObj, "rate", &rateVal);
		if (!JSVAL_IS_VOID(actionVal) && !JSVAL_IS_VOID(rateVal)) {
			double rate = JSVAL_TO_DOUBLE(rateVal);
			CCActionInterval *pAction =
					static_cast<CCActionInterval*> (JS_GetPrivate(context,
							JSVAL_TO_OBJECT(actionVal)));
			CCAction *pSpeed = CCSpeed::actionWithAction(pAction, rate);
			if (pSpeed) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pSpeed);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsSpeedBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

