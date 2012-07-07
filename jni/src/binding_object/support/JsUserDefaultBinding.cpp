#define TAG "JsUserDefaultBinding"
#include "JsUserDefaultBinding.h"
#include "Log.h"
#include "V8Convert.h"
#include "V8Engine.h"

JS_CLASS_METHOD(JsUserDefaultBinding, GetBoolForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD(JsUserDefaultBinding, GetIntegerForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD( JsUserDefaultBinding,GetFloatForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD(JsUserDefaultBinding, GetDoubleForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD(JsUserDefaultBinding, GetStringForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD( JsUserDefaultBinding,SetBoolForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD( JsUserDefaultBinding,SetIntegerForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD( JsUserDefaultBinding,SetFloatForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD(JsUserDefaultBinding, SetDoubleForKey) {
	return v8::Undefined();
}
JS_CLASS_METHOD( JsUserDefaultBinding,SetStringForKey) {
	return v8::Undefined();
}

void JsUserDefaultBinding::BindingOnV8(Persistent<Context> context) {
	Handle < Object > obj = V8Engine::ExposeGlobalObject(context,
			v8::String::New("UserDefault"), v8::ReadOnly);
	ExposeMethod( obj);
}

void JsUserDefaultBinding::ExposeMethod(Handle<Object> obj) {

	V8Engine::ExposeMethod(obj, String::New("setStringForKey"),
			InvocationCallback(SetStringForKey));
	V8Engine::ExposeMethod(obj, String::New("setDoubleForKey"),
			InvocationCallback(SetDoubleForKey));
	V8Engine::ExposeMethod(obj, String::New("setFloatForKey"),
			InvocationCallback(SetFloatForKey));
	V8Engine::ExposeMethod(obj, String::New("setIntegerForKey"),
			InvocationCallback(SetIntegerForKey));
	V8Engine::ExposeMethod(obj, String::New("setBoolForKey"),
			InvocationCallback(SetBoolForKey));
	V8Engine::ExposeMethod(obj, String::New("getStringForKey"),
			InvocationCallback(GetStringForKey));
	V8Engine::ExposeMethod(obj, String::New("getDoubleForKey"),
			InvocationCallback(GetDoubleForKey));
	V8Engine::ExposeMethod(obj, String::New("getFloatForKey"),
			InvocationCallback(GetFloatForKey));
	V8Engine::ExposeMethod(obj, String::New("getIntegerForKey"),
			InvocationCallback(GetIntegerForKey));
	V8Engine::ExposeMethod(obj, String::New("getBoolForKey"),
			InvocationCallback(GetBoolForKey));
}
