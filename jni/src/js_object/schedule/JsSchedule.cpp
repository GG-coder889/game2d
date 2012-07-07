#define TAG "JsSchedule"
#include "JsSchedule.h"
#include "Log.h"

JsSchedule::JsSchedule() :
	jsScheduleCallback(JSVAL_NULL), callbackValue(NULL), id(0) {
}

JsSchedule::~JsSchedule() {
	JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
	JS_RemoveValueRoot(context, &jsScheduleCallback);
	JS_RemoveObjectRoot(context, &callbackValue);
}
void JsSchedule::update(ccTime dt) {
	JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
	if (jsScheduleCallback != JSVAL_NULL) {
		jsval rVal;
		if (callbackValue) {
			if (context) {
				JS_CallFunctionValue(context, callbackValue,
						jsScheduleCallback, 0, NULL, &rVal);
			}
		} else {
			JS_CallFunctionValue(context,
					JavaScriptEngine::ShareInstance().ShareObject(),
					jsScheduleCallback, 0, NULL, &rVal);
		}

	}
}
void JsSchedule::SetScheduleCallback(jsval jsCallback) {
	this->jsScheduleCallback = jsCallback;
	JS_AddValueRoot(JavaScriptEngine::ShareInstance().ShareContext(),
			&this->jsScheduleCallback);
}

void JsSchedule::SetCallbackData(JSObject *callbackValue) {
	this->callbackValue = callbackValue;
	JS_AddObjectRoot(JavaScriptEngine::ShareInstance().ShareContext(),
			&this->callbackValue);
}

