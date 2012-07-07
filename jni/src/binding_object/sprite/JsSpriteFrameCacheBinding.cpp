#define TAG "JsSpriteFrameCacheBinding"
#include "JsSpriteFrameCacheBinding.h"
#include "JsSpriteFrameBinding.h"
#include "Log.h"

JSClass JsSpriteFrameCacheBinding::clz = { "SpriteFrameCache", 0,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JSBool JsSpriteFrameCacheBinding::AddSpriteFramesWithFile(JSContext *context,
		unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *fileNameStr = JS_ValueToString(context, args[0]);
		char *fileName = JS_EncodeString(context, fileNameStr);
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
				fileName);
		JS_free(context, fileName);
	}
	return JS_TRUE;
}

JSBool JsSpriteFrameCacheBinding::SpriteFrameByName(JSContext *context,
		unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *fileNameStr = JS_ValueToString(context, args[0]);
		char *fileName = JS_EncodeString(context, fileNameStr);
		CCSpriteFrame
				*pSpriteFrame =
						CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
								fileName);
		JSObject *newObj = JS_NewObject(context, &JsSpriteFrameBinding::clz,
				JsSpriteFrameBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pSpriteFrame);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		JS_free(context, fileName);
	}
	return JS_TRUE;
}

void JsSpriteFrameCacheBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSFunctionSpec methods[] = { JS_FN("addSpriteFramesWithFile",
			AddSpriteFramesWithFile, 1, 0), JS_FN("spriteFrameByName",
			SpriteFrameByName, 1, 0), JS_FS_END };

	JSObject *frameObj = JS_DefineObject(context, global, "SpriteFrameCache",
			&clz, 0, JSPROP_ENUMERATE);
	JS_DefineFunctions(context, frameObj, methods);
}
