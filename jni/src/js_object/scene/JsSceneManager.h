#ifndef _JS_SCENE_MANAGER_H
#define _JS_SCENE_MANAGER_H
#include "cocos2d.h"
#include "TransitionSceneEnum.h"
using namespace cocos2d;
class JsSceneManager {
public:
	static void ChangeTo(TransitionSceneEnum transition, ccTime t,
			CCScene *pScene);
	static void ChangeTo(CCScene *pScene);
	static CCScene * CreateTransitionScene(TransitionSceneEnum transition,
			ccTime t, CCScene *pScene);
};

#endif
