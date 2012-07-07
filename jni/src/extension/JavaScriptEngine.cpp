#define TAG "JavaScriptEngine"
#include "JavaScriptEngine.h"
#include "JsObjectBinding.h"
#include "Log.h"
JSClass JavaScriptEngine::globalClass = { "Global", JSCLASS_GLOBAL_FLAGS,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JavaScriptEngine::JavaScriptEngine() {
	globalContext = NULL;
	globalRuntime = NULL;
	globalObject = NULL;

}

void JavaScriptEngine::BindingGlobalObject() {
	GlobalFunction::BindingOnEngine(globalContext, globalObject);
	JsDirectorBinding::BindingOnEngine(globalContext, globalObject);
	JsSimpleAudioEngineBinding::BindingOnEngine(globalContext, globalObject);
	JsSpriteFrameCacheBinding::BindingOnEngine(globalContext, globalObject);
	JsAnimationCacheBinding::BindingOnEngine(globalContext, globalObject);
	JsSceneManagerBinding::BindingOnEngine(globalContext, globalObject);
	JsTransitionSceneBinding::BindingOnEngine(globalContext, globalObject);
	JsTextAlignmentBinding::BindingOnEngine(globalContext, globalObject);
	JsLogBinding::BindingOnEngine(globalContext, globalObject);
	JsTextureCacheBinding::BindingOnEngine(globalContext, globalObject);
}

void JavaScriptEngine::BindingObject() {
	JSObject *nodeObj = JsNodeBinding::BindingOnEngine(globalContext,
			globalObject, NULL);
	JsTexture2DBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsPointBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsSizeBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsRectBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsSpriteFrameBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsAnimationBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsAnimateBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsMoveByBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsDelayTimeBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsFadeOutBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsFadeInBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsProgressToBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsRepeatForeverBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsSpeedBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsRepeatBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsRotateToBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsRotateByBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsEaseElasticOutBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsEaseOutBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsBezierToBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsBezierByBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsMoveToBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsSequenceBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsSpawnBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsCallFuncBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsTMXTiledMapBinding::BindingOnEngine(globalContext, globalObject, nodeObj);
	JsTMXLayerBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsTMXObjectGroupBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsStringDictionaryBinding::BindingOnEngine(globalContext, globalObject,
			NULL);
	JsSceneBinding::BindingOnEngine(globalContext, globalObject, nodeObj);
	JSObject *layerObj = JsLayerBinding::BindingOnEngine(globalContext,
			globalObject, nodeObj);
	JsBox2dDebugLayerBinding::BindingOnEngine(globalContext, globalObject,
			layerObj);
	JsLayerColorBinding::BindingOnEngine(globalContext, globalObject, layerObj);
	JsMenuBinding::BindingOnEngine(globalContext, globalObject, layerObj);
	JsGLESDebugDrawBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsSpriteBinding::BindingOnEngine(globalContext, globalObject, nodeObj);
	JsLabelBMFontBinding::BindingOnEngine(globalContext, globalObject, nodeObj);
	JsLabelTTFBinding::BindingOnEngine(globalContext, globalObject, nodeObj);
	JsSpriteBatchNodeBinding::BindingOnEngine(globalContext, globalObject,
			nodeObj);
	JsMenuItemImageBinding::BindingOnEngine(globalContext, globalObject,
			nodeObj);
	JsMenuItemFontBinding::BindingOnEngine(globalContext, globalObject, nodeObj);
	JsProgressTimerBinding::BindingOnEngine(globalContext, globalObject,
			nodeObj);
	JsParticleSystemQuadBinding::BindingOnEngine(globalContext, globalObject,
			nodeObj);
	Jsb2BodyBinding::BindingOnEngine(globalContext, globalObject, NULL);
	Jsb2WorldBinding::BindingOnEngine(globalContext, globalObject, NULL);
	Jsb2PolygonShapeBinding::BindingOnEngine(globalContext, globalObject, NULL);
	Jsb2BodyDefBinding::BindingOnEngine(globalContext, globalObject, NULL);
	Jsb2FixtureDefBinding::BindingOnEngine(globalContext, globalObject, NULL);
	Jsb2CircleShapeBinding::BindingOnEngine(globalContext, globalObject, NULL);
	Jsb2EdgeShapeBinding::BindingOnEngine(globalContext, globalObject, NULL);

	JsColor3BBinding::BindingOnEngine(globalContext, globalObject, NULL);
	JsTouchBinding::BindingOnEngine(globalContext, globalObject, NULL);
}

char * JavaScriptEngine::LoadJsFile(const char* fileName) {
	unsigned long bufferSize = 0;
	char *codes = NULL;
	char* data = (char*) (CCFileUtils::getFileData(fileName, "r", &bufferSize));
	if (data) {
		codes = new char[bufferSize + 1];
		codes[bufferSize] = '\0';
		memcpy(codes, data, bufferSize);
		delete[] data;
		data = NULL;
	}
	return codes;
}

void JavaScriptEngine::ReportError(JSContext *cx, const char *message,
		JSErrorReport *report) {
	LogInfo(TAG, "file is %s,line number is %u, message is :%s\n",
			report->filename ? report->filename : "",
			(unsigned int) report->lineno, message);
}
void JavaScriptEngine::RunScript(const char *fileName) {
	char * scriptStr = LoadJsFile(fileName);
	if (scriptStr == NULL) {
		return;
	}
	int lineNumber = 0;
	JSObject *script = JS_CompileScript(globalContext, globalObject, scriptStr,
			strlen(scriptStr), fileName, lineNumber);
	delete[] scriptStr;
	if (script == NULL) {
		return;
	}
	jsval rval;
	JSBool status =
			JS_ExecuteScript(globalContext, globalObject, script, &rval);
	if (status == JS_FALSE) {
		if (JSVAL_IS_NULL(rval)) {
			LogInfo(TAG, "rval : (JSVAL_IS_NULL(rval)");
		} else if ((JSVAL_IS_BOOLEAN(rval)) && (JS_FALSE == (JSVAL_TO_BOOLEAN(
				rval)))) {
			LogInfo(TAG, "rval : (return value is JS_FALSE");
		} else if (JSVAL_IS_STRING(rval)) {
			JSString *str = JS_ValueToString(globalContext, rval);
			if (str == NULL) {
				LogInfo(TAG, "rval : return string is NULL");
			} else {
				char * content = JS_EncodeString(globalContext, str);
				LogInfo(TAG, "rval : return string =\n%s\n", content);
				JS_free(globalContext, content);
			}
		} else if (JSVAL_IS_NUMBER(rval)) {
			double number;
			if (JS_FALSE == JS_ValueToNumber(globalContext, rval, &number)) {
				LogInfo(TAG, "rval : return number could not be converted");
			} else {
				LogInfo(TAG, "rval : return number =\n%f", number);
			}
		}
	}
}

void JavaScriptEngine::Start() {

	globalRuntime = JS_NewRuntime(32L * 1024L * 1024L);
	if (globalRuntime == NULL) {
		LogInfo(TAG, "(globalRuntime == NULL)");
		return;
	}
	globalContext = JS_NewContext(globalRuntime, 8192);
	if (globalContext == NULL) {
		LogInfo(TAG, "(globalContext == NULL)");
		return;
	}
	JS_SetOptions(globalContext, JSOPTION_VAROBJFIX);
	JS_SetVersion(globalContext, JSVERSION_LATEST);
	JS_SetErrorReporter(globalContext, ReportError);
	globalObject = JS_NewCompartmentAndGlobalObject(globalContext,
			&globalClass, NULL);
	if (globalObject == NULL) {
		LogInfo(TAG, "(globalObject == NULL)");
		return;
	}
	if (!JS_InitStandardClasses(globalContext, globalObject)) {
		LogInfo(TAG, "(!JS_InitStandardClasses(globalContext, global))");
		return;
	}
	BindingGlobalObject();
	BindingObject();
	RunScript("index.js");
}

void JavaScriptEngine::GC() {
	if (globalContext) {
		JS_GC( globalContext);
	}
}

void JavaScriptEngine::ShutDown() {
	JS_DestroyContext( globalContext);
	JS_DestroyRuntime( globalRuntime);
	JS_ShutDown();
}

