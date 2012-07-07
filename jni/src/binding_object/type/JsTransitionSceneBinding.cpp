#define TAG "JsTransitionSceneBinding"
#include "JsTransitionSceneBinding.h"
#include "cocos2d.h"
#include "Log.h"
#include "TransitionSceneEnum.h"
using namespace cocos2d;

JSClass JsTransitionSceneBinding::clz = { "TransitionScene", 0,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,RotoZoomCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(RotoZoom));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SceneOrientedCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SceneOriented));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,ShrinkGrowCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(ShrinkGrow));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,JumpZoomCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(JumpZoom));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,MoveInLCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(MoveInL));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,MoveInRCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(MoveInR));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,MoveInTCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(MoveInT));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,MoveInBCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(MoveInB));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SlideInLCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SlideInL));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SlideInRCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SlideInR));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SlideInBCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SlideInB));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SlideInTCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SlideInT));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FlipXCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FlipX));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FlipYCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FlipY));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FlipAngularCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FlipAngular));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,ZoomFlipXCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(ZoomFlipX));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,ZoomFlipYCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(ZoomFlipY));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,ZoomFlipAngularCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(ZoomFlipAngular));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FadeCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(Fade));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,CrossFadeCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(CrossFade));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SplitColsCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SplitCols));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,SplitRowsCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(SplitRows));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FadeTRCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FadeTR));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FadeBLCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FadeBL));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FadeUpCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FadeUp));
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(JsTransitionSceneBinding,FadeDownCallback) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(FadeDown));
	return JS_TRUE;
}
void JsTransitionSceneBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSPropertySpec properties[] = { { "rotoZoom", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetRotoZoomCallback, JS_StrictPropertyStub }, {
			"sceneOriented", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetSceneOrientedCallback, JS_StrictPropertyStub }, { "shrinkGrow",
			0, JSPROP_PERMANENT | JSPROP_SHARED, GetShrinkGrowCallback,
			JS_StrictPropertyStub }, { "jumpZoom", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetJumpZoomCallback, JS_StrictPropertyStub }, {
			"moveInL", 0, JSPROP_PERMANENT | JSPROP_SHARED, GetMoveInLCallback,
			JS_StrictPropertyStub }, { "moveInR", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetMoveInRCallback, JS_StrictPropertyStub }, {
			"moveInT", 0, JSPROP_PERMANENT | JSPROP_SHARED, GetMoveInTCallback,
			JS_StrictPropertyStub }, { "moveInB", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetMoveInBCallback, JS_StrictPropertyStub }, {
			"slideInL", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetSlideInLCallback, JS_StrictPropertyStub }, { "slideInR", 0,
			JSPROP_PERMANENT | JSPROP_SHARED, GetSlideInRCallback,
			JS_StrictPropertyStub }, { "slideInB", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetSlideInBCallback, JS_StrictPropertyStub }, {
			"slideInT", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetSlideInTCallback, JS_StrictPropertyStub }, { "flipX", 0,
			JSPROP_PERMANENT | JSPROP_SHARED, GetFlipXCallback,
			JS_StrictPropertyStub }, { "flipY", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetFlipYCallback, JS_StrictPropertyStub }, {
			"flipAngular", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetFlipAngularCallback, JS_StrictPropertyStub }, { "zoomFlipX", 0,
			JSPROP_PERMANENT | JSPROP_SHARED, GetZoomFlipXCallback,
			JS_StrictPropertyStub }, { "zoomFlipY", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetZoomFlipYCallback, JS_StrictPropertyStub }, {
			"zoomFlipAngular", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetZoomFlipAngularCallback, JS_StrictPropertyStub }, { "fade", 0,
			JSPROP_PERMANENT | JSPROP_SHARED, GetFadeCallback,
			JS_StrictPropertyStub }, { "crossFade", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetCrossFadeCallback, JS_StrictPropertyStub }, {
			"splitCols", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetSplitColsCallback, JS_StrictPropertyStub }, { "fadeTR", 0,
			JSPROP_PERMANENT | JSPROP_SHARED, GetFadeTRCallback,
			JS_StrictPropertyStub }, { "fadeBL", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetFadeBLCallback, JS_StrictPropertyStub }, {
			"fadeUp", 0, JSPROP_PERMANENT | JSPROP_SHARED, GetFadeUpCallback,
			JS_StrictPropertyStub }, { "fadeDown", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetFadeDownCallback, JS_StrictPropertyStub },
			{ 0 } };
	JSObject *transitionObj = JS_DefineObject(context, global,
			"TransitionScene", &clz, 0, JSPROP_ENUMERATE);
	JS_DefineProperties(context, transitionObj, properties);
}

