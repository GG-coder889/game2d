#define TAG "JsSpawnBinding"
#include "JsSpawnBinding.h"
#include "cocos2d.h"
using namespace cocos2d;

JSClass JsSpawnBinding::clz = { "Spawn", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsSpawnBinding::obj = NULL;

JSBool JsSpawnBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		JSIdArray * animationArray = JS_Enumerate(context, jsonObj);
		jsuint arrayLen = animationArray->length;
		CCArray *pAnimations = CCArray::arrayWithCapacity(arrayLen);
		jsval proVal;
		JSObject *proObj;
		jsid id;
		for (int i = 0; i < arrayLen; i++) {
			id = animationArray->vector[i];
			JS_GetPropertyById(context, jsonObj, id, &proVal);
			JS_ValueToObject(context, proVal, &proObj);
			CCFiniteTimeAction *pAction =
					static_cast<CCFiniteTimeAction*> (JS_GetPrivate(context,
							proObj));
			pAnimations->addObject(pAction);
		}
		JS_DestroyIdArray(context, animationArray);
		if (pAnimations) {
			CCFiniteTimeAction *pSpawn = CCSpawn::actionsWithArray(pAnimations);
			if (pSpawn) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pSpawn);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsSpawnBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}
