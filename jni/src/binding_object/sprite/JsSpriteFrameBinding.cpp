#define TAG "JsSpriteFrameBinding"
#include "JsSpriteFrameBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"

JSObject *JsSpriteFrameBinding::obj = NULL;
JSClass JsSpriteFrameBinding::clz = { "SpriteFrame", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };

JS_CLASS_METHOD(JsSpriteFrameBinding,SetOffsetInPixels) {
	if(argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCSpriteFrame *pFrame = static_cast<CCSpriteFrame*>(JS_GetPrivate(context,thisObj));
		if(pFrame) {
			jsval *args = JS_ARGV(context, vp);
			double x = 0;
			double y = 0;
			JS_ValueToNumber(context, args[0], &x);
			JS_ValueToNumber(context, args[1], &y);
			pFrame->setOffsetInPixels(ccp(x, y));
		}
	}
	return JS_TRUE;
}
JSBool JsSpriteFrameBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval textureVal;
		jsval rectVal;
		JS_GetProperty(context, jsonObj, "texture", &textureVal);
		JS_GetProperty(context, jsonObj, "rect", &rectVal);
		if (!JSVAL_IS_VOID(textureVal) && !JSVAL_IS_VOID(rectVal)) {
			JSObject *textureObj;
			JS_ValueToObject(context, textureVal, &textureObj);
			JSObject * rectObj;
			JS_ValueToObject(context, rectVal, &rectObj);
			CCTexture2D *pTexture = static_cast<CCTexture2D*> (JS_GetPrivate(
					context, textureObj));
			CCRect *pRect = static_cast<CCRect*> (JS_GetPrivate(context,
					rectObj));
			CCSpriteFrame *pFrame = CCSpriteFrame::frameWithTexture(pTexture,
					*pRect);
			if (pFrame == NULL) {
				JS_ReportOutOfMemory(context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pFrame);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * JsSpriteFrameBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("setOffsetInPixels", SetOffsetInPixels,
			2, JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

