#ifndef _JS_CALLBACK_H
#define _JS_CALLBACK_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
#include "Log.h"
#include "JavaScriptEngine.h"
using namespace cocos2d;
class JsCallback: public CCCallFunc {
public:
	JsCallback() :
		jsCallbackFunction(JSVAL_NULL), callbackValue(JSVAL_NULL) {
	}
	virtual ~JsCallback() {
		JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
		JS_RemoveValueRoot(context, &jsCallbackFunction);
		JS_RemoveValueRoot(context, &callbackValue);
	}
	virtual void execute();
	bool initWithJsScriptFunc(jsval jsScriptFunc);
	void SetCallbackData(jsval callbackValue);
	static JsCallback *actionWithJsScriptFunc(jsval jsScriptFunc);
private:
	jsval jsCallbackFunction;
	jsval callbackValue;
};
#endif
