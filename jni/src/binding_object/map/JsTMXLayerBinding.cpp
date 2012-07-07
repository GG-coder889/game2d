#define TAG "JsTMXLayerBinding"
#include "JsTMXLayerBinding.h"

JSClass JsTMXLayerBinding::clz = { "TMXLayer", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsTMXLayerBinding::obj = NULL;

JS_CLASS_METHOD(JsTMXLayerBinding,TileGIDAt) {
	if (argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXLayer *pLayer = static_cast<CCTMXLayer*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		double x = 0;
		double y = 0;
		JS_ConvertArguments(context,argc,args,"dd",&x,&y);
		int id = pLayer->tileGIDAt(ccp(x, y));
		JS_SET_RVAL(context, vp, INT_TO_JSVAL(id));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsTMXLayerBinding,SetTileGID) {
	if (argc == 3) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXLayer *pLayer = static_cast<CCTMXLayer*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		int gid = 0;
		double x = 0;
		double y = 0;
		JS_ConvertArguments(context,argc,args,"idd",&gid,&x,&y);
		pLayer->setTileGID(gid, ccp(x, y));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsTMXLayerBinding,RemoveTileAt) {
	if (argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXLayer *pLayer = static_cast<CCTMXLayer*>(JS_GetPrivate(context,thisObj));
		double x = 0;
		double y = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"dd",&x,&y);
		pLayer->removeTileAt(ccp(x, y));
	}
	return JS_TRUE;
}

JSBool JsTMXLayerBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	return JS_FALSE;
}

JSObject * JsTMXLayerBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "tileGIDAt", TileGIDAt, 2, JSPROP_PERMANENT
			| JSPROP_SHARED }, { "removeTileAt", RemoveTileAt, 3,
			JSPROP_PERMANENT | JSPROP_SHARED }, { "setTileGID", SetTileGID, 2,
			JSPROP_PERMANENT | JSPROP_SHARED }, JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
