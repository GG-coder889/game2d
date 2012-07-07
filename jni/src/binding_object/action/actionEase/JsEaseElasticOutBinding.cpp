#define TAG "JsEaseElasticOutBinding"
#include "JsEaseElasticOutBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsEaseElasticOutBinding::clz = { "EaseElasticOut", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsEaseElasticOutBinding::obj = NULL;

JSBool JsEaseElasticOutBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval actionVal;
		jsval periodVal;
		JS_GetProperty(context, jsonObj, "action", &actionVal);
		JS_GetProperty(context, jsonObj, "period", &periodVal);
		if (!JSVAL_IS_VOID(actionVal) && !JSVAL_IS_VOID(periodVal)) {
			double period = JSVAL_TO_DOUBLE(periodVal);
			CCActionInterval *pAction =
					static_cast<CCActionInterval*> (JS_GetPrivate(context,
							JSVAL_TO_OBJECT(actionVal)));
			CCActionInterval *pEaseElasticOut =
					CCEaseElasticOut::actionWithAction(pAction, period);
			if (pEaseElasticOut) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pEaseElasticOut);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsEaseElasticOutBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

