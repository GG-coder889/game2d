#ifndef _JS_TMXLAYER_BINDING_H
#define _JS_TMXLAYER_BINDING_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
using namespace cocos2d;

class JsTMXLayerBinding {
public:
	static JS_METHOD( TileGIDAt);
	static JS_METHOD( RemoveTileAt);
	static JS_METHOD( SetTileGID);

	static JSBool Create(JSContext *cx, unsigned int argc, jsval *argv);
	static JSObject * BindingOnEngine(JSContext *ctx, JSObject *global,
			JSObject *parent);
public:
	static JSClass clz;
	static JSObject *obj;
};
#endif
