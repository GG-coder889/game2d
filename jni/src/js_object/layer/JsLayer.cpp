#define TAG "JsLayer"
#include "JsLayer.h"
#include "Log.h"
#include "Macros.h"
#include "JavaScriptEngine.h"
#include "JsTouchBinding.h"
JsLayer::JsLayer() {
	jsTouchesEndedCallback = JSVAL_NULL;
	jsTouchesMovedCallback = JSVAL_NULL;
	jsTouchesBeganCallback = JSVAL_NULL;
	jsTouchesCancelledCallback = JSVAL_NULL;
	jsTouchEndedCallback = JSVAL_NULL;
	jsTouchMovedCallback = JSVAL_NULL;
	jsTouchBeganCallback = JSVAL_NULL;
	jsTouchCancelledCallback = JSVAL_NULL;
	callbackObj = NULL;
	isMultiTouches = false;
}

JsLayer::~JsLayer() {
	JS_RemoveObjectRoot(JavaScriptEngine::ShareInstance().ShareContext(),
			&callbackObj);
}

bool JsLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	return true;

}

void JsLayer::SetJsTouchesEndedCallback(jsval jsCallback) {
	jsTouchesEndedCallback = jsCallback;
}

void JsLayer::SetJsTouchesMovedCallback(jsval jsCallback) {
	jsTouchesMovedCallback = jsCallback;
}

void JsLayer::SetJsTouchesBeganCallback(jsval jsCallback) {
	jsTouchesBeganCallback = jsCallback;
}

void JsLayer::SetJsTouchEndedCallback(jsval jsCallback) {
	jsTouchEndedCallback = jsCallback;
}

void JsLayer::SetJsTouchMovedCallback(jsval jsCallback) {
	jsTouchMovedCallback = jsCallback;
}

void JsLayer::SetJsTouchesCancelledCallback(jsval jsCallback) {
	jsTouchesCancelledCallback = jsCallback;
}

void JsLayer::SetJsTouchCancelledCallback(jsval jsCallback) {
	jsTouchCancelledCallback = jsCallback;
}

void JsLayer::SetJsTouchBeganCallback(jsval jsCallback) {
	jsTouchBeganCallback = jsCallback;
}

void JsLayer::registerWithTouchDispatcher() {
	if (this->isMultiTouches) {
		CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this, 0);
	} else {
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0,
				true);
	}
}

void JsLayer::SetIsMultiTouches(bool isMultiTouches) {
	this->isMultiTouches = isMultiTouches;
}

void JsLayer::ccTouchesBegan(CCSet* touches, CCEvent* event) {
	if (jsTouchesBeganCallback != JSVAL_NULL) {
		CallbackTouchesEvent(touches, jsTouchesBeganCallback);
	}
}

void JsLayer::ccTouchesMoved(CCSet* touches, CCEvent* event) {
	if (jsTouchesMovedCallback != JSVAL_NULL) {
		CallbackTouchesEvent(touches, jsTouchMovedCallback);
	}
}

void JsLayer::ccTouchesEnded(CCSet* touches, CCEvent* event) {
	if (jsTouchesEndedCallback != JSVAL_NULL) {
		CallbackTouchesEvent(touches, jsTouchesEndedCallback);
	}
}

void JsLayer::ccTouchesCancelled(CCSet *touch, CCEvent *event) {
	if (jsTouchesCancelledCallback != JSVAL_NULL) {
		CallbackTouchesEvent(touch, jsTouchesCancelledCallback);
	}

}

void JsLayer::ccTouchEnded(CCTouch* touch, CCEvent* event) {
	if (jsTouchEndedCallback != JSVAL_NULL) {
		CallbackTouchEvent(touch, jsTouchEndedCallback);
	}
}
bool JsLayer::ccTouchBegan(CCTouch* touch, CCEvent* event) {
	if (jsTouchBeganCallback != JSVAL_NULL) {
		CallbackTouchEvent(touch, jsTouchBeganCallback);
	}
	return true;
}
void JsLayer::ccTouchMoved(CCTouch* touch, CCEvent* event) {
	if (jsTouchMovedCallback != JSVAL_NULL) {
		CallbackTouchEvent(touch, jsTouchMovedCallback);
	}
}

void JsLayer::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
	if (jsTouchCancelledCallback != JSVAL_NULL) {
		CallbackTouchEvent(touch, jsTouchCancelledCallback);
	}

}
void JsLayer::SetCallbackObj(JSObject *obj) {
	callbackObj = obj;
	JS_AddObjectRoot(JavaScriptEngine::ShareInstance().ShareContext(),
			&callbackObj);
}

void JsLayer::CallbackTouchEvent(CCTouch* touch, jsval callback) {
	int argc = 1;
	jsval args[argc];
	jsval rVal;
	JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
	JSObject *newObj = JS_NewObject(context, &JsTouchBinding::clz,
			JsTouchBinding::obj, NULL);
	JS_SetPrivate(context, newObj, touch);
	args[0] = OBJECT_TO_JSVAL(newObj);
	JSObject
			*callObj =
					callbackObj == NULL ? JavaScriptEngine::ShareInstance().ShareObject()
							: callbackObj;
	JS_CallFunctionValue(context, callObj, callback, argc, args, &rVal);
}

void JsLayer::CallbackTouchesEvent(CCSet* touches, jsval callback) {
	JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
	JSObject *arrayObj = JS_NewArrayObject(context, 0, NULL);
	CCSetIterator it;
	CCTouch *touch;
	int i = 0;
	JSObject *newObj;
	jsval newObjVal;
	for (it = touches->begin(); it != touches->end(); it++) {
		touch = (CCTouch*) (*it);
		if (!touch) {
			break;
		}
		newObj = JS_NewObject(context, &JsTouchBinding::clz,
				JsTouchBinding::obj, NULL);
		JS_SetPrivate(context, newObj, touch);
		newObjVal = OBJECT_TO_JSVAL(newObj);
		JS_SetElement(context, arrayObj, i, &newObjVal);
		i++;
	}
	int argc = 1;
	jsval args[argc];
	args[0] = OBJECT_TO_JSVAL(arrayObj);
	jsval rVal;
	JSObject
			*callObj =
					callbackObj == NULL ? JavaScriptEngine::ShareInstance().ShareObject()
							: callbackObj;
	JS_CallFunctionValue(context, callObj, callback, argc, args, &rVal);
}
