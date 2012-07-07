#define TAG "JsSpriteBinding"
#include "JsSpriteBinding.h"
#include "JavaScriptEngine.h"
#include "cocos2d.h"
#include "JsSprite.h"
#include "Log.h"
using namespace cocos2d;

JSClass JsSpriteBinding::clz = { "Sprite", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsSpriteBinding::obj = NULL;

JS_CLASS_METHOD(JsSpriteBinding,SetTextureRect) {
	if (argc == 4) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
		double x = 0;
		double y = 0;
		double w = 0;
		double h = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"dddd",&x,&y,&w,&h);
		pSprite->setTextureRect(CCRectMake(x, y, w, h));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,SetOpacity) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pSprite->setOpacity(JSVAL_TO_INT(args[0]));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,Status) {
	JSObject *thisObj = JS_THIS_OBJECT(context,vp);
	JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
	if(pSprite) {
		if(argc == 1) {
			jsval *args = JS_ARGV(context, vp);
			pSprite->SetStatus(args[0]);
		}
		JS_SET_RVAL(context,vp, pSprite->GetStatus());
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,Loop) {
	JSObject *thisObj = JS_THIS_OBJECT(context,vp);
	double delay = 0;
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JS_ValueToNumber(context,args[0],&delay);
	}
	JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
	if(pSprite) {
		pSprite->Loop(delay,thisObj);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,SpriteWithFile) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval fileNameVal;
		jsval rectVal;
		JS_GetProperty(context, jsonObj,
				"rect", &rectVal);
		JS_GetProperty(context, jsonObj,
				"fileName", &fileNameVal);
		if (!JSVAL_IS_VOID(fileNameVal)) {
			JSString *fileStr = JSVAL_TO_STRING(fileNameVal);
			JsSprite *pSprite = NULL;
			char *file = JS_EncodeString(context,fileStr);
			if(JSVAL_IS_VOID(rectVal)) {
				pSprite = JsSprite::SpriteWithFile(
						file);
			} else {
				JSObject *rectObj;
				JS_ValueToObject(context,rectVal, &rectObj);
				CCRect *pRect = static_cast<CCRect*>(JS_GetPrivate(context,rectObj));
				pSprite = JsSprite::SpriteWithFile(file,
						*pRect);
			}
			JS_free(context,file);
			if (pSprite == NULL) {
				JS_ReportOutOfMemory( context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz,
					obj, NULL);
			JS_SetPrivate(context,newObj, pSprite);
			JS_SET_RVAL(cx, vp,OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsSpriteBinding,SpriteWithTexture) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval textureVal;
		jsval rectVal;
		JS_GetProperty(context, jsonObj,
				"texture", &textureVal);
		JS_GetProperty(context, jsonObj,
				"rect", &rectVal);
		if (JSVAL_IS_OBJECT(textureVal) && !JSVAL_IS_NULL(textureVal)) {
			JSObject *textureObj;
			JS_ValueToObject(context,textureVal, &textureObj);
			CCTexture2D *pTexture = static_cast<CCTexture2D*>(JS_GetPrivate(context,textureObj));
			JsSprite *pSprite = NULL;
			if(JSVAL_IS_VOID(rectVal)) {
				pSprite = JsSprite::SpriteWithTexture(
						pTexture);
			} else {
				JSObject *rectObj;
				JS_ValueToObject(context,rectVal, &rectObj);
				CCRect *pRect = static_cast<CCRect*>(JS_GetPrivate(context,rectObj));
				pSprite = JsSprite::SpriteWithTexture(pTexture,
						*pRect);
			}
			if (pSprite == NULL) {
				JS_ReportOutOfMemory( context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz,
					obj, NULL);
			JS_SetPrivate(context,newObj, pSprite);
			JS_SET_RVAL(cx, vp,OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsSpriteBinding,SpriteWithSpriteFrame) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval frameVal;
		JSBool isContainedFrame = JS_GetProperty(context, jsonObj,
				"frame", &frameVal);
		if (isContainedFrame == JS_TRUE) {
			JSObject *frameObj;
			JS_ValueToObject(context,frameVal, &frameObj);
			CCSpriteFrame *pSpriteFrame = static_cast<CCSpriteFrame*>(JS_GetPrivate(context,frameObj));
			JsSprite *pSprite = JsSprite::SpriteWithSpriteFrame(
					pSpriteFrame);
			if (pSprite == NULL) {
				JS_ReportOutOfMemory( context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz,
					obj, NULL);
			JS_SetPrivate(context,newObj, pSprite);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,InitWithFile) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
		JSString *fileStr = JSVAL_TO_STRING(args[0]);
		char *file = JS_EncodeString(context,fileStr);
		pSprite->initWithFile(file);
		JS_free(context,file);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,InitWithSpriteFrame) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
		JSObject *frameObj;
		JS_ValueToObject(context,args[0], &frameObj);
		CCSpriteFrame *pSpriteFrame = static_cast<CCSpriteFrame*>(JS_GetPrivate(context,frameObj));
		pSprite->initWithSpriteFrame(pSpriteFrame);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsSpriteBinding,InitWithTexture) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		JsSprite *pSprite = static_cast<JsSprite*>(JS_GetPrivate(context,thisObj));
		JSObject *frameObj;
		JS_ValueToObject(context,args[0], &frameObj);
		CCTexture2D *pTexture = static_cast<CCTexture2D*>(JS_GetPrivate(context,frameObj));
		pSprite->initWithTexture(pTexture);
	}
	return JS_TRUE;
}

JSBool JsSpriteBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval fileNameVal;
		JS_GetProperty(context, jsonObj, "fileName", &fileNameVal);
		if (!JSVAL_IS_VOID(fileNameVal)) {
			JSString *fileNameStr = JS_ValueToString(context, fileNameVal);
			char *file = JS_EncodeString(context, fileNameStr);
			JsSprite *pSprite = JsSprite::SpriteWithFile(file);
			JS_free(context, file);
			if (pSprite == NULL) {
				JS_ReportOutOfMemory(context);
			}
			if (JS_IsConstructing(context, vp)) {
				JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
				JS_SetPrivate(context, newObj, pSprite);
				JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
			} else {
				JSObject *thisObj = JS_THIS_OBJECT(context, vp);
				JS_SetPrivate(context, thisObj, pSprite);
			}
			return JS_TRUE;
		}
	} else {
		JsSprite *pSprite = new JsSprite();
		pSprite->autorelease();
		if (JS_IsConstructing(context, vp)) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pSprite);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JSObject *thisObj = JS_THIS_OBJECT(context, vp);
			JS_SetPrivate(context, thisObj, pSprite);
		}
		return JS_TRUE;
	}
}

JSObject * JsSpriteBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("constructor", Create, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"initWithTexture", InitWithTexture, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"initWithSpriteFrame", InitWithSpriteFrame, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"initWithFile", InitWithFile, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setTextureRect", SetTextureRect, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setOpacity", SetOpacity, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN("loop",
			Loop, 1, JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
			JS_FN("status", Status, 1,
					JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE),
			JS_FS_END };

	JSFunctionSpec staticMethods[] = { JS_FN("spriteWithTexture",
			SpriteWithTexture, 1, 0), JS_FN("spriteWithSpriteFrame",
			SpriteWithSpriteFrame, 1, 0), JS_FN("spriteWithFile",
			SpriteWithFile, 1, 0), JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, staticMethods);
	return obj;
}
