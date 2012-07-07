#define TAG "JsBox2dDebugLayer"
#include "JsBox2dDebugLayer.h"
#include "Log.h"
#include "JavaScriptEngine.h"
JsBox2dDebugLayer::JsBox2dDebugLayer() {
	jsDrawCallback = JSVAL_NULL;
}

bool JsBox2dDebugLayer::init() {
	if (!JsLayer::init()) {
		return false;
	}
	return true;

}

void JsBox2dDebugLayer::draw() {
	glDisable( GL_TEXTURE_2D);
	glDisableClientState( GL_COLOR_ARRAY);
	glDisableClientState( GL_TEXTURE_COORD_ARRAY);
	if (jsDrawCallback != JSVAL_NULL) {
		jsval rVal;
		JS_CallFunctionValue(JavaScriptEngine::ShareInstance().ShareContext(),
				JavaScriptEngine::ShareInstance().ShareObject(),
				jsDrawCallback, 0, NULL, &rVal);
	}
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void JsBox2dDebugLayer::SetJsDrawCallback(jsval jsCallback) {
	jsDrawCallback = jsCallback;
}

jsval JsBox2dDebugLayer::GetJsDrawCallback() {
	return jsDrawCallback;
}
