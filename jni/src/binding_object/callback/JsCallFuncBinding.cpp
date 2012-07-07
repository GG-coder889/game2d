#define TAG "JsCallFuncBinding"
#include "JsCallFuncBinding.h"
#include "JsCallback.h"
JSClass JsCallFuncBinding::clz = { "CallFunc", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsCallFuncBinding::obj = NULL;

JSBool JsCallFuncBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		JSObject *jsonObj;
		jsval *args = JS_ARGV(context, vp);
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval handlerVal;
		JS_GetProperty(context, jsonObj, "handler", &handlerVal);
		if (!JSVAL_IS_VOID(handlerVal)) {
			JsCallback *pCallFunc = JsCallback::actionWithJsScriptFunc(
					handlerVal);
			if (pCallFunc) {
				jsval dataVal;
				JS_GetProperty(context, jsonObj, "data", &dataVal);
				if (!JSVAL_IS_NULL(dataVal)) {
					pCallFunc->SetCallbackData(dataVal);
				}
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pCallFunc);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsCallFuncBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

