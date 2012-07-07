#define TAG "JsLayerColorBinding"
#include "JsLayerColorBinding.h"
#include "Log.h"

JSClass JsLayerColorBinding::clz = { "LayerColor", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsLayerColorBinding::obj = NULL;

JSBool JsLayerColorBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval colorVal;
		JS_GetProperty(context, jsonObj, "color", &colorVal);
		if (!JSVAL_IS_VOID(colorVal)) {
			JSObject *colorObj;
			JS_ValueToObject(context, colorVal, &colorObj);
			ccColor4B *pColor = static_cast<ccColor4B*> (JS_GetPrivate(context,
					colorObj));
			CCLayerColor *pLayer = CCLayerColor::layerWithColor(*pColor);
			if (pLayer) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pLayer);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
				return JS_TRUE;
			}
		}
	}
	return JS_TRUE;
}

JSObject * JsLayerColorBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

