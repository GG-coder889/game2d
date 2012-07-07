#define TAG "JsScene"
#include "JsScene.h"
#include "Log.h"
#include "JsScheduleManager.h"
JsScene::JsScene() {
	NEW_STATE_MACHINE( JsScene);
	pLayer = JsLayer::node();
}

STATE_MACHINE_IMPLEMENT( JsScene)

JsScene::~JsScene() {
	DELETE_STATE_MACHINE( JsScene);
}

bool JsScene::init() {
	if (!CCScene::init()) {
		return false;
	}
	//remove pre scene unused schedule
	JsScheduleManager::SharedScheduleManager()->UnscheduleAllSelector();
	addChild(pLayer, 100);
	return true;
}

