#define TAG "Jsb2BodyBinding"
#include "Jsb2BodyBinding.h"
#include "JsPointBinding.h"
#include "Log.h"

JSClass Jsb2BodyBinding::clz = { "b2Body", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2BodyBinding::obj = NULL;

JS_CLASS_METHOD( Jsb2BodyBinding,CreateFixture) {
	if (argc >= 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2Body *pBody = static_cast<b2Body*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		if (argc == 1) {
			JSObject *fixtureObj = NULL;
			JS_ConvertArguments(context,argc,args,"o",&fixtureObj);
			b2FixtureDef *fixture = static_cast<b2FixtureDef*>(JS_GetPrivate(context,fixtureObj));
			pBody->CreateFixture(fixture);
		} else {
			JSObject *shapeObj = NULL;
			int density = 0;
			JS_ConvertArguments(context,argc,args,"oi",&shapeObj,&density);
			b2Shape *shape = static_cast<b2Shape*>(JS_GetPrivate(context,shapeObj));
			pBody->CreateFixture(shape, density);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2BodyBinding,GetNext) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2Body *pBody = static_cast<b2Body*>(JS_GetPrivate(context,thisObj));
		b2Body *pNextBody = pBody->GetNext();
		if(pNextBody) {
			JSObject *newObj = JS_NewObject(context, &Jsb2BodyBinding::clz, Jsb2BodyBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pNextBody);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JS_SET_RVAL(context, vp, JSVAL_NULL);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2BodyBinding,GetUserData) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2Body *pBody = static_cast<b2Body*>(JS_GetPrivate(context,thisObj));
		jsval *data = static_cast<jsval*>(pBody->GetUserData());
		JS_SET_RVAL(context,vp,*data);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2BodyBinding,GetPosition) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2Body *pBody = static_cast<b2Body*>(JS_GetPrivate(context,thisObj));
		CCPoint *p = new CCPoint(pBody->GetPosition().x,pBody->GetPosition().y);
		if(p) {
			JSObject *newObj = JS_NewObject(context, &JsPointBinding::clz, JsPointBinding::obj, NULL);
			JS_SetPrivate(context, newObj, p);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(Jsb2BodyBinding,DynamicBody) {

	JS_SET_RVAL(context,vp,INT_TO_JSVAL(b2_dynamicBody));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(Jsb2BodyBinding,StaticBody) {
	JS_SET_RVAL(context,vp,INT_TO_JSVAL(b2_staticBody));
	return JS_TRUE;
}

JS_CLASS_GET_PROPERTY(Jsb2BodyBinding,KinematicBody) {
	JS_SET_RVAL(context,vp,INT_TO_JSVAL(b2_kinematicBody));
	return JS_TRUE;
}
JS_CLASS_METHOD( Jsb2BodyBinding,GetAngle) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2Body *pBody = static_cast<b2Body*>(JS_GetPrivate(context,thisObj));
		JS_SET_RVAL(cx, vp, DOUBLE_TO_JSVAL(pBody->GetAngle()));
	}
	return JS_TRUE;
}

JSObject * Jsb2BodyBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("getAngle", GetAngle, 0,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("getPosition",
			GetPosition, 0, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
			"getUserData", GetUserData, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("getNext", GetNext, 0, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("createFixture", CreateFixture, 1,
					JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	JSPropertySpec staticProperties[] = { { "dynamicBody", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetDynamicBody, JS_StrictPropertyStub }, {
			"staticBody", 0, JSPROP_PERMANENT | JSPROP_SHARED, GetStaticBody,
			JS_StrictPropertyStub }, { "kinematicBody", 0, JSPROP_PERMANENT
			| JSPROP_SHARED, GetKinematicBody, JS_StrictPropertyStub }, { 0 } };
	obj = JS_InitClass(context, global, parent, &clz, NULL, 0, NULL, methods,
			staticProperties, NULL);

	return obj;
}

