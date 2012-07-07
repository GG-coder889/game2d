#include "JsSimpleAudioEngineBinding.h"

JSClass JsSimpleAudioEngineBinding::clz = { "Audio", 0, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

void JsSimpleAudioEngineBinding::BindingOnEngine(JSContext *context,
		JSObject *global) {
	JSFunctionSpec methods[] = { JS_FN("playBackgroundMusic",
			PlayBackgroundMusic, 1, 0), JS_FN("stopBackgroundMusic",
			StopBackgroundMusic, 1, 0), JS_FN("pauseBackgroundMusic",
			PauseBackgroundMusic, 0, 0), JS_FN("resumeBackgroundMusic",
			ResumeBackgroundMusic, 0, 0), JS_FN("setBackgroundMusicVolume",
			SetBackgroundMusicVolume, 1, 0), JS_FN("playEffect", PlayEffect, 1,
			0), JS_FS_END };
	JSObject *audioObj = JS_DefineObject(context, global, "Audio", &clz, 0,
			JSPROP_ENUMERATE);
	JS_DefineFunctions(context, audioObj, methods);
}

JS_CLASS_METHOD(JsSimpleAudioEngineBinding,PlayBackgroundMusic)
{
	if(argc >= 1)
	{
		jsval *args = JS_ARGV(context, vp);
		JSString *fileNameStr = JS_ValueToString(context,args[0]);
		char *pFileName = JS_EncodeString(context,fileNameStr);
		JSBool bLoop = false;
		if(argc == 2)
		{
			JS_ValueToBoolean(context,args[1],&bLoop);
		}
		if(pFileName)
		{
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(pFileName,bLoop);
		}
		JS_free(context,pFileName);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSimpleAudioEngineBinding,StopBackgroundMusic)
{
	if(argc == 1)
	{
		jsval *args = JS_ARGV(context, vp);
		JSBool bReleaseData = false;
		JS_ValueToBoolean(context,args[0],&bReleaseData);
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(bReleaseData);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsSimpleAudioEngineBinding,PlayEffect)
{
	if(argc >= 1)
	{	jsval *args = JS_ARGV(context, vp);
		JSString *fileNameStr = JS_ValueToString(context,args[0]);
		char *pFileName = JS_EncodeString(context,fileNameStr);
		JSBool bLoop = false;
		if(argc == 2)
		{
			JS_ValueToBoolean(context,args[1],&bLoop);
		}
		if(pFileName)
		{
			SimpleAudioEngine::sharedEngine()->playEffect(pFileName,bLoop);
		}
		JS_free(context,pFileName);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsSimpleAudioEngineBinding,PauseBackgroundMusic)
{
	if(argc == 0)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsSimpleAudioEngineBinding,SetBackgroundMusicVolume)
{
	if(argc == 1)
	{
		jsval *args = JS_ARGV(context, vp);
		double volume = 0;
		JS_ValueToNumber(context,args[0],&volume);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsSimpleAudioEngineBinding,ResumeBackgroundMusic)
{
	if(argc == 0)
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	return JS_TRUE;
}

