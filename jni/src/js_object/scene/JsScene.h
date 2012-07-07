#ifndef _JS_SCENE_H
#define _JS_SCENE_H
#include "cocos2d.h"
#include "StateMachine.h"
#include "StateMachineDefine.h"
#include "JsLayer.h"
using namespace cocos2d;

class JsScene: public CCScene {
	STATE_MACHINE_DEFINE( JsScene);
public:
	JsScene();
	virtual ~JsScene();
	virtual bool init();
	SCENE_NODE_FUNC( JsScene);
	JsLayer *ControlPanel() {
		return pLayer;
	}

private:
	JsLayer *pLayer;
};

#endif
