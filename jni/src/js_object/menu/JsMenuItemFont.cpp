#define TAG "JsMenuItemFont"
#include "JsMenuItemFont.h"
#include "JsMenuItemFontBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"
JsMenuItemFont * JsMenuItemFont::ItemFromString(jsval jsCallback,
		const char * title) {
	JsMenuItemFont * pRet = new JsMenuItemFont();
	if (pRet && pRet->initFromString(title, pRet,
			menu_selector(JsMenuItemFont::MenuItemCallback))) {
		pRet->SetJsMenuItemCallback(jsCallback);
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

JsMenuItemFont * JsMenuItemFont::ItemFromString(const char * title) {
	JsMenuItemFont * pRet = new JsMenuItemFont();
	if (pRet && pRet->initFromString(title, NULL, NULL)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void JsMenuItemFont::MenuItemCallback(CCObject * pSender) {
	JsMenuItemFont * self = (JsMenuItemFont *) pSender;
	if (self) {
		jsval rVal;
		int argc = 1;
		jsval argv[argc];
		JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
		JSObject *newObj = JS_NewObject(context, &JsMenuItemFontBinding::clz,
				JsMenuItemFontBinding::obj, NULL);
		JS_SetPrivate(context, newObj, self);
		argv[0] = OBJECT_TO_JSVAL(newObj);
		JS_CallFunctionValue(context, JavaScriptEngine::ShareInstance().ShareObject(),
				jsMenuItemCallback, argc, argv, &rVal);
	}
}

jsval JsMenuItemFont::GetJsMenuItemCallback() {
	return jsMenuItemCallback;

}
void JsMenuItemFont::SetJsMenuItemCallback(jsval jsCallback) {
	jsMenuItemCallback = jsCallback;
}
