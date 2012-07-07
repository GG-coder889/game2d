#define TAG "JsAnimationCacheBinding"
#include "JsAnimationCacheBinding.h"
#include "JsAnimationBinding.h"
JSClass JsAnimationCacheBinding::clz = { "AnimationCache", 0, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_METHOD(JsAnimationCacheBinding,AddAnimation) {
	if(argc == 2) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *animationObj = NULL;
		JS_ValueToObject(context,args[0],&animationObj);
		CCAnimation *pAnimation = static_cast<CCAnimation*>(JS_GetPrivate(context,animationObj));
		JSString *keyStr = JS_ValueToString(context,args[1]);
		char *pKey = JS_EncodeString(context,keyStr);
		if(pAnimation && pKey) {
			CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, pKey);
			JS_free(context,pKey);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsAnimationCacheBinding,AnimationByName) {
	if(argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *keyStr = JS_ValueToString(context,args[0]);
		char *pKey = JS_EncodeString(context,keyStr);
		if(pKey) {
			CCAnimation *pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(pKey);
			JSObject *newObj = JS_NewObject(context, &JsAnimationBinding::clz, JsAnimationBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pAnimation);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			JS_free(context,pKey);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsAnimationCacheBinding,RemoveAnimationByName) {
	if(argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *keyStr = JS_ValueToString(context,args[0]);
		char *pKey = JS_EncodeString(context,keyStr);
		if(pKey) {
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName(pKey);
			JS_free(context,pKey);
		}
	}
	return JS_TRUE;
}

void JsAnimationCacheBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSFunctionSpec methods[] = { JS_FN("addAnimation", AddAnimation, 2, 0),
			JS_FN("animationByName", AnimationByName, 1, 0), JS_FN(
					"removeAnimationByName", RemoveAnimationByName, 1, 0),
			JS_FS_END };
	JSObject *frameObj = JS_DefineObject(context, global, "AnimationCache",
			&clz, 0, JSPROP_ENUMERATE);
	JS_DefineFunctions(context, frameObj, methods);
}
