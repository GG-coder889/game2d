#define TAG "JsRepeatForeverBinding"
#include "JsRepeatForeverBinding.h"

JSClass JsRepeatForeverBinding::clz = { "RepeatForever", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsRepeatForeverBinding::obj = NULL;

JSBool JsRepeatForeverBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		jsval animateVal;
		JS_ValueToObject(context, args[0], &jsonObj);
		JS_GetProperty(context, jsonObj, "action", &animateVal);
		if (!JSVAL_IS_VOID(animateVal)) {
			JSObject *animateObj;
			JS_ValueToObject(context, animateVal, &animateObj);
			CCActionInterval *pAnimate =
					static_cast<CCActionInterval*> (JS_GetPrivate(context,
							animateObj));
			if (pAnimate) {
				CCFiniteTimeAction *pReapForver =
						CCRepeatForever::actionWithAction(pAnimate);
				if (pReapForver) {
					JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
					JS_SetPrivate(context, newObj, pReapForver);
					JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
				}
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsRepeatForeverBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}
