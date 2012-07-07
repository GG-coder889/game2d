#ifndef _JS_BOX2D_DEBUG_LAYER_H
#define _JS_BOX2D_DEBUG_LAYER_H
#include "cocos2d.h"
#include "jsapi.h"
#include "JsLayer.h"
using namespace cocos2d;

class JsBox2dDebugLayer: public JsLayer {

public:
	JsBox2dDebugLayer();
	virtual bool init();
	LAYER_NODE_FUNC( JsBox2dDebugLayer);
	virtual void draw();
	void SetJsDrawCallback(jsval jsCallback);
	jsval GetJsDrawCallback();
private:
	jsval jsDrawCallback;
};

#endif
