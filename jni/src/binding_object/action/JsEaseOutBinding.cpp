#define TAG "JsEaseOutBinding"
#include "JsEaseOutBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsEaseOutBinding::clz = { "EaseOut", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsEaseOutBinding::obj = NULL;

JSBool JsEaseOutBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval actionVal;
		jsval rateVal;
		JS_GetProperty(context, jsonObj, "action", &actionVal);
		JS_GetProperty(context, jsonObj, "rate", &rateVal);
		if (!JSVAL_IS_VOID(actionVal) && !JSVAL_IS_VOID(rateVal)) {
			double rate = 0;
			JS_ValueToNumber(context, rateVal, &rate);
			JSObject *actionObj;
			JS_ValueToObject(context, actionVal, &actionObj);
			CCActionInterval *pAction =
					static_cast<CCActionInterval*> (JS_GetPrivate(context,
							actionObj));
			CCActionInterval *pEaseOut = CCEaseOut::actionWithAction(pAction,
					rate);
			if (pEaseOut) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pEaseOut);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}

		}
	}
	return JS_TRUE;
}

JSObject * JsEaseOutBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

