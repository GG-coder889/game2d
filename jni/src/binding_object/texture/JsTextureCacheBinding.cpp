#define TAG "JsTextureCacheBinding"
#include "JsTextureCacheBinding.h"
#include "JavaScriptEngine.h"
#include "JsSizeBinding.h"
#include "JsTexture2DBinding.h"
#include "ImageResourceCache.h"
#include "Log.h"
#include "SimpleAudioEngine.h"
#include "JsScheduleManager.h"
using namespace CocosDenshion;
JSClass JsTextureCacheBinding::clz = { "TextureCache", 0, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JSBool JsTextureCacheBinding::AddImage(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *fileNameStr = JS_ValueToString(context, args[0]);
		char *fileName = JS_EncodeString(context, fileNameStr);
		CCTextureCache::sharedTextureCache()->addImage(fileName);
		JS_free(context, fileName);
	}

	return JS_TRUE;
}
void JsTextureCacheBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSObject *textureCacheObj = JS_DefineObject(context, global,
			"TextureCache", &clz, 0, JSPROP_ENUMERATE);
	JSFunctionSpec methods[] = { JS_FN("addImage", AddImage, 1, 0), JS_FS_END };
	JS_DefineFunctions(context, textureCacheObj, methods);
}
