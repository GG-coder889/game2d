#define TAG "JsFadeInBinding"
#include "JsFadeInBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsFadeInBinding::clz = { "FadeIn", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsFadeInBinding::obj = NULL;

JSBool JsFadeInBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval durationVal;
		JS_GetProperty(context, jsonObj, "duration", &durationVal);
		if (!JSVAL_IS_VOID(durationVal)) {
			double duration = JSVAL_TO_DOUBLE(durationVal);
			CCActionInterval *pFadeIn =
					CCFadeIn::actionWithDuration(duration);
			if (pFadeIn) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pFadeIn);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsFadeInBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

