#define TAG "Jsb2WorldBinding"
#include "Jsb2WorldBinding.h"
#include "Jsb2BodyBinding.h"
#include "Log.h"
#include "JsGLESDebugDraw.h"

JSClass Jsb2WorldBinding::clz = { "b2World", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, Finalize, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *Jsb2WorldBinding::obj = NULL;

JS_CLASS_METHOD( Jsb2WorldBinding,CreateBody) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSObject *bodyDefObj = NULL;
		JS_ConvertArguments(context,argc,args,"o",&bodyDefObj);
		b2BodyDef * pBodyDef = static_cast<b2BodyDef*>(JS_GetPrivate(context,bodyDefObj));
		b2Body *pBody = pWorld->CreateBody(pBodyDef);
		if (pBody) {
			JSObject *newObj = JS_NewObject(context, &Jsb2BodyBinding::clz, Jsb2BodyBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pBody);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,SetDebugDraw) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSObject *drawObj = NULL;
		JS_ConvertArguments(context,argc,args,"o",&drawObj);
		JsGLESDebugDraw * pDebugDraw =static_cast<JsGLESDebugDraw*>( JS_GetPrivate(context,drawObj));
		pWorld->SetDebugDraw(pDebugDraw);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,DrawDebugData) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		pWorld->DrawDebugData();
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,Step) {
	if (argc == 3) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		double dt = 0;
		int velocityIterations = 0;
		int positionIterations = 0;
		JS_ConvertArguments(context,argc,args,"dii",&dt,&velocityIterations,&positionIterations);
		pWorld->Step(dt, velocityIterations, positionIterations);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,SetAllowSleeping) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSBool doSleep = 0;
		JS_ConvertArguments(context,argc,args,"b",&doSleep);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		pWorld->SetAllowSleeping(doSleep);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,SetContinuousPhysics) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSBool enable = 0;
		JS_ConvertArguments(context,argc,args,"b",&enable);
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		pWorld->SetContinuousPhysics(enable);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,GetBodyList) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		b2Body *pBody = pWorld->GetBodyList();
		if (pBody) {
			JSObject *newObj = JS_NewObject(context, &Jsb2BodyBinding::clz, Jsb2BodyBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pBody);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD( Jsb2WorldBinding,GetBodyCount) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		b2World *pWorld = static_cast<b2World*>(JS_GetPrivate(context,thisObj));
		JS_SET_RVAL(cx, vp, INT_TO_JSVAL(pWorld->GetBodyCount()));
	}
	return JS_TRUE;
}

void Jsb2WorldBinding::Finalize(JSContext *context, JSObject *obj) {
	if (b2World* pWorld = static_cast<b2World*>(JS_GetPrivate(context,obj))) {
		delete pWorld;
	}
}

JS_CLASS_METHOD( Jsb2WorldBinding,Create) {
	if (argc == 2) {
		jsval *args = JS_ARGV(context, vp);
		double x = 0;
		double y = 0;
		JS_ConvertArguments(context,argc,args,"dd",&x,&y);
		b2Vec2 gravity = b2Vec2(x, y);
		b2World *pWorld = new b2World(gravity);
		if (pWorld) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pWorld);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JSObject * Jsb2WorldBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("drawDebugData", DrawDebugData, 0,
			JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("setDebugDraw",
			SetDebugDraw, 1, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
			"createBody", CreateBody, 1, JSPROP_PERMANENT | JSPROP_SHARED),
			JS_FN("step", Step, 3, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
					"getBodyCount", GetBodyCount, 0,
					JSPROP_PERMANENT | JSPROP_SHARED), JS_FN("getBodyList",
					GetBodyList, 0, JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
					"setContinuousPhysics", SetContinuousPhysics, 1,
					JSPROP_PERMANENT | JSPROP_SHARED), JS_FN(
					"setAllowSleeping", SetAllowSleeping, 1,
					JSPROP_PERMANENT | JSPROP_SHARED), JS_FS_END };
	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}

