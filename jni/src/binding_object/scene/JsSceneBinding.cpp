#define TAG "JsSceneBinding"
#include "JsSceneBinding.h"
#include "JsLayerBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"
#include "JsScene.h"
JSObject *JsSceneBinding::obj = NULL;
JSClass JsSceneBinding::clz = { "Scene", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_METHOD(JsSceneBinding,Status) {
	JSObject *thisObj = JS_THIS_OBJECT(context,vp);
	JsScene *pScene = static_cast<JsScene*>(JS_GetPrivate(context,thisObj));
	if(pScene) {
		if(argc == 1) {
			jsval *args = JS_ARGV(context, vp);
			pScene->SetStatus(args[0]);
		}
		JS_SET_RVAL(context,vp, pScene->GetStatus());
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSceneBinding,Loop) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsScene *pScene = static_cast<JsScene*>(JS_GetPrivate(context,thisObj));
		if(pScene) {
			pScene->Loop(JSVAL_TO_DOUBLE(args[0]),thisObj);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSceneBinding,ControlPanel) {
	if(argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsScene *pScene = static_cast<JsScene*>(JS_GetPrivate(context,thisObj));
		JsLayer *pLayer = pScene->ControlPanel();
		if(pLayer) {
			JSObject *newObj = JS_NewObject(context, &JsLayerBinding::clz, JsLayerBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pLayer);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSBool JsSceneBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 0) {
		JsScene* pScene = JsScene::node();
		if (pScene == NULL) {
			JS_ReportOutOfMemory(context);
			return JS_FALSE;
		}
		if (JS_IsConstructing(context, vp)) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pScene);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JSObject *thisObj = JS_THIS_OBJECT(context, vp);
			JS_SetPrivate(context, thisObj, pScene);
		}
		return JS_TRUE;
	}
	return JS_FALSE;
}

JSObject * JsSceneBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("constructor", Create, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"status", Status, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"controlPanel", ControlPanel, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN("loop",
			Loop, 0, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
			JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
