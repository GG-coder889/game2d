#ifndef _JS_SIMPLEAUDIOENGINE_BINDING_H
#define _JS_SIMPLEAUDIOENGINE_BINDING_H

#include "SimpleAudioEngine.h"
#include "jsapi.h"
#include "Macros.h"
using namespace CocosDenshion;

class JsSimpleAudioEngineBinding {
public:
	static JS_METHOD( PlayBackgroundMusic);
	static JS_METHOD( StopBackgroundMusic);
	static JS_METHOD( PauseBackgroundMusic);
	static JS_METHOD( SetBackgroundMusicVolume);
	static JS_METHOD( ResumeBackgroundMusic);
	static JS_METHOD( PlayEffect);
	static void BindingOnEngine(JSContext *context, JSObject *global);
private:
	static JSClass clz;
};
#endif
