#define TAG "JsSizeBinding"
#include "JsSizeBinding.h"
#include "Log.h"
JSClass JsSizeBinding::clz = { "Size", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, Finalize,
		JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsSizeBinding::obj = NULL;

JSBool JsSizeBinding::PropertyGet(JSContext *context, JSObject *obj, jsid id,
		jsval *val) {
	int propId = JSID_TO_INT(id);
	CCSize *pSize = static_cast<CCSize*> (JS_GetPrivate(context, obj));
	if (!pSize)
		return JS_FALSE;
	float result = 0;
	switch (propId) {
	case Width:
		result = pSize->width;
		break;
	case Height:
		result = pSize->height;
		break;
	default:
		break;
	}
	jsval resultVal;
	JS_NewNumberValue(context, result, &resultVal);
	JS_SET_RVAL(context, val, resultVal);
	return JS_TRUE;
}

JSBool JsSizeBinding::PropertySet(JSContext *context, JSObject *obj, jsid id,
		JSBool strict, jsval *val) {
	int propId = JSID_TO_INT(id);
	CCSize *pSize = static_cast<CCSize*> (JS_GetPrivate(context, obj));
	if (!pSize)
		return JS_FALSE;
	double data;
	JS_ValueToNumber(context, *val, &data);
	switch (propId) {
	case Width:
		pSize->width = data;
		break;
	case Height:
		pSize->height = data;
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool JsSizeBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval widthVal;
		JSBool isContainedWidth = JS_GetProperty(context, jsonObj, "width",
				&widthVal);
		jsval heightVal;
		JSBool isContainedHeight = JS_GetProperty(context, jsonObj, "height",
				&heightVal);
		if (isContainedWidth == JS_TRUE && isContainedHeight == JS_TRUE) {
			double w = 0;
			double h = 0;
			JS_ValueToNumber(context, widthVal, &w);
			JS_ValueToNumber(context, heightVal, &h);
			CCSize *pSize = new CCSize(w, h);
			if (pSize == NULL) {
				JS_ReportOutOfMemory(context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pSize);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			return JS_TRUE;
		}
	}
	return JS_TRUE;
}

void JsSizeBinding::Finalize(JSContext *context, JSObject *obj) {
	CCSize *pSize = static_cast<CCSize*> (JS_GetPrivate(context, obj));
	if (pSize) {
		delete pSize;
	}
}

JSObject * JsSizeBinding::BindingOnEngine(JSContext *context, JSObject *global,
		JSObject *parent) {
	JSPropertySpec properties[] = { { "width", Width, JSPROP_PERMANENT
			| JSPROP_SHARED, PropertyGet, PropertySet }, { "height", Height,
			JSPROP_PERMANENT | JSPROP_SHARED, PropertyGet, PropertySet }, { 0,
			0, 0, 0, 0 } };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, properties,
			NULL, NULL, NULL);
	return obj;
}

