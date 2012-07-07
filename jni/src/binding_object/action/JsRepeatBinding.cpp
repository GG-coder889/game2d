#define TAG "JsRepeatBinding"
#include "JsRepeatBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsRepeatBinding::clz = { "Repeat", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsRepeatBinding::obj = NULL;

JSBool JsRepeatBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		jsval animateVal;
		jsval timeVal;
		JS_ValueToObject(context, args[0], &jsonObj);
		JS_GetProperty(context, jsonObj, "action", &animateVal);
		JS_GetProperty(context, jsonObj, "time", &timeVal);
		if (!JSVAL_IS_VOID(animateVal) && !JSVAL_IS_VOID(timeVal)) {
			JSObject *animateObj;
			JS_ValueToObject(context, animateVal, &animateObj);
			CCActionInterval *pAction =
					static_cast<CCActionInterval*> (JS_GetPrivate(context,
							animateObj));
			double time = 0;
			JS_ValueToNumber(context, timeVal, &time);
			if (pAction) {
				CCFiniteTimeAction *pRepeat = CCRepeat::actionWithAction(
						pAction, time);
				if (pRepeat) {
					JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
					JS_SetPrivate(context, newObj, pRepeat);
					JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
				}
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsRepeatBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

