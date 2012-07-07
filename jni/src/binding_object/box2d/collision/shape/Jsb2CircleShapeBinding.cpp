#define TAG "Jsb2CircleShapeBinding"
#include "Jsb2CircleShapeBinding.h"
#include "Log.h"

JSClass Jsb2CircleShapeBinding::clz = { "b2CircleShape", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2CircleShapeBinding::obj = NULL;

JS_CLASS_METHOD(Jsb2CircleShapeBinding,SetRadius) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context, vp);
		b2CircleShape *pShape = static_cast<b2CircleShape*> (JS_GetPrivate(
						context, thisObj));
		double radius = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"d",&radius);
		pShape->m_radius = radius;
	}
	return JS_TRUE;
}

void Jsb2CircleShapeBinding::Finalize(JSContext *context, JSObject *obj) {
	if (b2CircleShape* pShape = static_cast<b2CircleShape*>(JS_GetPrivate(context,obj))) {
		delete pShape;
	}
}

JS_CLASS_METHOD( Jsb2CircleShapeBinding,Create) {
	if (argc == 0) {
		b2CircleShape *pShape = new b2CircleShape();
		if(pShape) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pShape);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * Jsb2CircleShapeBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("setRadius", SetRadius, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), { 0 } };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
