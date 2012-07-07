#define TAG "JsTouchBinding"
#include "JsTouchBinding.h"
#include "JsPointBinding.h"

JSClass JsTouchBinding::clz = { "Touch", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JSObject *JsTouchBinding::obj = NULL;

JS_CLASS_METHOD(JsTouchBinding, Location) {
	if(argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTouch * pTouch =static_cast<CCTouch*> (JS_GetPrivate(context,thisObj));
		CCPoint location = pTouch->locationInView(0);
		location = CCDirector::sharedDirector()->convertToGL(location);
		CCPoint *point = new CCPoint(location.x,location.y);
		JSObject *newObj = JS_NewObject(context, &JsPointBinding::clz, JsPointBinding::obj,
				NULL);
		JS_SetPrivate(context, newObj, point);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsTouchBinding, PreviousLocation) {
	if(argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTouch * pTouch =static_cast<CCTouch*> (JS_GetPrivate(context,thisObj));
		CCPoint location = pTouch->previousLocationInView(0);
		location = CCDirector::sharedDirector()->convertToGL(location);
		CCPoint *point = new CCPoint(location.x,location.y);
		JSObject *newObj = JS_NewObject(context, &JsPointBinding::clz, JsPointBinding::obj,
				NULL);
		JS_SetPrivate(context, newObj, point);
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JSObject * JsTouchBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "location", Location, 0, JSPROP_PERMANENT
			| JSPROP_SHARED }, { "previousLocation", PreviousLocation, 0,
			JSPROP_PERMANENT | JSPROP_SHARED }, JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, NULL, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
