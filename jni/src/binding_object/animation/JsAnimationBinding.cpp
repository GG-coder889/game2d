#define TAG "JsAnimationBinding"
#include "JsAnimationBinding.h"
#include "JsSpriteFrameBinding.h"

JSClass JsAnimationBinding::clz = { "Animation", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsAnimationBinding::obj = NULL;

JSBool JsAnimationBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval framesVal;
		jsval delayVal;
		JS_GetProperty(context, jsonObj, "frames", &framesVal);
		JS_GetProperty(context, jsonObj, "delay", &delayVal);
		if (!JSVAL_IS_VOID(framesVal) && !JSVAL_IS_VOID(delayVal)) {
			JSObject *arrayObj;
			JS_ValueToObject(context, framesVal, &arrayObj);
			uint32_t arrayLen = 0;
			JS_GetArrayLength(context, arrayObj, &arrayLen);
			CCMutableArray<CCSpriteFrame*>* pAnimFrames = new CCMutableArray<
					CCSpriteFrame*> (arrayLen);
			jsval elementVal;
			JSObject *element;
			CCSpriteFrame *pFrame;
			for (uint32_t i = 0; i < arrayLen; i++) {
				JS_GetElement(context, arrayObj, i, &elementVal);
				JS_ValueToObject(context, elementVal, &element);
				pFrame = static_cast<CCSpriteFrame*> (JS_GetPrivate(context,
						element));
				if (pFrame) {
					pAnimFrames ->addObject(pFrame);
				}
			}
			double delay;
			JS_ValueToNumber(context, delayVal, &delay);
			CCAnimation *pAnimation = CCAnimation::animationWithFrames(
					pAnimFrames, delay);
			pAnimFrames->release();
			if (pAnimation) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pAnimation);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsAnimationBinding,GetSpriteFrame) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCAnimation *pAnimation = static_cast<CCAnimation*>(JS_GetPrivate(context,thisObj));
		int index = 0;
		JS_ValueToInt32(context,args[0],&index);
		CCSpriteFrame *pFrame = pAnimation->getFrames()->getObjectAtIndex(
				index);
		JSObject *newObj = JS_NewObject(context, &JsSpriteFrameBinding::clz, JsSpriteFrameBinding::obj, NULL);
		JS_SetPrivate(context,newObj, pFrame);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JSObject * JsAnimationBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("getSpriteFrame", GetSpriteFrame, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

