#include "JsTextAlignmentBinding.h"

JSClass JsTextAlignmentBinding::clz = { "TextAlignment", 0, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_GET_PROPERTY(JsTextAlignmentBinding,Left) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(CCTextAlignmentLeft));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsTextAlignmentBinding,Right) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(CCTextAlignmentRight));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsTextAlignmentBinding,Center) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(CCTextAlignmentCenter));
	return JS_TRUE;
}
void JsTextAlignmentBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSObject *textAlignmentObj = JS_DefineObject(context, global,
			"TextAlignment", &clz, 0, JSPROP_ENUMERATE);
	JSPropertySpec properties[] = { { "left", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetLeft, JS_StrictPropertyStub },
			{ "center", 0, JSPROP_PERMANENT | JSPROP_SHARED, GetCenter,
					JS_StrictPropertyStub }, { "right", 0, JSPROP_PERMANENT
					| JSPROP_SHARED, GetRight, JS_StrictPropertyStub }, { 0 } };
	JS_DefineProperties(context, textAlignmentObj, properties);
}
