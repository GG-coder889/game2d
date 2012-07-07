#define TAG "JsTexture2DBinding"
#include "JsTexture2DBinding.h"
#include "Log.h"
#include "JavaScriptEngine.h"

JSClass JsTexture2DBinding::clz = { "Texture2D", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsTexture2DBinding::obj = NULL;

JSBool JsTexture2DBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval fileNameVal;
		JS_GetProperty(context, jsonObj, "fileName", &fileNameVal);
		if (!JSVAL_IS_VOID(fileNameVal)) {
			JSString *fileNameStr = JS_ValueToString(context, fileNameVal);
			char *fileName = JS_EncodeString(context, fileNameStr);
			CCTexture2D *pTexture =
					CCTextureCache::sharedTextureCache()->addImage(fileName);
			JS_free(context, fileName);
			if (pTexture == NULL) {
				JS_ReportOutOfMemory(context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pTexture);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * JsTexture2DBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

