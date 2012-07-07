#ifndef _JAVASCRIPT_ENGINE_H
#define _JAVASCRIPT_ENGINE_H
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JavaScriptEngine {
public:
	JavaScriptEngine();
public:
	static JavaScriptEngine & ShareInstance() {
		static JavaScriptEngine instance;
		return instance;
	}
public:
	JSContext *ShareContext() {
		return globalContext;
	}
	JSObject *ShareObject() {
		return globalObject;
	}
	JSRuntime *ShareRuntime() {
		return globalRuntime;
	}
public:
	char * LoadJsFile(const char* fileName);
	void BindingGlobalObject();
	void BindingObject();
	void Start();
	static void ReportError(JSContext *cx, const char *message,
			JSErrorReport *report);
	void RunScript(const char *fileName);
	void ShutDown();
	void GC();
private:
	JSContext* globalContext;
	JSRuntime* globalRuntime;
	JSObject * globalObject;
	static JSClass globalClass;
};

#endif
