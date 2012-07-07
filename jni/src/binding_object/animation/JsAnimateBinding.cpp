#define TAG "JsAnimateBinding"
#include "JsAnimateBinding.h"

JSClass JsAnimateBinding::clz = { "Animate", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsAnimateBinding::obj = NULL;

JSBool JsAnimateBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval animationVal;
		jsval restoreFrameVal;
		JSBool isContainedAnimation = JS_GetProperty(context, jsonObj,
				"animation", &animationVal);
		JSBool isContainedRestoreFrame = JS_GetProperty(context, jsonObj,
				"restoreFrame", &restoreFrameVal);
		if (isContainedAnimation && isContainedRestoreFrame) {
			JSObject *animationObj;
			JS_ValueToObject(context, animationVal, &animationObj);
			CCAnimation *pAnimation = static_cast<CCAnimation*> (JS_GetPrivate(
					context, animationObj));
			bool bRestoreOriginalFrame = JSVAL_TO_BOOLEAN(restoreFrameVal);
			if (pAnimation) {
				CCAnimate *pAnimate = CCAnimate::actionWithAnimation(
						pAnimation, bRestoreOriginalFrame);
				if (pAnimate) {
					JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
					JS_SetPrivate(context, newObj, pAnimate);
					JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
				}
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsAnimateBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}
