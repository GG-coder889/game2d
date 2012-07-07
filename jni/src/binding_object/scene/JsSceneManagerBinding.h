#ifndef _JS_SCENE_MANAGER_BINDING_H
#define _JS_SCENE_MANAGER_BINDING_H
#include "Macros.h"
#include "jsapi.h"

class JsSceneManagerBinding {
public:
	static JS_METHOD( ChangeTo);
	static void BindingOnEngine(JSContext *context, JSObject *global);
public:
	static JSClass clz;

};
#endif
