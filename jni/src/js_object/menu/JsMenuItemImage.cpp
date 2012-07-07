#define TAG "JsMenuItemImage"
#include "JsMenuItemImage.h"
#include "JsMenuItemImageBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"
JsMenuItemImage * JsMenuItemImage::ItemFromNormalImage(jsval jsCallback,
		const char * normalImage, const char * selectedIamge) {
	JsMenuItemImage * pRet = new JsMenuItemImage();
	if (pRet && pRet->initFromNormalImage(normalImage, selectedIamge, NULL,
			pRet, menu_selector(JsMenuItemImage::MenuItemCallback))) {
		pRet->SetJsMenuItemCallback(jsCallback);
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

JsMenuItemImage * JsMenuItemImage::ItemFromNormalImage(
		const char * normalImage, const char * selectedIamge) {
	JsMenuItemImage * pRet = new JsMenuItemImage();
	if (pRet && pRet->initFromNormalImage(normalImage, selectedIamge, NULL,
			NULL, NULL)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
void JsMenuItemImage::MenuItemCallback(CCObject * pSender) {
	JsMenuItemImage * self = (JsMenuItemImage *) pSender;
	if (self) {
		jsval rVal;
		int argc = 1;
		jsval argv[argc];
		JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
		JSObject *newObj = JS_NewObject(context, &JsMenuItemImageBinding::clz,
				JsMenuItemImageBinding::obj, NULL);
		JS_SetPrivate(context, newObj, self);
		argv[0] = OBJECT_TO_JSVAL(newObj);
		JS_CallFunctionValue(context,
				JavaScriptEngine::ShareInstance().ShareObject(),
				jsMenuItemCallback, argc, argv, &rVal);
	}
}
jsval JsMenuItemImage::GetJsMenuItemCallback() {
	return jsMenuItemCallback;

}
void JsMenuItemImage::SetJsMenuItemCallback(jsval jsCallback) {
	jsMenuItemCallback = jsCallback;
}
