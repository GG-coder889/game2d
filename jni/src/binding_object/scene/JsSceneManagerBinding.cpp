#define TAG "JsSceneManagerBinding"
#include "JsSceneManagerBinding.h"
#include "TransitionSceneEnum.h"
#include "cocos2d.h"
#include "Log.h"
#include "JsSceneManager.h"
#include "JsScheduleManager.h"
#include "JavaScriptEngine.h"
#include "JsScene.h"
using namespace cocos2d;

JSClass JsSceneManagerBinding::clz = { "SceneManager", 0, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_METHOD(JsSceneManagerBinding,ChangeTo) {
	CCScene *pScene = NULL;
	if (argc == 3) {
		jsval *args = JS_ARGV(context, vp);
		pScene = static_cast<JsScene*>(JS_GetPrivate(context,JSVAL_TO_OBJECT(args[0])));
		TransitionSceneEnum transition = static_cast<TransitionSceneEnum> (JSVAL_TO_INT(args[1]));
		double time = JSVAL_TO_DOUBLE(args[2]);
		JsSceneManager::ChangeTo(transition,time,pScene);
	} else if(argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		pScene = static_cast<JsScene*>(JS_GetPrivate(context,JSVAL_TO_OBJECT(args[0])));
		JsSceneManager::ChangeTo(pScene);
	}
	return JS_TRUE;
}

void JsSceneManagerBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSFunctionSpec methods[] = { JS_FN("changeTo", ChangeTo, 1, 0), JS_FS_END };
	JSObject *directorObj = JS_DefineObject(context, global, "SceneManager",
			&clz, 0, JSPROP_ENUMERATE);
	JS_DefineFunctions(context, directorObj, methods);
}
