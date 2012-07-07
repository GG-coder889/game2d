#ifndef _JS_LAYER_H
#define _JS_LAYER_H
#include "cocos2d.h"
#include "jsapi.h"
using namespace cocos2d;

class JsLayer: public CCLayer {

public:
	JsLayer();
	virtual ~JsLayer();
	virtual bool init();
	virtual void registerWithTouchDispatcher();
	void SetIsMultiTouches(bool isMultiTouches);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
	virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
	virtual void ccTouchesMoved(CCSet* touches, CCEvent* event);
	virtual void ccTouchesCancelled(CCSet *touches, CCEvent *event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchCancelled(CCTouch *touch, CCEvent *event);
	LAYER_NODE_FUNC( JsLayer);
	void SetJsTouchesEndedCallback(jsval jsCallback);
	void SetJsTouchesMovedCallback(jsval jsCallback);
	void SetJsTouchesBeganCallback(jsval jsCallback);
	void SetJsTouchesCancelledCallback(jsval jsCallback);

	void SetJsTouchEndedCallback(jsval jsCallback);
	void SetJsTouchMovedCallback(jsval jsCallback);
	void SetJsTouchBeganCallback(jsval jsCallback);
	void SetJsTouchCancelledCallback(jsval jsCallback);

	void SetCallbackObj(JSObject *obj);
protected:
	void CallbackTouchesEvent(CCSet *touches, jsval callback);
	void CallbackTouchEvent(CCTouch *touch, jsval callback);
protected:
	jsval jsTouchesEndedCallback;
	jsval jsTouchesMovedCallback;
	jsval jsTouchesBeganCallback;
	jsval jsTouchesCancelledCallback;

	jsval jsTouchEndedCallback;
	jsval jsTouchMovedCallback;
	jsval jsTouchBeganCallback;
	jsval jsTouchCancelledCallback;
	bool isMultiTouches;
	JSObject *callbackObj;
};

#endif
