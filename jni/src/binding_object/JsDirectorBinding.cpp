#define TAG "JsDirectorBinding"
#include "JsDirectorBinding.h"
#include "JavaScriptEngine.h"
#include "JsSizeBinding.h"
#include "JsTexture2DBinding.h"
#include "ImageResourceCache.h"
#include "Log.h"
#include "SimpleAudioEngine.h"
#include "JsScheduleManager.h"
using namespace CocosDenshion;
JSClass JsDirectorBinding::clz = { "Application", 0, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JSBool JsDirectorBinding::SetDisplayFPS(JSContext *context, unsigned int argc,
		jsval *vp) {
	JSBool displayFPS = false;
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		displayFPS = JSVAL_TO_BOOLEAN(args[0]);
	}
	CCDirector::sharedDirector()->setDisplayFPS(displayFPS);
	return JS_TRUE;
}

JSBool JsDirectorBinding::GetWinSize(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 0) {
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCSize *pSize = new CCSize(size.width, size.height);
		JSObject *newObj = JS_NewObject(context, &JsSizeBinding::clz,
				JsSizeBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pSize);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}
JSBool JsDirectorBinding::End(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 0) {
		CCDirector::sharedDirector()->end();
		ImageResourceCache::PurgeImageResourceCache();
		JsScheduleManager::PurgeScheduleManager();
	}
	return JS_TRUE;
}

JSBool JsDirectorBinding::Start(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		if (!CCDirector::sharedDirector()->getRunningScene()) {
			jsval *args = JS_ARGV(context, vp);
			JSObject *sceneObj;
			JS_ValueToObject(context, args[0], &sceneObj);
			CCScene *pScene = static_cast<CCScene*> (JS_GetPrivate(context,
					sceneObj));
			if (pScene) {
				CCDirector::sharedDirector()->runWithScene(pScene);
			}
		}
	}
	return JS_TRUE;
}

JSBool JsDirectorBinding::Pause(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 0) {
		CCDirector::sharedDirector()->pause();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	return JS_TRUE;
}

JSBool JsDirectorBinding::Resume(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 0) {
		CCDirector::sharedDirector()->resume();
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	return JS_TRUE;
}

JSBool JsDirectorBinding::GetResource(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *keyStr = JS_ValueToString(context, args[0]);
		char *pKey = JS_EncodeString(context, keyStr);
		CCTexture2D *pTexture =
				ImageResourceCache::SharedImageResourceCache()->GetImage(pKey);
		if (pTexture) {
			JSObject *newObj = JS_NewObject(context, &JsTexture2DBinding::clz,
					JsTexture2DBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pTexture);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
		JS_free(context, pKey);
	}
	return JS_TRUE;
}

JSBool JsDirectorBinding::LoadResources(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 2) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		JSIdArray * imgArray = JS_Enumerate(context, jsonObj);
		jsuint arrayLen = imgArray->length;
		jsval callbackFunction = args[1];
		int argc = 1;
		jsval callArgs[argc];
		jsval rVal;
		jsid id;
		jsval imgVal;
		jsval fileVal;
		JSString *imgStr;
		JSString *fileStr;
		for (int i = 0; i < arrayLen; i++) {
			id = imgArray->vector[i];
			JS_IdToValue(context, id, &imgVal);
			JS_GetPropertyById(context, jsonObj, id, &fileVal);

			if (!JSVAL_IS_VOID(imgVal) && !JSVAL_IS_VOID(fileVal)) {
				imgStr = JSVAL_TO_STRING(imgVal);
				fileStr = JSVAL_TO_STRING(fileVal);
				char *img = JS_EncodeString(context, imgStr);
				char *file = JS_EncodeString(context, fileStr);
				bool
						isAdded =
								ImageResourceCache::SharedImageResourceCache()->AddImage(
										img, file);
				if (isAdded) {
					callArgs[0] = INT_TO_JSVAL(i + 1);
					JS_CallFunctionValue(context,
							JavaScriptEngine::ShareInstance().ShareObject(),
							callbackFunction, argc, args, &rVal);
				}
				JS_free(context, img);
				JS_free(context, file);
			}

		}
	}
	return JS_TRUE;
}
void JsDirectorBinding::BindingOnEngine(JSContext *context, JSObject *global) {
	JSObject *directorObj = JS_DefineObject(context, global, "Application",
			&clz, 0, JSPROP_ENUMERATE);
	JSFunctionSpec methods[] = { JS_FN("setDisplayFPS", SetDisplayFPS, 1, 0),
			JS_FN("getWinSize", GetWinSize, 0, 0), JS_FN("exit", End, 0, 0),
			JS_FN("start", Start, 1, 0), JS_FN("pause", Pause, 0, 0), JS_FN(
					"resume", Resume, 0, 0), JS_FN("getResource", GetResource,
					1, 0), JS_FN("loadResources", LoadResources, 2, 0),
			JS_FS_END };
	JS_DefineFunctions(context, directorObj, methods);
}
