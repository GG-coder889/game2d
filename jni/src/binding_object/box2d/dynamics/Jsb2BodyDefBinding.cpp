#define TAG "Jsb2BodyDefBinding"
#include "Jsb2BodyDefBinding.h"
#include "Log.h"
JSClass Jsb2BodyDefBinding::clz = { "b2BodyDef", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2BodyDefBinding::obj = NULL;

JS_CLASS_METHOD(Jsb2BodyDefBinding,SetPosition) {
	if (argc == 2) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2BodyDef *pBodyDef = static_cast<b2BodyDef*>(JS_GetPrivate(context,thisObj));
		double x = 0;
		double y = 0;
		JS_ConvertArguments(context,argc,args,"dd",&x,&y);
		pBodyDef->position.Set(x, y);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(Jsb2BodyDefBinding,SetUserData) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2BodyDef *pBodyDef = static_cast<b2BodyDef*>(JS_GetPrivate(context,thisObj));
		pBodyDef->userData = &(args[0]);
	}
	return JS_TRUE;
}

JS_CLASS_SET_PROPERTY(Jsb2BodyDefBinding,Type) {
	b2BodyDef *pBodyDef = static_cast<b2BodyDef*> (JS_GetPrivate(context,obj));
	int type = 0;
	JS_ConvertArguments(context,1,vp,"i",&type);
	pBodyDef->type = static_cast<b2BodyType> (type);
	return JS_TRUE;
}
JS_CLASS_GET_PROPERTY(Jsb2BodyDefBinding,Type) {
	b2BodyDef *pBodyDef = static_cast<b2BodyDef*> (JS_GetPrivate(context,obj));
	JS_SET_RVAL(context,vp,INT_TO_JSVAL(pBodyDef->type));
	return JS_TRUE;
}

void Jsb2BodyDefBinding::Finalize(JSContext *context, JSObject *obj) {
	if (b2BodyDef* pBodyDef = static_cast<b2BodyDef*>(JS_GetPrivate(context,obj))) {
		delete pBodyDef;
	}
}

JS_CLASS_METHOD( Jsb2BodyDefBinding,Create) {
	if (argc == 0) {
		b2BodyDef *pBodyDef = new b2BodyDef();
		if(pBodyDef) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pBodyDef);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * Jsb2BodyDefBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("setUserData", SetUserData, 1,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("setPosition",
			SetPosition, 1, JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	JSPropertySpec properties[] = { { "type", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetType, SetType }, { 0 } };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, properties,
			methods, NULL, NULL);
	return obj;
}
