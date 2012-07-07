#define TAG "JsSpriteBatchNodeBinding"
#include "JsSpriteBatchNodeBinding.h"
#include "JsTexture2DBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"

JSObject *JsSpriteBatchNodeBinding::obj = NULL;
JSClass JsSpriteBatchNodeBinding::clz = { "SpriteBatchNode",
		JSCLASS_HAS_PRIVATE, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_METHOD(JsSpriteBatchNodeBinding,Create) {
	if(argc == 0 ) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval fileNameVal;
		JS_GetProperty(context, jsonObj,
				"fileName", &fileNameVal);
		jsval capacityVal;
		JS_GetProperty(context, jsonObj,
				"capacity", &capacityVal);
		if(!JSVAL_IS_NULL(fileNameVal) && !JSVAL_IS_NULL(capacityVal)) {
			JSString *fileNameStr = JS_ValueToString(context, fileNameVal);
			char * fileName = JS_EncodeString(context,fileNameStr);
			int capacity = 0;
			JS_ValueToInt32(context,capacityVal,&capacity);
			CCSpriteBatchNode *pBatchNode = CCSpriteBatchNode::batchNodeWithFile(
					fileName, capacity);
			JS_free(context, fileName);
			if(pBatchNode) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context,newObj, pBatchNode);
				JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			}

		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBatchNodeBinding,GetTexture) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCSpriteBatchNode *pBatchNode = static_cast<CCSpriteBatchNode*>(JS_GetPrivate(context,thisObj));
		if (pBatchNode) {
			JSObject *newObj = JS_NewObject(context, &JsTexture2DBinding::clz, JsTexture2DBinding::obj, NULL);
			JS_SetPrivate(context,newObj, pBatchNode->getTexture());
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * JsSpriteBatchNodeBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {

	JSFunctionSpec methods[] = { { "getTexture", GetTexture, 1,
			JSPROP_PERMANENT | JSPROP_SHARED }, JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

