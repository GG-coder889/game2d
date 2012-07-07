#define TAG "JsSequenceBinding"
#include "JsSequenceBinding.h"
#include "cocos2d.h"
#include "Log.h"
using namespace cocos2d;

JSClass JsSequenceBinding::clz = { "Sequence", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsSequenceBinding::obj = NULL;

JSBool JsSequenceBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval actionsVal;
		JS_GetProperty(context, jsonObj, "actions", &actionsVal);
		CCArray *pAnimations = NULL;
		if (!JSVAL_IS_VOID(actionsVal)) {
			JSObject *arrayObj;
			JS_ValueToObject(context, actionsVal, &arrayObj);
			uint32_t arrayLen = 0;
			JS_GetArrayLength(context, arrayObj, &arrayLen);
			pAnimations = CCArray::arrayWithCapacity(arrayLen);
			jsval elementVal;
			JSObject *element;
			CCFiniteTimeAction *pAction;
			for (uint32_t i = 0; i < arrayLen; i++) {
				JS_GetElement(context, arrayObj, i, &elementVal);
				JS_ValueToObject(context, elementVal, &element);
				pAction = static_cast<CCFiniteTimeAction*> (JS_GetPrivate(
						context, element));
				if (pAction) {
					pAnimations->addObject(pAction);
				}
			}
		} else {
			JSIdArray * animationArray = JS_Enumerate(context, jsonObj);
			jsuint arrayLen = animationArray->length;
			pAnimations = CCArray::arrayWithCapacity(arrayLen);
			jsval proVal;
			JSObject *proObj;
			jsid id;
			for (int i = 0; i < arrayLen; i++) {
				id = animationArray->vector[i];
				JS_GetPropertyById(context, jsonObj, id, &proVal);
				JS_ValueToObject(context, proVal, &proObj);
				CCFiniteTimeAction *pAction =
						static_cast<CCFiniteTimeAction*> (JS_GetPrivate(
								context, proObj));
				pAnimations->addObject(pAction);
			}
			JS_DestroyIdArray(context, animationArray);
		}
		if (pAnimations) {
			CCFiniteTimeAction *pSequence = CCSequence::actionsWithArray(
					pAnimations);
			if (pSequence) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pSequence);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsSequenceBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}
