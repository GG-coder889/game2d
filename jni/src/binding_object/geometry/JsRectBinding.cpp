#define TAG "JsRectBinding"
#include "JsRectBinding.h"
#include "JsPointBinding.h"
#include "JsSizeBinding.h"
#include "Log.h"
JSClass JsRectBinding::clz = { "Rect", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, Finalize,
		JSCLASS_NO_OPTIONAL_MEMBERS };
;
JSObject *JsRectBinding::obj = NULL;

JSBool JsRectBinding::RectContainsPoint(JSContext *context, uint32_t argc,
		jsval *vp) {
	if (argc == 2) {
		jsval *args = JS_ARGV(context, vp);
		jsval rectVal = args[0];
		jsval pointVal = args[1];
		if (JSVAL_IS_OBJECT(rectVal) && JSVAL_IS_OBJECT(pointVal)) {
			JSObject *rectObj;
			JSObject *pointObj;
			JS_ConvertArguments(context, 2, JS_ARGV(cx, vp), "oo", &rectObj,
					&pointObj);
			if (rectObj && pointObj) {
				CCRect* pRect = static_cast<CCRect*> (JS_GetPrivate(context,
						rectObj));
				CCPoint* pPoint = static_cast<CCPoint*> (JS_GetPrivate(context,
						pointObj));
				if (pRect && pPoint) {
					bool ret = CCRect::CCRectContainsPoint(*pRect, *pPoint);
					JS_SET_RVAL(context, vp, BOOLEAN_TO_JSVAL(ret));
				}
			}
		}
	}
	return JS_TRUE;
}
JSBool JsRectBinding::RectIntersectsRect(JSContext *context, uint32_t argc,
		jsval *vp) {
	if (argc == 2) {
		JSObject *rectObjA;
		JSObject *rectObjB;
		JS_ConvertArguments(context, 2, JS_ARGV(cx, vp), "oo", &rectObjA,
				&rectObjB);
		CCRect* pRectA =
				static_cast<CCRect*> (JS_GetPrivate(context, rectObjA));
		CCRect* pRectB =
				static_cast<CCRect*> (JS_GetPrivate(context, rectObjB));
		bool ret = CCRect::CCRectIntersectsRect(*pRectA, *pRectB);
		JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
		return JS_TRUE;
	}
	JS_SET_RVAL(cx, vp, JSVAL_TRUE);
	return JS_TRUE;
}

JSBool JsRectBinding::PropertyGet(JSContext *context, JSObject *obj, jsid id,
		jsval *val) {
	int propId = JSID_TO_INT(id);
	CCRect *pRect = static_cast<CCRect*> (JS_GetPrivate(context, obj));
	if (!pRect)
		return JS_FALSE;
	switch (propId) {
	case Origin:
		do {
			JSObject *pointObj = JS_NewObject(context, &JsPointBinding::clz,
					JsPointBinding::obj, NULL);
			CCPoint *pPoint = new CCPoint(pRect->origin.x, pRect->origin.y);
			JS_SetPrivate(context, pointObj, pPoint);
			JS_SET_RVAL(context, val, OBJECT_TO_JSVAL(pointObj));
		} while (0);
		break;
	case Size:
		do {
			JSObject *sizeObj = JS_NewObject(context, &JsSizeBinding::clz,
					JsSizeBinding::obj, NULL);
			CCSize *pSize = new CCSize(pRect->size.width, pRect->size.height);
			JS_SetPrivate(context, sizeObj, pSize);
			JS_SET_RVAL(context, val, OBJECT_TO_JSVAL(sizeObj));
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool JsRectBinding::PropertySet(JSContext *context, JSObject *obj, jsid id,
		JSBool strict, jsval *val) {
	int propId = JSID_TO_INT(id);
	CCRect *pRect = static_cast<CCRect*> (JS_GetPrivate(context, obj));
	if (!pRect)
		return JS_FALSE;
	switch (propId) {
	case Origin:
		do {
			JSObject *pointObj;
			JS_ValueToObject(context, *val, &pointObj);
			CCPoint *pPoint = static_cast<CCPoint*> (JS_GetPrivate(context,
					pointObj));
			pRect->origin = *pPoint;
		} while (0);
		break;
	case Size:
		do {
			JSObject *sizeObj;
			JS_ValueToObject(context, *val, &sizeObj);
			CCSize *pSize = static_cast<CCSize*> (JS_GetPrivate(context,
					sizeObj));
			pRect->size = *pSize;
		} while (0);
		break;
	default:
		break;
	}
	return JS_TRUE;
}

JSBool JsRectBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *jsonObj;
		JS_ValueToObject(context, args[0], &jsonObj);
		jsval xVal;
		JSBool isContainedX = JS_GetProperty(context, jsonObj, "x", &xVal);
		jsval yVal;
		JSBool isContainedY = JS_GetProperty(context, jsonObj, "y", &yVal);
		jsval widthVal;
		JSBool isContainedWidth = JS_GetProperty(context, jsonObj, "width",
				&widthVal);
		jsval heightVal;
		JSBool isContainedHeight = JS_GetProperty(context, jsonObj, "height",
				&heightVal);
		if (isContainedX == JS_TRUE && isContainedY == JS_TRUE
				&& isContainedWidth == JS_TRUE && isContainedHeight == JS_TRUE) {
			double x = 0;
			double y = 0;
			double w = 0;
			double h = 0;
			JS_ValueToNumber(context, xVal, &x);
			JS_ValueToNumber(context, yVal, &y);
			JS_ValueToNumber(context, widthVal, &w);
			JS_ValueToNumber(context, heightVal, &h);
			CCRect *pRect = new CCRect(x, y, w, h);
			if (pRect == NULL) {
				JS_ReportOutOfMemory(context);
				return JS_FALSE;
			}
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pRect);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
			return JS_TRUE;
		}
	}
	return JS_TRUE;
}

void JsRectBinding::Finalize(JSContext *context, JSObject *obj) {
	CCRect *pRect = static_cast<CCRect*> (JS_GetPrivate(context, obj));
	if (pRect) {
		delete pRect;
	}
}

JSObject * JsRectBinding::BindingOnEngine(JSContext *context, JSObject *global,
		JSObject *parent) {
	JSPropertySpec properties[] = { { "origin", Origin, JSPROP_PERMANENT
			| JSPROP_SHARED, PropertyGet, PropertySet }, { "size", Size,
			JSPROP_PERMANENT | JSPROP_SHARED, PropertyGet, PropertySet }, { 0,
			0, 0, 0, 0 } };

	JSFunctionSpec staticMethods[] = { JS_FN("rectContainsPoint",
			RectContainsPoint, 2, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
			"rectIntersectsRect", RectIntersectsRect, 2,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, properties,
			NULL, NULL, staticMethods);
	return obj;
}

