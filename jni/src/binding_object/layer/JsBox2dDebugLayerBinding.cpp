#define TAG "JsBox2dDebugLayerBinding"
#include "JsBox2dDebugLayerBinding.h"
#include "Log.h"
#include "JsBox2dDebugLayer.h"

JSClass JsBox2dDebugLayerBinding::clz = { "DebugLayer", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsBox2dDebugLayerBinding::obj = NULL;

JS_CLASS_GET_PROPERTY(JsBox2dDebugLayerBinding,OnDraw) {
	JsBox2dDebugLayer *pLayer = static_cast<JsBox2dDebugLayer*> (JS_GetPrivate(context, obj));
	jsval touchesMoved = pLayer->GetJsDrawCallback();
	JS_SET_RVAL(context, vp,touchesMoved);
	return JS_TRUE;
}
JS_CLASS_SET_PROPERTY(JsBox2dDebugLayerBinding,OnDraw) {
	if(JSVAL_IS_OBJECT(*vp)) {
		JsBox2dDebugLayer *pLayer = static_cast<JsBox2dDebugLayer*> (JS_GetPrivate(context, obj));
		pLayer->SetJsDrawCallback(*vp);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsBox2dDebugLayerBinding,Create) {
	if (argc == 0) {
		JsBox2dDebugLayer* pLayer = JsBox2dDebugLayer::node();
		if (pLayer == NULL) {
			JS_ReportOutOfMemory(context);
			return JS_FALSE;
		}
		if (JS_IsConstructing(context, vp)) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pLayer);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JSObject *thisObj = JS_THIS_OBJECT(context, vp);
			JS_SetPrivate(context, thisObj, pLayer);
		}
		return JS_TRUE;
	}
	return JS_FALSE;
}

JSObject * JsBox2dDebugLayerBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSPropertySpec properties[] = { { "onDraw", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetOnDraw, SetOnDraw }, { 0 } };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, properties,
			NULL, NULL, NULL);
	return obj;
}
