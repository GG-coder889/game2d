#define TAG "JsCallback"
#include "JsCallback.h"
#include "JavaScriptEngine.h"
JsCallback* JsCallback::actionWithJsScriptFunc(jsval jsScriptFunc) {
	JsCallback *pRet = new JsCallback();
	if (pRet && pRet->initWithJsScriptFunc(jsScriptFunc)) {
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

void JsCallback::execute() {
	if (jsCallbackFunction != JSVAL_NULL) {
		jsval rVal;
		JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
		int argc = 1;
		jsval args[argc];
		args[0] = callbackValue;
		JS_CallFunctionValue(context,
				JavaScriptEngine::ShareInstance().ShareObject(),
				jsCallbackFunction, argc, args, &rVal);
	}
}

bool JsCallback::initWithJsScriptFunc(jsval jsScriptFunc) {
	this->jsCallbackFunction = jsScriptFunc;
	JS_AddValueRoot(JavaScriptEngine::ShareInstance().ShareContext(),
			&this->jsCallbackFunction);
	return true;
}

void JsCallback::SetCallbackData(jsval obj) {
	this->callbackValue = obj;
	JS_AddValueRoot(JavaScriptEngine::ShareInstance().ShareContext(),
			&this->callbackValue);
}

