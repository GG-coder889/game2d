#define TAG "Jsb2EdgeShapeBinding"
#include "Jsb2EdgeShapeBinding.h"
#include "Log.h"

JSClass Jsb2EdgeShapeBinding::clz = { "b2EdgeShape", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2EdgeShapeBinding::obj = NULL;

JS_CLASS_METHOD( Jsb2EdgeShapeBinding,Set) {
	if (argc == 4) {
		JSObject *thisObj = JS_THIS_OBJECT(context, vp);
		b2EdgeShape *pShape = static_cast<b2EdgeShape*> (JS_GetPrivate(context,
						thisObj));
		float x1 = 0;
		float y1 = 0;
		float x2 = 0;
		float y2 = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"dddd",&x1,&y1,&x2,&y2);
		pShape->Set(b2Vec2(x1, y1), b2Vec2(x2, y2));
	}
	return JS_TRUE;
}

void Jsb2EdgeShapeBinding::Finalize(JSContext *context, JSObject *obj) {
	if (b2EdgeShape* pShape = static_cast<b2EdgeShape*>(JS_GetPrivate(context,obj))) {
		delete pShape;
	}
}

JS_CLASS_METHOD( Jsb2EdgeShapeBinding,Create) {
	if (argc == 0) {
		b2EdgeShape *pShape = new b2EdgeShape();
		if(pShape) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pShape);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * Jsb2EdgeShapeBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("set", Set, 4,
			JSPROP_PERMANENT | JSPROP_SHARED), { 0 } };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

