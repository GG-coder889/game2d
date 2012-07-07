#define TAG "Jsb2PolygonShapeBinding"
#include "Jsb2PolygonShapeBinding.h"
#include "Log.h"

JSClass Jsb2PolygonShapeBinding::clz = { "b2PolygonShape", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2PolygonShapeBinding::obj = NULL;

JS_CLASS_METHOD( Jsb2PolygonShapeBinding,Set) {
	/*if (argc == 1) {
	 b2PolygonShape *pShape = LOAD_PTR(0,b2PolygonShape*);
	 if (args[0]->IsArray()) {
	 Handle < Array > array = Handle<Array>::Cast(args[0]);
	 int arrayLen = array->Length();
	 b2Vec2 vertices[arrayLen];
	 float x, y;
	 Handle < Array > subArray;
	 for (int i = 0; i < arrayLen; i++) {
	 subArray = Handle<Array>::Cast(array->Get(v8::Int32::New(i)));
	 x = subArray->Get(v8::Int32::New(0))->NumberValue();
	 y = subArray->Get(v8::Int32::New(1))->NumberValue();
	 vertices[i].Set(x, y);
	 }
	 pShape->Set(vertices, arrayLen);
	 }
	 }*/
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2PolygonShapeBinding,SetAsBox) {
	if (argc >= 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2PolygonShape *pShape = static_cast<b2PolygonShape*>(JS_GetPrivate(context,thisObj));
		double hx = 0;
		double hy = 0;
		jsval *args = JS_ARGV(context, vp);
		if (argc == 5) {
			double vectorX = 0;
			double vectorY = 0;
			double angle = 0;
			JS_ConvertArguments(context,argc,args,"ddddd",&hx,&hy,&vectorX,&vectorY,&angle);
			pShape->SetAsBox(hx, hy, b2Vec2(vectorX, vectorY), angle);
		} else {
			JS_ConvertArguments(context,argc,args,"dd",&hx,&hy);
			pShape->SetAsBox(hx, hy);
		}

	}
	return JS_TRUE;
}

void Jsb2PolygonShapeBinding::Finalize(JSContext *context, JSObject *obj) {
	if (b2PolygonShape* pShape = static_cast<b2PolygonShape*>(JS_GetPrivate(context,obj))) {
		delete pShape;
	}
}

JS_CLASS_METHOD( Jsb2PolygonShapeBinding,Create) {
	if (argc == 0) {
		b2PolygonShape *pShape = new b2PolygonShape();
		if(pShape) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pShape);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * Jsb2PolygonShapeBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("setAsBox", SetAsBox, 2,
			JSPROP_PERMANENT | JSPROP_SHARED), { 0 } };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
