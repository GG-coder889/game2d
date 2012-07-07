#define TAG "Jsb2FixtureDefBinding"
#include "Jsb2FixtureDefBinding.h"
#include "Log.h"

JSClass Jsb2FixtureDefBinding::clz = { "b2FixtureDef", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2FixtureDefBinding::obj = NULL;

JS_CLASS_METHOD( Jsb2FixtureDefBinding,SetShape) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2FixtureDef *pFixtureDef = static_cast<b2FixtureDef*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSObject* shapeObj = NULL;
		JS_ConvertArguments(context,argc,args,"o",&shapeObj);
		b2Shape *shape = static_cast<b2Shape*>(JS_GetPrivate(context,shapeObj));
		pFixtureDef->shape = shape;
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2FixtureDefBinding,SetDensity) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2FixtureDef *pFixtureDef = static_cast<b2FixtureDef*>(JS_GetPrivate(context,thisObj));
		double density = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"d",&density);
		pFixtureDef->density = density;
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2FixtureDefBinding,SetFriction) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2FixtureDef *pFixtureDef = static_cast<b2FixtureDef*>(JS_GetPrivate(context,thisObj));
		double friction = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"d",&friction);
		pFixtureDef->friction = friction;
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2FixtureDefBinding,SetRestitution) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2FixtureDef *pFixtureDef = static_cast<b2FixtureDef*>(JS_GetPrivate(context,thisObj));
		double restitution = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context,argc,args,"d",&restitution);
		pFixtureDef->restitution = restitution;
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2FixtureDefBinding,SetUserData) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2FixtureDef *pFixtureDef = static_cast<b2FixtureDef*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		pFixtureDef->userData = &(args[0]);
	}
	return JS_TRUE;
}

void Jsb2FixtureDefBinding::Finalize(JSContext *context, JSObject *obj) {
	if (b2FixtureDef *pDef = static_cast<b2FixtureDef*>(JS_GetPrivate(context,obj))) {
		delete pDef;
	}
}

JS_CLASS_METHOD( Jsb2FixtureDefBinding,Create) {
	if (argc == 0) {
		b2FixtureDef *pDef = new b2FixtureDef();
		if (pDef) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pDef);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * Jsb2FixtureDefBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("setFriction", SetFriction, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("setDensity", SetDensity,
			1, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("setShape", SetShape,
			1, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("setUserData",
			SetUserData, 1, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
			"setRestitution", SetRestitution, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

