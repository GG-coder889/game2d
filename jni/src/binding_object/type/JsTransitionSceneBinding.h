#ifndef _JS_TRANSITION_SCENE_BINDING_H
#define _JS_TRANSITION_SCENE_BINDING_H
#include "Macros.h"
#include "jsapi.h"
#include "TransitionSceneEnum.h"
class JsTransitionSceneBinding {
public:
	static JS_GET_PROPERTY( RotoZoomCallback);
	static JS_GET_PROPERTY( SceneOrientedCallback);
	static JS_GET_PROPERTY( ShrinkGrowCallback);
	static JS_GET_PROPERTY( JumpZoomCallback);
	static JS_GET_PROPERTY( MoveInLCallback);
	static JS_GET_PROPERTY( MoveInRCallback);
	static JS_GET_PROPERTY( MoveInTCallback);
	static JS_GET_PROPERTY( MoveInBCallback);
	static JS_GET_PROPERTY( SlideInLCallback);
	static JS_GET_PROPERTY( SlideInRCallback);
	static JS_GET_PROPERTY( SlideInBCallback);
	static JS_GET_PROPERTY( SlideInTCallback);
	static JS_GET_PROPERTY( FlipXCallback);
	static JS_GET_PROPERTY( FlipYCallback);
	static JS_GET_PROPERTY( FlipAngularCallback);
	static JS_GET_PROPERTY( ZoomFlipXCallback);
	static JS_GET_PROPERTY( ZoomFlipYCallback);
	static JS_GET_PROPERTY( ZoomFlipAngularCallback);
	static JS_GET_PROPERTY( FadeCallback);
	static JS_GET_PROPERTY( CrossFadeCallback);
	static JS_GET_PROPERTY( SplitColsCallback);
	static JS_GET_PROPERTY( SplitRowsCallback);
	static JS_GET_PROPERTY( FadeTRCallback);
	static JS_GET_PROPERTY( FadeBLCallback);
	static JS_GET_PROPERTY( FadeUpCallback);
	static JS_GET_PROPERTY( FadeDownCallback);

	static void BindingOnEngine(JSContext *context, JSObject *global);
public:
	static JSClass clz;
};
#endif
