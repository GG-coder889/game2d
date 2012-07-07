#ifndef _JS_TMXTILEDMAP_BINDING_H
#define _JS_TMXTILEDMAP_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;

class JsTMXTiledMapBinding {

public:
	static JS_METHOD( GetMapSize);
	static JS_METHOD( GetTileSize);
	static JS_METHOD( LayerNamed);
	static JS_METHOD( ObjectGroupNamed);
	static JS_METHOD( InitWithTMXFile);
	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
