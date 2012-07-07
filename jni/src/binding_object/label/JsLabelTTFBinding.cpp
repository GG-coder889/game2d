#define TAG "JsLabelTTFBinding"
#include "JsLabelTTFBinding.h"
#include "JavaScriptEngine.h"
#include "Log.h"

JSClass JsLabelTTFBinding::clz = { "LabelTTF", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsLabelTTFBinding::obj = NULL;

JS_CLASS_METHOD(JsLabelTTFBinding, SetColor) {
	if (argc == 3) {
		JSObject *labelObj = JS_THIS_OBJECT(context, vp);
		jsval *args = JS_ARGV(context, vp);
		CCLabelTTF * pLabel = static_cast<CCLabelTTF*> (JS_GetPrivate(context,
						labelObj));
		int r = 0;
		int g = 0;
		int b = 0;
		JS_ConvertArguments(context,argc,args,"iii",&r,&g,&b);
		pLabel->setColor(ccc3(r, g, b));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsLabelTTFBinding, SetString) {
	if (argc == 1) {
		JSObject *labelObj = JS_THIS_OBJECT(context, vp);
		jsval *args = JS_ARGV(context, vp);
		CCLabelTTF * pLabel = static_cast<CCLabelTTF*> (JS_GetPrivate(context,
						labelObj));
		JSString *labelStr = JS_ValueToString(context, args[0]);
		char * label = JS_EncodeString(context, labelStr);
		pLabel->setString(label);
		JS_free(context,label);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsLabelTTFBinding, GetString) {
	if (argc == 0) {
		JSObject *labelObj = JS_THIS_OBJECT(context, vp);
		CCLabelTTF * pLabel = static_cast<CCLabelTTF*> (JS_GetPrivate(context,
						labelObj));
		const char * label = pLabel->getString();
		JSString *lableStr = JS_NewStringCopyN(context,label,strlen(label));
		JS_SET_RVAL(context, vp, STRING_TO_JSVAL(lableStr));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsLabelTTFBinding,Create) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		JSIdArray * propertyArray = JS_Enumerate(context, jsonObj);
		jsint length = propertyArray->length;
		JS_DestroyIdArray(context,propertyArray);
		jsval labelVal;
		JS_GetProperty(context, jsonObj,
				"label", &labelVal);
		jsval fontNameVal;
		JS_GetProperty(context, jsonObj,
				"fontName", &fontNameVal);
		jsval fontSizeVal;
		JS_GetProperty(context, jsonObj,
				"fontSize", &fontSizeVal);
		if(!JSVAL_IS_VOID(labelVal) && !JSVAL_IS_VOID(fontNameVal) && !JSVAL_IS_VOID(fontSizeVal)) {
			JSString *labelStr = JS_ValueToString(context, labelVal);
			char * label = JS_EncodeString(context, labelStr);
			JSString *fontNameStr = JS_ValueToString(context, fontNameVal);
			char * fontName = JS_EncodeString(context, fontNameStr);
			double fontSize = 0;
			JS_ValueToNumber(context,fontNameVal,&fontSize);
			CCLabelTTF *pLabelTTF = NULL;
			if(length == 5) {
				jsval dimensionsVal;
				jsval alignmentVal;
				JS_GetProperty(context, jsonObj,
						"dimensions", &dimensionsVal);
				JS_GetProperty(context, jsonObj,
						"alignment", &alignmentVal);
				if(!JSVAL_IS_VOID(dimensionsVal) && !JSVAL_IS_VOID(alignmentVal)) {
					CCSize *dimensions = static_cast<CCSize*>(JSVAL_TO_PRIVATE(dimensionsVal));
					int alignment = 0;
					JS_ConvertArguments(context,1,&alignmentVal,"i",&alignment);
					CCTextAlignment type = static_cast<CCTextAlignment>(alignment);
					pLabelTTF = CCLabelTTF::labelWithString(label,*dimensions,type, fontName,
							fontSize);
				}
			} else if(length == 3) {
				pLabelTTF = CCLabelTTF::labelWithString(label, fontName,
						fontSize);
			}
			if (pLabelTTF) {
				JSObject *newObj = JS_NewObject(context, &clz,
						obj, NULL);
				JS_SetPrivate(context,newObj, pLabelTTF);
				JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
			}
			JS_free(context,label);
			JS_free(context,fontName);
		}
	}
	return JS_TRUE;
}

JSObject * JsLabelTTFBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("setColor", SetColor, 0,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("setString", SetString, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("getString", GetString, 0,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
