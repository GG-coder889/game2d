#define TAG "JsTMXTiledMapBinding"
#include "JsTMXTiledMapBinding.h"
#include "JsSizeBinding.h"
#include "JsTMXLayerBinding.h"
#include "JsTMXObjectGroupBinding.h"
#include "Log.h"

JSClass JsTMXTiledMapBinding::clz = { "TMXTiledMap", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsTMXTiledMapBinding::obj = NULL;

JS_CLASS_METHOD(JsTMXTiledMapBinding,LayerNamed) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXTiledMap *pMap = static_cast<CCTMXTiledMap*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSString *layerNameStr = JS_ValueToString(context, args[0]);
		char *pLayerName = JS_EncodeString(context, layerNameStr);
		CCTMXLayer *pLayer = pMap->layerNamed(pLayerName);
		JSObject *newObj = JS_NewObject(context, &JsTMXLayerBinding::clz,
				JsTMXLayerBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pLayer);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		JS_free(context,pLayerName);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsTMXTiledMapBinding,ObjectGroupNamed) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXTiledMap *pMap = static_cast<CCTMXTiledMap*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSString *groupNameStr = JS_ValueToString(context, args[0]);
		char *pGroupName = JS_EncodeString(context, groupNameStr);
		CCTMXObjectGroup *pGroup = pMap->objectGroupNamed(pGroupName);
		JSObject *newObj = JS_NewObject(context, &JsTMXObjectGroupBinding::clz,
				JsTMXObjectGroupBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pGroup);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		JS_free(context,pGroupName);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsTMXTiledMapBinding,GetMapSize) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXTiledMap *pMap = static_cast<CCTMXTiledMap*>(JS_GetPrivate(context,thisObj));
		CCSize *pSize = new CCSize(pMap->getMapSize().width,
				pMap->getMapSize().height);
		JSObject *newObj = JS_NewObject(context, &JsSizeBinding::clz,
				JsSizeBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pSize);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsTMXTiledMapBinding,GetTileSize) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXTiledMap *pMap = static_cast<CCTMXTiledMap*>(JS_GetPrivate(context,thisObj));
		CCSize *pSize = new CCSize(pMap->getTileSize().width,
				pMap->getTileSize().height);
		JSObject *newObj = JS_NewObject(context, &JsSizeBinding::clz,
				JsSizeBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pSize);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsTMXTiledMapBinding,InitWithTMXFile) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *mapFileStr = JS_ValueToString(context, args[0]);
		char *pMapFile = JS_EncodeString(context, mapFileStr);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXTiledMap *pMap = static_cast<CCTMXTiledMap*>(JS_GetPrivate(context,thisObj));
		pMap->initWithTMXFile(pMapFile);
		JS_free(context, pMapFile);
	}
	return JS_TRUE;
}
JSBool JsTMXTiledMapBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj = NULL;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval mapFileVal;
		JS_GetProperty(context, jsonObj, "mapFile", &mapFileVal);
		if (!JSVAL_IS_VOID(mapFileVal)) {
			JSString *mapFileStr = JS_ValueToString(context, mapFileVal);
			char *pMapFile = JS_EncodeString(context, mapFileStr);
			CCTMXTiledMap *pMap = CCTMXTiledMap::tiledMapWithTMXFile(pMapFile);
			if (pMap) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pMap);
				JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
			}
			JS_free(context, pMapFile);
		}
	} else {
		CCTMXTiledMap *pMap = new CCTMXTiledMap();
		pMap->autorelease();
		if (JS_IsConstructing(context, vp)) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pMap);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JSObject *thisObj = JS_THIS_OBJECT(context, vp);
			JS_SetPrivate(context, thisObj, pMap);
		}
	}
	return JS_TRUE;
}

JSObject * JsTMXTiledMapBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "initWithTMXFile", InitWithTMXFile, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE }, {
			"getMapSize", GetMapSize, 0, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "getTileSize", GetTileSize, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE }, {
			"layerNamed", LayerNamed, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, { "objectGroupNamed",
			ObjectGroupNamed, 1, JSPROP_PERMANENT | JSPROP_SHARED
					| JSPROP_ENUMERATE }, JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

