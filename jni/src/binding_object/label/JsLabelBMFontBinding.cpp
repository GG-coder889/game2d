#define TAG "JsLabelBMFontBinding"
#include "JsLabelBMFontBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"

JSClass JsLabelBMFontBinding::clz = { "LabelBMFont", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsLabelBMFontBinding::obj = NULL;

JS_CLASS_METHOD(JsLabelBMFontBinding,Create) {
	if (argc == 1)
	{
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval labelVal;
		JS_GetProperty(context, jsonObj,
				"label", &labelVal);
		jsval fntFileVal;
		JS_GetProperty(context, jsonObj,
				"fntFile", &fntFileVal);
		if(!JSVAL_IS_VOID(labelVal) && !JSVAL_IS_VOID(fntFileVal) ) {
			JSString *labelStr = JS_ValueToString(context, labelVal);
			char * label = JS_EncodeString(context, labelStr);
			JSString *fntFileStr = JS_ValueToString(context, fntFileVal);
			char * fntFile = JS_EncodeString(context, fntFileStr);
			CCLabelBMFont *pLabel = CCLabelBMFont::labelWithString(label, fntFile);
			if (pLabel) {
				JSObject *newObj = JS_NewObject(context, &clz,
						obj, NULL);
				JS_SetPrivate(context,newObj, pLabel);
				JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
			}
			JS_free(context,label);
			JS_free(context,fntFile);
		}
	}
	return JS_TRUE;
}

JSObject * JsLabelBMFontBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}
