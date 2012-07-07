#define TAG "JsLayerBinding"
#include "JsLayerBinding.h"
#include "JsLayer.h"
#include "Log.h"
JSClass JsLayerBinding::clz = { "Layer", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsLayerBinding::obj = NULL;

JS_CLASS_METHOD(JsLayerBinding,SetIsTouchEnabled) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSBool enable = false;
		JS_ConvertArguments (context,argc,args,"b",&enable);
		pLayer->setIsTouchEnabled(enable);
		pLayer->SetCallbackObj(thisObj);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsLayerBinding,SetIsMultiTouches) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSBool enable = false;
		JS_ConvertArguments (context,argc,args,"b",&enable);
		pLayer->SetIsMultiTouches(enable);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsLayerBinding,SetIsAccelerometerEnabled) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSBool enable = false;
		JS_ConvertArguments (context,argc,args,"b",&enable);
		pLayer->setIsAccelerometerEnabled(enable);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( JsLayerBinding, OnTouchesMoved) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchesMovedCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchesEnded) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchesEndedCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchesBegan) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchesBeganCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchesCancelled) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchesCancelledCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchMoved) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchMovedCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchEnded) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchEndedCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchBegan) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchBeganCallback(args[0]);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD( JsLayerBinding, OnTouchCancelled) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsLayer * pLayer =static_cast<JsLayer*> (JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pLayer->SetJsTouchCancelledCallback(args[0]);
	}
	return JS_TRUE;
}
JSBool JsLayerBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 0) {
		JsLayer* pLayer = JsLayer::node();
		if (pLayer == NULL) {
			JS_ReportOutOfMemory(context);
			return JS_FALSE;
		}
		if (JS_IsConstructing(context, vp)) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pLayer);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JSObject *thisObj = JS_THIS_OBJECT(context, vp);
			JS_SetPrivate(context, thisObj, pLayer);
		}
		return JS_TRUE;
	}
	return JS_FALSE;
}

JSObject * JsLayerBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "constructor", Create, 0, JSPROP_PERMANENT
			| JSPROP_SHARED | JSPROP_ENUMERATE }, { "setIsTouchEnabled",
			SetIsTouchEnabled, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "setIsMultiTouches",
			SetIsMultiTouches, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "setIsAccelerometerEnabled",
			SetIsAccelerometerEnabled, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "onTouchesBegan", OnTouchesBegan,
			1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE }, {
			"onTouchesMoved", OnTouchesMoved, 1, JSPROP_PERMANENT
					| JSPROP_SHARED | JSPROP_ENUMERATE }, { "onTouchesEnded",
			OnTouchesEnded, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "onTouchesCancelled",
			OnTouchesCancelled, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "onTouchBegan", OnTouchBegan, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE }, {
			"onTouchMoved", OnTouchMoved, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "onTouchEnded", OnTouchEnded, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE }, {
			"onTouchCancelled", OnTouchCancelled, 1, JSPROP_PERMANENT
					| JSPROP_SHARED | JSPROP_ENUMERATE }, JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

