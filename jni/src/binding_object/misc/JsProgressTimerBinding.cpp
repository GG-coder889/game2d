#define TAG "JsProgressTimerBinding"
#include "JsProgressTimerBinding.h"
JSClass JsProgressTimerBinding::clz = { "ProgressTimer", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsProgressTimerBinding::obj = NULL;

JS_CLASS_METHOD(JsProgressTimerBinding,SetPercentage) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCProgressTimer *pProgressTimer = static_cast<CCProgressTimer*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		double percent = 0;
		JS_ConvertArguments(context,argc,args,"d",&percent);
		pProgressTimer->setPercentage(percent);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsProgressTimerBinding,SetType) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCProgressTimer *pProgressTimer = static_cast<CCProgressTimer*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		int type = 0;
		JS_ConvertArguments(context,argc,args,"i",&type);
		CCProgressTimerType progressType = static_cast<CCProgressTimerType>(type);
		pProgressTimer->setType(progressType);
	}
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsProgressTimerBinding,RadialCCW) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(kCCProgressTimerTypeRadialCCW));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsProgressTimerBinding,RadialCW) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(kCCProgressTimerTypeRadialCW));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsProgressTimerBinding,HorizontalBarLR) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(kCCProgressTimerTypeHorizontalBarLR));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsProgressTimerBinding,HorizontalBarRL) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(kCCProgressTimerTypeHorizontalBarRL));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsProgressTimerBinding,HorizontalBarBT) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(kCCProgressTimerTypeVerticalBarBT));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(JsProgressTimerBinding,HorizontalBarTB) {
	JS_SET_RVAL(context, vp, INT_TO_JSVAL(kCCProgressTimerTypeVerticalBarTB));
	return JS_TRUE;
}

JS_CLASS_METHOD(JsProgressTimerBinding,Create) {
	if (argc == 1) {
		CCProgressTimer* pProgressTimer = NULL;
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval fileNameVal;
		JS_GetProperty(context, jsonObj,
				"fileName", &fileNameVal);
		jsval textureVal;
		JS_GetProperty(context, jsonObj,
				"texture", &textureVal);
		if (!JSVAL_IS_VOID(fileNameVal)) {
			JSString *fileStr = JSVAL_TO_STRING(fileNameVal);
			char *fileName = JS_EncodeString(context,fileStr);
			pProgressTimer = CCProgressTimer::progressWithFile(fileName);
			JS_free(context,fileName);
		} else if(!JSVAL_IS_VOID(textureVal)) {
			JSObject *obj = JSVAL_TO_OBJECT(textureVal);
			CCTexture2D *texture = static_cast<CCTexture2D*>(JS_GetPrivate(context,obj));
			pProgressTimer = CCProgressTimer::progressWithTexture(texture);
		}

		if(pProgressTimer) {
			JSObject *newObj = JS_NewObject(context, &clz, obj,
					NULL);
			JS_SetPrivate(context, newObj, pProgressTimer);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * JsProgressTimerBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "setPercentage", SetPercentage, 1,
			JSPROP_PERMANENT | JSPROP_SHARED }, { "setType", SetType, 1,
			JSPROP_PERMANENT | JSPROP_SHARED }, JS_FS_END };
	JSPropertySpec staticProperties[] = { { "radialCCW", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetRadialCCW, JS_StrictPropertyStub }, {
			"horizontalBarTB", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetHorizontalBarTB, JS_StrictPropertyStub }, { "radialCW", 0,
			JSPROP_PERMANENT | JSPROP_SHARED, GetRadialCW,
			JS_StrictPropertyStub }, { "horizontalBarBT", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetHorizontalBarBT, JS_StrictPropertyStub }, {
			"horizontalBarLR", 0, JSPROP_PERMANENT | JSPROP_SHARED,
			GetHorizontalBarLR, JS_StrictPropertyStub }, { "horizontalBarRL",
			0, JSPROP_PERMANENT | JSPROP_SHARED, GetHorizontalBarRL,
			JS_StrictPropertyStub }, { 0 } };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			staticProperties, NULL);
	return obj;
}
