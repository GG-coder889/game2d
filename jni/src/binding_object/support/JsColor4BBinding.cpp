#define TAG "JsColor4BBinding"
#include "JsColor4BBinding.h"
#include "Log.h"

JSClass JsColor4BBinding::clz = { "Color4B", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsColor4BBinding::obj = NULL;

void JsColor4BBinding::Finalize(JSContext *context, JSObject *obj) {
	ccColor4B *pColor = static_cast<ccColor4B*> (JS_GetPrivate(context, obj));
	if (pColor) {
		delete pColor;
	}
}
JSBool JsColor4BBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval rVal;
		jsval gVal;
		jsval bVal;
		jsval aVal;
		JS_GetProperty(context, jsonObj, "r", &rVal);
		JS_GetProperty(context, jsonObj, "g", &gVal);
		JS_GetProperty(context, jsonObj, "b", &bVal);
		JS_GetProperty(context, jsonObj, "o", &aVal);
		if (!JSVAL_IS_VOID(rVal) && !JSVAL_IS_VOID(gVal)
				&& !JSVAL_IS_VOID(bVal) && !JSVAL_IS_VOID(aVal)) {
			int r = JSVAL_TO_INT(rVal);
			int g = JSVAL_TO_INT(gVal);
			int b = JSVAL_TO_INT(bVal);
			int a = JSVAL_TO_INT(aVal);
			ccColor4B *pColor = new ccColor4B();
			pColor->r = r;
			pColor->g = g;
			pColor->b = b;
			pColor->a = a;

			if (pColor) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pColor);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
				return JS_TRUE;
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsColor4BBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

