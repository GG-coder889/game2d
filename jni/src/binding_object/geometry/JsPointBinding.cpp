#define TAG "JsPointBinding"
#include "JsPointBinding.h"
#include "Log.h"
JSClass JsPointBinding::clz = { "Point", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, Finalize,
		JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsPointBinding::obj = NULL;

JSBool JsPointBinding::PropertyGet(JSContext *context, JSObject *obj, jsid id,
		jsval *val) {
	int propId = JSID_TO_INT(id);
	CCPoint *pPoint = static_cast<CCPoint*> (JS_GetPrivate(context, obj));
	if (!pPoint)
		return JS_FALSE;
	float result = 0;
	switch (propId) {
	case X:
		result = pPoint->x;
		break;
	case Y:
		result = pPoint->y;
		break;
	default:
		break;
	}
	jsval resultVal;
	JS_NewNumberValue(context, result, &resultVal);
	JS_SET_RVAL(context, val, resultVal);
	return JS_TRUE;
}

JSBool JsPointBinding::PropertySet(JSContext *context, JSObject *obj, jsid id,
		JSBool strict, jsval *val) {
	int propId = JSID_TO_INT(id);
	CCPoint *pPoint = static_cast<CCPoint*> (JS_GetPrivate(context, obj));
	if (!pPoint)
		return JS_FALSE;
	double data;
	JS_ValueToNumber(context, *val, &data);
	switch (propId) {
	case X:
		pPoint->x = data;
		break;
	case Y:
		pPoint->y = data;
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( JsPointBinding,ToAngle) {
	if(argc == 1) {
		JSObject *objA;
		JS_ConvertArguments(context, argc, JS_ARGV(cx, vp), "o", &objA);
		CCPoint *p1 = static_cast<CCPoint*>(JS_GetPrivate(context,objA));
		CGFloat result = ccpToAngle(*p1);
		JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(result));
	}
	return JS_TRUE;

}
JS_CLASS_METHOD(JsPointBinding, Sub) {
	if(argc == 2) {
		JSObject *objA;
		JSObject *objB;
		JS_ConvertArguments(context, argc, JS_ARGV(cx, vp), "oo", &objA,
				&objB);
		CCPoint *p1 = static_cast<CCPoint*>(JS_GetPrivate(context,objA));
		CCPoint *p2 = static_cast<CCPoint*>(JS_GetPrivate(context,objB));
		CCPoint p = ccpSub(*p1,*p2);
		CCPoint *pPoint = new CCPoint(p.x,p.y);
		if(pPoint) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pPoint);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsPointBinding, Distance) {
	if(argc == 2) {
		JSObject *objA;
		JSObject *objB;
		JS_ConvertArguments(context, argc, JS_ARGV(cx, vp), "oo", &objA,
				&objB);
		CCPoint *p1 = static_cast<CCPoint*>(JS_GetPrivate(context,objA));
		CCPoint *p2 = static_cast<CCPoint*>(JS_GetPrivate(context,objB));
		CGFloat result = ccpDistance(*p1,*p2);
		JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(result));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsPointBinding, Normalize) {
	if(argc == 1) {
		JSObject *objA;
		JS_ConvertArguments(context, argc, JS_ARGV(cx, vp), "o", &objA);
		CCPoint *p1 = static_cast<CCPoint*>(JS_GetPrivate(context,objA));
		CCPoint p = ccpNormalize(*p1);
		CCPoint *pPoint = new CCPoint(p.x,p.y);
		if(pPoint) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pPoint);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsPointBinding, Add) {
	if(argc == 2) {
		JSObject *objA;
		JSObject *objB;
		JS_ConvertArguments(context, argc, JS_ARGV(cx, vp), "oo", &objA,
				&objB);
		CCPoint *p1 = static_cast<CCPoint*>(JS_GetPrivate(context,objA));
		CCPoint *p2 = static_cast<CCPoint*>(JS_GetPrivate(context,objB));
		CCPoint p = ccpAdd(*p1,*p2);
		CCPoint *pPoint = new CCPoint(p.x,p.y);
		if(pPoint) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pPoint);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsPointBinding,Mult) {
	if(argc == 2) {
		JSObject *objA;
		double s = 0;
		JS_ConvertArguments(context, argc, JS_ARGV(cx, vp), "od", &objA,
				&s);
		CCPoint *p1 = static_cast<CCPoint*>(JS_GetPrivate(context,objA));
		CCPoint p = ccpMult(*p1,s);
		CCPoint *pPoint = new CCPoint(p.x,p.y);
		if(pPoint) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pPoint);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSBool JsPointBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval xVal;
		JSBool isContainedX = JS_GetProperty(context, jsonObj, "x", &xVal);
		jsval yVal;
		JSBool isContainedY = JS_GetProperty(context, jsonObj, "y", &yVal);
		if (isContainedX == JS_TRUE && isContainedY == JS_TRUE) {
			double x = 0;
			double y = 0;
			JS_ValueToNumber(context, xVal, &x);
			JS_ValueToNumber(context, yVal, &y);
			CCPoint *pPoint = new CCPoint(x, y);

			if (pPoint == NULL) {
				JS_ReportOutOfMemory(context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pPoint);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

void JsPointBinding::Finalize(JSContext *context, JSObject *obj) {
	CCPoint *pPoint = static_cast<CCPoint*> (JS_GetPrivate(context, obj));
	if (pPoint) {
		delete pPoint;
	}
}

JSObject * JsPointBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {

	JSFunctionSpec staticMethods[] = { JS_FN("toAngle", ToAngle, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("normalize", Normalize, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("sub", Sub, 2,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("add", Add, 2,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("mult", Mult, 2,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("distance", Distance, 2,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };

	JSPropertySpec properties[] = { { "x", X, JSPROP_PERMANENT | JSPROP_SHARED,
			PropertyGet, PropertySet }, { "y", Y, JSPROP_PERMANENT
			| JSPROP_SHARED, PropertyGet, PropertySet }, { 0 } };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, properties,
			NULL, NULL, staticMethods);

	return obj;
}

