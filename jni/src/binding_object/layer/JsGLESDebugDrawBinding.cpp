#define TAG "JsGLESDebugDrawBinding"
#include "JsGLESDebugDrawBinding.h"
#include "JsGLESDebugDraw.h"

JSClass JsGLESDebugDrawBinding::clz = { "DebugDraw", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsGLESDebugDrawBinding::obj = NULL;

JS_CLASS_METHOD(JsGLESDebugDrawBinding,SetFlags) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsGLESDebugDraw * pDraw =static_cast<JsGLESDebugDraw*> (JS_GetPrivate(context,thisObj));
		uint flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_pairBit;
		flags += b2Draw::e_centerOfMassBit;
		pDraw->SetFlags(flags);
	}
	return JS_TRUE;
}

void JsGLESDebugDrawBinding::Finalize(JSContext *context, JSObject *obj) {
	JsGLESDebugDraw *pDebugDraw = static_cast<JsGLESDebugDraw*> (JS_GetPrivate(
			context, obj));
	if (pDebugDraw) {
		delete pDebugDraw;
	}
}
JS_CLASS_METHOD(JsGLESDebugDrawBinding,Create) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval ratioVal;
		JS_GetProperty(context, jsonObj,
				"ratio", &ratioVal);
		if(!JSVAL_IS_VOID(ratioVal)) {
			int ratio = JSVAL_TO_INT(ratioVal);
			JsGLESDebugDraw *pDebugDraw = new JsGLESDebugDraw(ratio);
			if (pDebugDraw) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pDebugDraw);
				JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsGLESDebugDrawBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "setFlags", SetFlags, 1, JSPROP_PERMANENT
			| JSPROP_SHARED }, JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
