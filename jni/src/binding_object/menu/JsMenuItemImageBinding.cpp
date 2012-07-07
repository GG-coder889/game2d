#define TAG "JsMenuItemImageBinding"
#include "JsMenuItemImageBinding.h"
#include "Log.h"
#include "JsMenuItemImage.h"
JSClass JsMenuItemImageBinding::clz = { "MenuItemImage", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsMenuItemImageBinding::obj = NULL;

JS_CLASS_METHOD(JsMenuItemImageBinding,Create) {
	if(argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval normalImageVal;
		JS_GetProperty(context, jsonObj,
				"normalImage", &normalImageVal);
		jsval selectedImageVal;
		JS_GetProperty(context, jsonObj,
				"selectedImage", &selectedImageVal);
		if(!JSVAL_IS_VOID(normalImageVal) && !JSVAL_IS_VOID(selectedImageVal)) {
			JSString *normalIamgeStr = JS_ValueToString(context,normalImageVal);
			char * normalImage = JS_EncodeString(context, normalIamgeStr);
			JSString *selectedIamgeStr = JS_ValueToString(context,selectedImageVal);
			char * selectedImage = JS_EncodeString(context, selectedIamgeStr);
			JsMenuItemImage *pMenuItem;
			jsval handlerVal;
			JS_GetProperty(context, jsonObj,
					"handler", &handlerVal);
			if(!JSVAL_IS_VOID(handlerVal)) {
				pMenuItem = JsMenuItemImage::ItemFromNormalImage(
						handlerVal, normalImage, selectedImage);
			}
			else {
				pMenuItem = JsMenuItemImage::ItemFromNormalImage(
						normalImage, selectedImage);
			}
			JS_free(context, normalImage);
			JS_free(context, selectedImage);
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

JSObject * JsMenuItemImageBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, NULL,
			NULL, NULL);
	return obj;
}

