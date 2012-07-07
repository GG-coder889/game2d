#define TAG "JsMenuItemFontBinding"
#include "JsMenuItemFontBinding.h"
#include "Log.h"
#include "JsMenuItemFont.h"
#include "JavaScriptEngine.h"
JSClass JsMenuItemFontBinding::clz = { "MenuItemFont", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsMenuItemFontBinding::obj = NULL;

JS_CLASS_METHOD(JsMenuItemFontBinding,Create) {
	if(argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj = NULL;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval titleVal;
		JS_GetProperty(context, jsonObj,
				"title", &titleVal);
		if(!JSVAL_IS_VOID(titleVal)) {
			JSString *titleStr = JS_ValueToString(context,titleVal);
			char *title = JS_EncodeString(context, titleStr);
			jsval handlerVal;
			JS_GetProperty(context, jsonObj,
					"handler", &handlerVal);
			JsMenuItemFont *pMenuItem;
			if(!JSVAL_IS_NULL(handlerVal)) {
				pMenuItem = JsMenuItemFont::ItemFromString(
						handlerVal, title);
			} else {
				pMenuItem = JsMenuItemFont::ItemFromString(title);
			}
			JS_free(context, title);
			if (pMenuItem)
			{
				JSObject *newObj = JS_NewObject(context, &clz,
						obj, NULL);
				JS_SetPrivate(context,newObj, pMenuItem);
				JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
			}
		}

	}
	return JS_TRUE;
}

JSObject * JsMenuItemFontBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

