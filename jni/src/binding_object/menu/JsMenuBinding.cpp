#define TAG "JsMenuBinding"
#include "JsMenuBinding.h"
JSClass JsMenuBinding::clz = { "Menu", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsMenuBinding::obj = NULL;

JS_CLASS_METHOD(JsMenuBinding,AlignItemsHorizontallyWithPadding) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCMenu * pMenu =static_cast<CCMenu*> (JS_GetPrivate(context,thisObj));
		if(pMenu) {
			jsval *args = JS_ARGV(context, vp);
			double align = 0;
			JS_ValueToNumber(context,args[0],&align);
			pMenu->alignItemsHorizontallyWithPadding(align);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsMenuBinding,Create) {
	CCMenu* pMenu = NULL;
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		JSIdArray * menuArray = JS_Enumerate(context, jsonObj);
		jsuint arrayLen = menuArray->length;
		jsval itemVal;
		JSObject *itemObj;
		jsid id;
		for (int i = 0; i < arrayLen; i++) {
			id = menuArray->vector[i];
			JS_GetPropertyById(context, jsonObj, id, &itemVal);
			JS_ValueToObject(context, itemVal, &itemObj);
			CCMenuItem * menuItem = static_cast<CCMenuItem*> (JS_GetPrivate(context,
							itemObj));
			if (pMenu) {
				pMenu->addChild(menuItem, i);
			} else {
				pMenu = CCMenu::menuWithItem(menuItem);
			}
		}
		JS_DestroyIdArray(context, menuArray);
	} else {
		pMenu = CCMenu::menuWithItem(NULL);
	}
	if (pMenu) {
		JSObject *newObj = JS_NewObject(context, &clz, obj,
				NULL);
		JS_SetPrivate(context, newObj, pMenu);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JSObject * JsMenuBinding::BindingOnEngine(JSContext *context, JSObject *global,
		JSObject *parent) {
	JSFunctionSpec methods[] = { { "alignItemsHorizontallyWithPadding",
			AlignItemsHorizontallyWithPadding, 0, JSPROP_PERMANENT
					| JSPROP_SHARED }, JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
