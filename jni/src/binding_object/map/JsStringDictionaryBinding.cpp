#define TAG "JsStringDictionaryBinding"
#include "JsStringDictionaryBinding.h"

JSClass JsStringDictionaryBinding::clz = { "StringDictionary",
		JSCLASS_HAS_PRIVATE, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsStringDictionaryBinding::obj = NULL;

JS_CLASS_METHOD(JsStringDictionaryBinding,GetIntValue) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCStringToStringDictionary *pDict = static_cast<CCStringToStringDictionary*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSString *keyStr = JS_ValueToString(context,args[0]);
		char *pKey = JS_EncodeString(context,keyStr);
		int result = pDict->objectForKey(pKey)->toInt();
		JS_SET_RVAL(context, vp, INT_TO_JSVAL(result));
		JS_free(context,pKey);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsStringDictionaryBinding,GetStringValue) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCStringToStringDictionary *pDict = static_cast<CCStringToStringDictionary*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSString *keyStr = JS_ValueToString(context,args[0]);
		char *pKey = JS_EncodeString(context,keyStr);
		std::string result = pDict->objectForKey(pKey)->m_sString;
		JSString * resultStr = JS_NewStringCopyZ(context, result.c_str());
		JS_SET_RVAL(context, vp, STRING_TO_JSVAL(resultStr));
		JS_free(context,pKey);
	}
	return JS_TRUE;
}

JSBool JsStringDictionaryBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	return JS_FALSE;
}

JSObject * JsStringDictionaryBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "getIntValue", GetIntValue, 1,
			JSPROP_PERMANENT | JSPROP_SHARED }, { "getStringValue",
			GetStringValue, 1, JSPROP_PERMANENT | JSPROP_SHARED }, JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

