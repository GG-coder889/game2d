#define TAG "JsHttpRequestBinding"
#include "JsHttpRequestBinding.h"
#include "JsHttpRequest.h"
#include "V8Engine.h"
#include "StringConvert.h"
#include "Log.h"
JS_CLASS_METHOD(JsHttpRequestBinding,Get) {

	if(args.Length() == 1) {
		string url(*String::Utf8Value(args[0]));
		string result = JsHttpRequest::ShareJsHttpRequest()->Get(url);
		//GBKToUTF8(result,"gb2312","utf-8");
		return String::New(result.c_str());
	}
	return Undefined();
}

JS_CLASS_METHOD(JsHttpRequestBinding,Post) {
	return Undefined();
}
void JsHttpRequestBinding::BindingOnV8(Persistent<Context> context) {
	Handle < Object > obj = V8Engine::ExposeGlobalObject(context,
			v8::String::New("HttpRequest"), v8::ReadOnly);
	ExposeMethod( obj);
}

void JsHttpRequestBinding::ExposeMethod(Handle<Object> obj) {

	V8Engine::ExposeMethod(obj, String::New("get"), InvocationCallback(Get));
	V8Engine::ExposeMethod(obj, String::New("post"), InvocationCallback(Post));
}
